#include "ObjectRecognition\Algorithm.h"
#include "ObjectRecognition\LocalSettings.h"
#include "ObjectRecognition\Matcher.h"
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
	Algorithm::WorkMode workMode;
	string mediaFileName;
	string databaseFileName;
    string descriptorType;
    string matcherType;
	int frameNo;
	double maxWidth;
};


Algorithm::Algorithm(void)
:	detail_(new Detail)
{
	detail_->workMode = WORK_MODE_TRAIN;
	detail_->frameNo = 0;
    detail_->maxWidth = 640.0;
    detail_->descriptorType = "SURF";

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
			detail_->workMode = WORK_MODE_TRAIN;
		else if(workModeStr == "test")
			detail_->workMode = WORK_MODE_TEST;
	}

    if(node[0]["media"].isString())
        node[0]["media"] >> detail_->mediaFileName;

    if(node[0]["descriptorType"].isString())
        node[0]["descriptorType"] >> detail_->descriptorType;

    if(node[0]["matcherType"].isString())
        node[0]["matcherType"] >> detail_->matcherType;

    if(node[0]["database"].isString())
    {
        node[0]["database"] >> detail_->databaseFileName;
        if(ReadStringList(LocalSettingsPtr->GetInputDirectory() + detail_->databaseFileName) == false)
            CV_Error(1, "Wrong image list format in " + detail_->databaseFileName + "!");
    }

    node[0]["maxWidth"] >> detail_->maxWidth;

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
	if(detail_->workMode == WORK_MODE_TRAIN)
	{
		if(detail_->frameNo < 0 || detail_->frameNo >= int(imageList_.size()))
			return false;

		frame = imread(imageList_[detail_->frameNo], 1);
	}
	else if(detail_->frameNo == 0)
	{
		frame = imread(LocalSettingsPtr->GetInputDirectory() + detail_->mediaFileName, 1);
	}
	else
	{
		frame = Mat();
	}

	return !frame.empty();
}


void Algorithm::Process(void)
{
	CV_Assert(!detail_->mediaFileName.empty() || !imageList_.empty());

	cout << "HeadMovementAlgorithm: Press ESC to exit." << endl;
	Mat frame;

	while(true)
	{
#ifdef DEBUG_MODE
        TickMeter tm;
        tm.start();
#endif
		if(GrabFrame(frame) == false)
			break;

        resize(frame, frame, Size(), detail_->maxWidth / frame.cols, detail_->maxWidth / frame.cols);

        StartFeatureExtractors(frame);

        VisualizeProcesses();

		if(detail_->workMode == WORK_MODE_TRAIN)
			SaveData();
		else
			MatchToDatabase(frame);
		
        detail_->frameNo++;

		// press ESC to exit
		//if(waitKey(5) >= 0) 
		//	break;

#ifdef DEBUG_MODE
        tm.stop();
        double ms = tm.getTimeMilli();
        double fps = 1000.0 / ms;
        printf("Processing time: %6.2lf ms - %6.2lf fps.\n", ms, fps);
#endif
	}
}


void Algorithm::SaveData(void)
{
	CV_Assert(!detail_->databaseFileName.empty());

    FileToken ft(imageList_[detail_->frameNo]);
    string descName = ft.GetPath() + ft.GetName() + "_descriptors.xml.gz";
	FileStorage fsDesc(descName, FileStorage::WRITE, "UTF-8");

	if(!fsDesc.isOpened())
		CV_Error(1, "XML does not exist (" + descName + ")!");

	fsDesc << "database" << "[";
	fsDesc << "{:" << "path" << imageList_[detail_->frameNo];

	for(LocalFeaturePool::iterator elem = localFeaturePool_.begin(); elem != localFeaturePool_.end(); elem++)
	{
		const vector<KeyPoint>& keyPoints = elem->second->keyPoints;
		const Mat& descriptors = elem->second->descriptors;

		fsDesc << elem->first + "_KeyPoints" << keyPoints;
		fsDesc << elem->first + "_Descriptors" << descriptors;
	}

	fsDesc << "}";
	fsDesc << "]";
	fsDesc.release();
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

void Algorithm::MatchToDatabase(const Mat& frame)
{
    CV_Assert(!detail_->databaseFileName.empty());

	Matcher matcher(detail_->descriptorType, detail_->matcherType);
    const Mat& queryDescriptors = localFeaturePool_[detail_->descriptorType]->descriptors;
    matcher.Process(imageList_, queryDescriptors);

    const vector<DMatch>& matches = matcher.GetMatches();

    if(matches.size() > 1)
    {
        map<int, int> avgMatches;
        for(int i = 0; i < int(matches.size()); i++)
            avgMatches[matches[i].imgIdx]++;

        int maxInd = -1;
        int maxVal = -1;
        for(map<int, int>::iterator it = avgMatches.begin(); it != avgMatches.end(); it++)
        {
            if(it->second > maxVal)
            {
                maxInd = it->first;
                maxVal = it->second;
            }
        }

        if(maxInd >= 0 && maxInd < int(imageList_.size()))
        {
            cout << "Best match: " << imageList_[maxInd] << endl;

            FileToken ft(imageList_[maxInd]);
            string fullName = ft.GetPath() + ft.GetName() + "_descriptors.xml.gz";

            FileStorage fs(fullName, FileStorage::READ, "UTF-8");
            if(!fs.isOpened())
                CV_Error(1, "Descriptor XML does not exist (" + fullName + ")!");

            FileNode node = fs["database"];
            string key = detail_->descriptorType + "_KeyPoints";

            if(!node[0][key].isNone())
            {
                vector<KeyPoint> trainKeypoints;
                read(node[0][key], trainKeypoints);

                if(!trainKeypoints.empty())
                {
                    const vector<KeyPoint>& queryKeypoints = localFeaturePool_[detail_->descriptorType]->keyPoints;
                    Mat trainImage = imread(imageList_[maxInd], 1);
                    Mat drawImg;
                    vector<char> mask;

                    resize(trainImage, trainImage, Size(), detail_->maxWidth / trainImage.cols, detail_->maxWidth / trainImage.cols);

                    MaskMatchesByTrainImgIdx(matches, maxInd, mask);
                    drawMatches(
                        frame, queryKeypoints, 
                        trainImage, trainKeypoints,
                        matches, drawImg, 
                        Scalar(255, 0, 0), Scalar(0, 255, 255), mask 
                    );

                    VisualizerPtr->ShowImage("Matches", drawImg, true);
                }
            }

            fs.release();
        }
    }
}

void Algorithm::MaskMatchesByTrainImgIdx( const vector<DMatch>& matches, int trainImgIdx, vector<char>& mask )
{
    mask.resize( matches.size() );
    fill( mask.begin(), mask.end(), 0 );
    for( size_t i = 0; i < matches.size(); i++ )
    {
        if( matches[i].imgIdx == trainImgIdx )
            mask[i] = 1;
    }
}


}
