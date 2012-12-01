#include "ObjectRecognition\Algorithm.h"
#include "ObjectRecognition\LocalSettings.h"
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

Algorithm::Algorithm(void)
:   cameraId_(0),
	fileName_(""),
    resolution_(Size(640, 480))
{
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
	if(node[0]["media"].isInt())
	{
		node[0]["media"] >> cameraId_;
		videoCapture_.open(cameraId_);
	}
	else if(node[0]["media"].isString())
	{
		node[0]["media"] >> fileName_;
		videoCapture_.open(/*LocalSettingsPtr->GetInputDirectory() +*/ fileName_);
	}

	if(!videoCapture_.isOpened())
		CV_Error(1, "VideoCapture is not opened!");
    
    node[0]["width"] >> resolution_.width;
    node[0]["height"] >> resolution_.height;


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

void Algorithm::Process(void)
{
	cout << "HeadMovementAlgorithm: Press ESC to exit." << endl;

	while(true)
	{
#ifdef DEBUG_MODE
        double t = (double)cvGetTickCount();
#endif
		// get a new frame from camera
		videoCapture_ >> frame_;

		if(frame_.empty())
			break;

        resize(frame_, frame_, resolution_);

        StartFeatureExtractors();
        VisualizeProcesses();

        keyPoints_.clear();
        for(LocalFeaturePool::iterator elem = localFeaturePool_.begin(); elem != localFeaturePool_.end(); elem++)
        {
            const vector<KeyPoint>& keyPoints = elem->second->keyPoints;
            for(size_t i = 0; i < keyPoints.size(); i++)
                keyPoints_.push_back(keyPoints[i]);
        }

        if(!keyPoints_.empty())
        {
            // TODO
        }

		
		// press ESC to exit
		if(waitKey(5) >= 0) 
			break;

#ifdef DEBUG_MODE
        t = (double)cvGetTickCount() - t;
        double ms = t / ((double)cvGetTickFrequency() * 1000.0);
        double fps = 1000.0 / ms;
        printf("Processing time: %6.2lf ms - %6.2lf fps.\n", ms, fps);
#endif
	}
}

void Algorithm::StartFeatureExtractors(void)
{

    for(ThreadPool::iterator elem = threadPool_.begin(); elem != threadPool_.end(); elem++)
    {
        GlobalFeature* globalFeature = dynamic_cast<GlobalFeature*>(elem->second);
        LocalFeature* localFeature = dynamic_cast<LocalFeature*>(elem->second);

        if(globalFeature)
        {
            globalFeature->SetFrame(frame_);
            globalFeature->Start();
        }

        if(localFeature)
        {
            localFeature->SetFrame(frame_);
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
