#include "StarFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

StarFeature::StarFeature(const string& name)
:	Feature(name)
{
	LoadSettingsFromFileStorage();

    starDetector_ = new StarFeatureDetector(maxSize_, responseThreshold_, 
        lineThresholdProjected_, lineThresholdBinarized_, suppressNonmaxSize_);
}

StarFeature::~StarFeature(void)
{
    delete starDetector_;
}

void StarFeature::LoadSettingsFromFileStorage(void)
{
	string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
	FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		throw ExceptionError("Setting XML does not exist for " + name_ + "!");

	fileStorage["maxSize"] >> maxSize_;
	fileStorage["responseThreshold"] >> responseThreshold_;
	fileStorage["lineThresholdProjected"] >> lineThresholdProjected_;
	fileStorage["lineThresholdBinarized"] >> lineThresholdBinarized_;
	fileStorage["suppressNonmaxSize"] >> suppressNonmaxSize_;
}

void StarFeature::Process(void)
{
    starDetector_->detect(frame_, keyPoints);
}

void StarFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
