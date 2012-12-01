#include "ObjectRecognition\Algorithm.h"
#include "ObjectRecognition\LocalSettings.h"
#include "ObjectRecognition\Tokenizer.h"
#include "ObjectRecognition\Visualizer.h"

#include "ObjectRecognition\SiftFeature.h"
#include "ObjectRecognition\SurfFeature.h"
#include "ObjectRecognition\OrbFeature.h"
#include "ObjectRecognition\StarFeature.h"
#include "ObjectRecognition\MserFeature.h"
#include "ObjectRecognition\FastFeature.h"

#include "ObjectRecognition\LbpFeature.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{


struct Algorithm::Detail 
{
	Algorithm::WorkMode workMode_;
	int cameraId_;				//!< ID of the camera to be analyzed.
	string mediaFileName_;
	string descriptorsFileName_;
	int frameNo_;
	double maxWidth_;
};


Algorithm::Algorithm(void)
:	detail_(new Detail)
{
	detail_->workMode_ = WORK_MODE_TRAIN;
	detail_->cameraId_ = 0;
	detail_->frameNo_ = 0;
    detail_->maxWidth_ = 640.0;

	LoadSettingsFromFileStorage();
}


Algorithm::~Algorithm(void)
{
	for(ThreadPool::iterator elem = threadPool_.begin(); elem != threadPool_.end(); elem++)
		delete elem->second;
}


void Algorithm::LoadSettingsFromFileStorage(void)
{
    FileStorage fileStorage(LocalSettingsPtr->GetProcessXmlFileName(), FileStorage::READ, "UTF-8");
    if(!fileStorage.isOpened())
        CV_Error(1, "Process XML does not exist (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");

    FileNode node = fileStorage["settings"];

	if(node[0]["workMode"].isString())
	{
		string workModeStr;
		node[0]["workMode"] >> workModeStr;

		if(workModeStr == "train")
			detail_->workMode_ = WORK_MODE_TRAIN;
		else if(workModeStr == "test")
			detail_->workMode_ = WORK_MODE_TEST;
		else
			CV_Error(1, "Wrong identifier in process xml <workMode> tag (just \"train\" or \"test\" allowed)!");
	}
	else
	{
		CV_Error(1, "Wrong identifier type in process xml <workMode> tag (it must be string)!");
	}

	if(detail_->workMode_ == WORK_MODE_TRAIN && node[0]["media"].isString())
	{
		node[0]["media"] >> detail_->mediaFileName_;
		if(detail_->mediaFileName_.compare(detail_->mediaFileName_.size() - 4, 4, ".txt") == 0)
		{
			if(ReadStringList(LocalSettingsPtr->GetInputDirectory() + detail_->mediaFileName_) == false)
				CV_Error(1, "Wrong image list format in " + detail_->mediaFileName_ + "!");
		}
		else
		{
			CV_Error(1, "File list (txt) must be given before training phase!");
		}
	}
	else if(detail_->workMode_ == WORK_MODE_TEST)
	{
		if(node[0]["media"].isInt())
		{
			node[0]["media"] >> detail_->cameraId_;
			videoCapture_.open(detail_->cameraId_);
		}
		else if(node[0]["media"].isString())
		{
			node[0]["media"] >> detail_->mediaFileName_;
			videoCapture_.open(LocalSettingsPtr->GetInputDirectory() + detail_->mediaFileName_);
		}

		if(!videoCapture_.isOpened())
			CV_Error(1, "VideoCapture is not opened!");
	}
	else
	{
		CV_Error(1, "Wrong configuration is given between work mode and media type!");
	}

	if(node[0]["descriptors"].isString())
	{
		node[0]["descriptors"] >> detail_->descriptorsFileName_;
	}
	else
	{
		CV_Error(1, "Wrong descriptors filename!");
	}

    node[0]["maxWidth"] >> detail_->maxWidth_;

    // Loading feature extractors
    node = fileStorage["featureExtractors"];
    for(size_t i = 0; i < node.size(); ++i)
    {
        string name, type;
        node[i]["name"] >> name;
        node[i]["type"] >> type;

        // Global feature extractors
        if(name.compare("SIFT") == 0)
            threadPool_[name] = localFeaturePool_[name] = new SiftFeature(name, type);
        else if(name.compare("SURF") == 0)
            threadPool_[name] = localFeaturePool_[name] = new SurfFeature(name, type);
        else if(name.compare("ORB") == 0)
            threadPool_[name] = localFeaturePool_[name] = new OrbFeature(name, type);
        else if(name.compare("STAR") == 0)
            threadPool_[name] = localFeaturePool_[name] = new StarFeature(name, type);
        else if(name.compare("MSER") == 0)
            threadPool_[name] = localFeaturePool_[name] = new MserFeature(name, type);
        else if(name.compare("FAST") == 0)
            threadPool_[name] = localFeaturePool_[name] = new FastFeature(name, type);
        else if(name.compare("LBP") == 0)
            threadPool_[name] = globalFeaturePool_[name] = new LbpFeature(name, type);
        else
            CV_Error(1, "Unkonwn feature extractor (" + name + ")!");
    }
    // Loading feature extractors
}


bool Algorithm::ReadStringList(const string& filename)
{
	imageList_.resize(0);

	FileStorage fs(filename, FileStorage::READ);
	if(!fs.isOpened())
		return false;

	FileNode n = fs.getFirstTopLevelNode();
	if(n.type() != FileNode::SEQ)
		return false;

	for(FileNodeIterator it = n.begin(); it != n.end(); ++it)
		imageList_.push_back(string(*it));

	return true;
}


bool Algorithm::GrabFrame(Mat& frame)
{
	if(detail_->workMode_ == WORK_MODE_TRAIN)
	{
		if(detail_->frameNo_ < 0 || detail_->frameNo_ >= int(imageList_.size()))
			return false;

		frame = imread(imageList_[detail_->frameNo_], 1);
	}
	else
	{
		videoCapture_ >> frame;
	}

	return !frame.empty();
}


void Algorithm::Process(void)
{
	CV_Assert(videoCapture_.isOpened() || !imageList_.empty());

	cout << "HeadMovementAlgorithm: Press ESC to exit." << endl;
	Mat frame;

	while(true)
	{
#ifdef DEBUG_MODE
        double t = (double)cvGetTickCount();
#endif
		if(GrabFrame(frame) == false)
			break;

		resize(frame, frame, Size(), detail_->maxWidth_ / frame.cols, detail_->maxWidth_ / frame.cols);

        StartFeatureExtractors(frame);

        VisualizeProcesses();

		SaveData();
		
		// press ESC to exit
		if(waitKey(5) >= 0) 
			break;

#ifdef DEBUG_MODE
        t = (double)cvGetTickCount() - t;
        double ms = t / ((double)cvGetTickFrequency() * 1000.0);
        double fps = 1000.0 / ms;
        printf("Processing time: %6.2lf ms - %6.2lf fps.\n", ms, fps);
#endif

		detail_->frameNo_++;
	}
}


void Algorithm::SaveData(void)
{
	CV_Assert(!detail_->descriptorsFileName_.empty());

	vector<string> pathParts;
	ObjectRecognition::Tokenizer t(imageList_[detail_->frameNo_], "\\.");
	while(t.NextToken())
		pathParts.push_back(t.GetToken());

	string fileName;
	if(pathParts.size() > 3)
		fileName = pathParts[pathParts.size() - 3] + "_" + pathParts[pathParts.size() - 2] + "_descriptors.xml";

	if(fileName.empty())
		CV_Error(1, "Wrong descriptor filename (" + imageList_[detail_->frameNo_] + ")!");

	FileStorage fs(LocalSettingsPtr->GetDescriptorsDirectory() + fileName, FileStorage::WRITE);
	if(!fs.isOpened())
	{
		CV_Error(1, "XML does not exist (" + LocalSettingsPtr->GetDescriptorsDirectory() + fileName + ")!");
	}

	fs << "database" << "[";
	fs << "{:" << "path" << imageList_[detail_->frameNo_];

	for(LocalFeaturePool::iterator elem = localFeaturePool_.begin(); elem != localFeaturePool_.end(); elem++)
	{
		const vector<KeyPoint>& keyPoints = elem->second->keyPoints;
		const Mat& descriptors = elem->second->descriptors;

		//fs << elem->first + "_KeyPoints" << keyPoints;
		fs << elem->first + "_Descriptors" << descriptors;
	}

	fs << "}";
	fs << "]";
	fs.release();
}

void Algorithm::StartFeatureExtractors(const Mat& frame)
{

    for(ThreadPool::iterator elem = threadPool_.begin(); elem != threadPool_.end(); elem++)
    {
        GlobalFeature* globalFeature = dynamic_cast<GlobalFeature*>(elem->second);
        LocalFeature* localFeature = dynamic_cast<LocalFeature*>(elem->second);

        if(globalFeature)
        {
            globalFeature->SetFrame(frame);
            globalFeature->Start();
        }

        if(localFeature)
        {
            localFeature->SetFrame(frame);
            localFeature->Start();
        }
    }
}


void Algorithm::VisualizeProcesses(void)
{
    for(ThreadPool::iterator elem = threadPool_.begin(); elem != threadPool_.end(); elem++)
    {
        GlobalFeature* globalFeature = dynamic_cast<GlobalFeature*>(elem->second);
        LocalFeature* localFeature = dynamic_cast<LocalFeature*>(elem->second);

        if(localFeature)
        {
            localFeature->Join();
            localFeature->Visualize();
        }

        if(globalFeature)
        {
            globalFeature->Join();
            globalFeature->Visualize();
        }
    }
}


}
