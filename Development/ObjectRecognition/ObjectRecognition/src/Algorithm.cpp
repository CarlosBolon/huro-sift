#include "Algorithm.h"

#include <iostream>

#include "SiftFeature.h"
#include "SurfFeature.h"
#include "OrbFeature.h"
#include "StarFeature.h"

//#include "ExceptionDescriptor.h"
//#include "LocalSettings.h"
#include "ImageFrame.h"

using namespace std;
using namespace cv;

Algorithm::Algorithm(void)
{
	// TODO: MSER, FAST classes.

    featurePool_["SIFT"] = new SiftFeature("SIFT");
    featurePool_["SURF"] = new SurfFeature("SURF");
    //featurePool_["ORB"] = new OrbFeature("ORB");
    //featurePool_["STAR"] = new StarFeature("STAR");

	imageFrame_ = new ImageFrame(0);
}

Algorithm::~Algorithm(void)
{
    for(FeaturePool::iterator fpElem = featurePool_.begin(); fpElem != featurePool_.end(); fpElem++)
        delete fpElem->second;

	delete imageFrame_;
}

void Algorithm::ProcessInit(void)
{
    Mat frame = imageFrame_->GetFrame();

    for(FeaturePool::iterator fpElem = featurePool_.begin(); fpElem != featurePool_.end(); fpElem++)
    {
        fpElem->second->SetFrame(frame);
        fpElem->second->Start();
    }
}

void Algorithm::Process(void)
{
    ProcessInit();

    for(FeaturePool::iterator fpElem = featurePool_.begin(); fpElem != featurePool_.end(); fpElem++)
        int result = reinterpret_cast<int>(fpElem->second->Join());

	waitKey(0);
}
