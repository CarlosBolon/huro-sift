#include "HuroAlgorithm.h"

#include <iostream>

#include "SiftFeature.h"
#include "SurfFeature.h"
#include "OrbFeature.h"
#include "StarFeature.h"
#include "MserFeature.h"
#include "FastFeature.h"

#include "LbpFeature.h"

#include "ImageFrame.h"
#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

HuroAlgorithm::HuroAlgorithm(void)
:	mediaType_("image"),
	cameraId_(0),
	imageName_("")
{
    LoadSettingsFromFileStorage();
}

HuroAlgorithm::~HuroAlgorithm(void)
{
    for(GlobalFeaturePool::iterator fpElem = globalFeaturePool_.begin(); fpElem != globalFeaturePool_.end(); fpElem++)
        delete fpElem->second;

    for(LocalFeaturePool::iterator fpElem = localFeaturePool_.begin(); fpElem != localFeaturePool_.end(); fpElem++)
        delete fpElem->second;

	delete imageFrame_;
}

void HuroAlgorithm::LoadSettingsFromFileStorage(void)
{
    FileStorage fileStorage(LocalSettingsPtr->GetProcessXmlFileName(), FileStorage::READ, "UTF-8");
    if(!fileStorage.isOpened())
        throw ExceptionError("Process XML does not exist (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");

    // Loading general settings
    FileNode node = fileStorage["settings"];
	node[0]["mediaType"] >> mediaType_;

    if(mediaType_.compare("camera") == 0)
	{
		node[0]["cameraId"] >> cameraId_	;
        imageFrame_ = new ImageFrame(cameraId_);
	}
    else if(mediaType_.compare("image") == 0)
	{
		node[0]["imageName"] >> imageName_;
        imageFrame_ = new ImageFrame(imageName_);
	}
    else
	{
        throw ExceptionError("Wrong media type in (" + LocalSettingsPtr->GetProcessXmlFileName() + ")!");
	}
    
    // Loading feature extractors
    node = fileStorage["featureExtractors"];
    for(size_t i = 0; i < node.size(); ++i)
    {
        string name, type;
        node[i]["name"] >> name;
        node[i]["type"] >> type;

        // Global feature extractors
        if(name.compare("SIFT") == 0)
            globalFeaturePool_[name] = new SiftFeature(name, type);
        else if(name.compare("SURF") == 0)
            globalFeaturePool_[name] = new SurfFeature(name, type);
        else if(name.compare("ORB") == 0)
            globalFeaturePool_[name] = new OrbFeature(name, type);
        else if(name.compare("STAR") == 0)
            globalFeaturePool_[name] = new StarFeature(name, type);
        else if(name.compare("MSER") == 0)
            globalFeaturePool_[name] = new MserFeature(name, type);
        else if(name.compare("FAST") == 0)
            globalFeaturePool_[name] = new FastFeature(name, type);
        else if(name.compare("LBP") == 0)
            localFeaturePool_[name] = new LbpFeature(name, type);
		// TODO: Local feature extractors here:
		// else if(...)
        else
            throw ExceptionWarning("Unkonwn feature extractor (" + name + ")!");
    }
}

void HuroAlgorithm::Process(void)
{
    // Initializing the global feature extractors
    Mat frame = imageFrame_->GetFrame();
    for(GlobalFeaturePool::iterator fpElem = globalFeaturePool_.begin(); fpElem != globalFeaturePool_.end(); fpElem++)
    {
        fpElem->second->SetFrame(frame);
        fpElem->second->Start();
    }

    // Initializing the local feature extractors
    for(LocalFeaturePool::iterator fpElem = localFeaturePool_.begin(); fpElem != localFeaturePool_.end(); fpElem++)
    {
        fpElem->second->SetFrame(frame);
        fpElem->second->Start();
    }

    // Starting global feature extractors
    for(GlobalFeaturePool::iterator fpElem = globalFeaturePool_.begin(); fpElem != globalFeaturePool_.end(); fpElem++)
        int result = reinterpret_cast<int>(fpElem->second->Join());

    // Starting local feature extractors
    for(LocalFeaturePool::iterator fpElem = localFeaturePool_.begin(); fpElem != localFeaturePool_.end(); fpElem++)
        int result = reinterpret_cast<int>(fpElem->second->Join());
}
