#include "ObjectRecognition\Algorithm.h"
#include "ObjectRecognition\LocalSettings.h"
#include "ObjectRecognition\FileToken.h"
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
	string databaseFileName_;
    string matcherType_;
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

    if(node[0]["media"].isString())
    {
        node[0]["media"] >> detail_->mediaFileName_;
    }
    else
    {
        CV_Error(1, "Wrong media type was given in process xml (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");
    }

    if(node[0]["matcherType"].isString())
    {
        node[0]["matcherType"] >> detail_->matcherType_;
    }
    else
    {
        CV_Error(1, "Wrong matcher type was given in process xml (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");
    }

    if(node[0]["database"].isString())
    {
        node[0]["database"] >> detail_->databaseFileName_;

        if(ReadStringList(LocalSettingsPtr->GetInputDirectory() + detail_->databaseFileName_) == false)
            CV_Error(1, "Wrong image list format in " + detail_->databaseFileName_ + "!");
    }
    else
    {
        CV_Error(1, "Wrong database type was given in process xml (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");
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
	else if(detail_->frameNo_ == 0)
	{
		frame = imread(LocalSettingsPtr->GetInputDirectory() + detail_->mediaFileName_, 1);
	}
	else
	{
		frame = Mat();
	}

	return !frame.empty();
}


void Algorithm::Process(void)
{
	CV_Assert(!detail_->mediaFileName_.empty() || !imageList_.empty());

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

		if(detail_->workMode_ == WORK_MODE_TRAIN)
			SaveData();
		else
			MatchToDatabase();
		
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
	CV_Assert(!detail_->databaseFileName_.empty());

    FileToken ft(imageList_[detail_->frameNo_]);
    string fullName = ft.GetPath() + ft.GetName() + "_descriptors.xml.gz";

	FileStorage fs(fullName, FileStorage::WRITE, "UTF-8");
	if(!fs.isOpened())
		CV_Error(1, "XML does not exist (" + fullName + ")!");

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

void Algorithm::MatchToDatabase(void)
{
    CV_Assert(!detail_->databaseFileName_.empty());

	vector<Mat> trainDescriptors;

    for(int i = 0; i < int(imageList_.size()); i++)
    {
        FileToken ft(imageList_[i]);
        string fullName = ft.GetPath() + ft.GetName() + "_descriptors.xml.gz";
        
        FileStorage fs(fullName, FileStorage::READ, "UTF-8");
        if(!fs.isOpened())
            CV_Error(1, "Descriptor XML does not exist (" + fullName + ")!");

        FileNode node = fs["database"];
        Mat descriptor;
        string key = detail_->matcherType_ + "_Descriptors";

        cout << "Loading " + detail_->matcherType_ + " descriptor for: " << fullName << endl;

        if(!node[0][key].isNone())
            node[0][key] >> descriptor;
        else
            CV_Error(1, detail_->matcherType_ + " descriptor does not exist (" + fullName + ")!");

        if(!descriptor.empty())
            trainDescriptors.push_back(descriptor);

        fs.release();
    }


}


}
