#include "SiftFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(const string& name)
:	Feature(name)
{
	LoadSettingsFromFileStorage();

    siftDetector_ = new SiftFeatureDetector(nfeatures_, nOctaveLayers_, contrastThreshold_, edgeThreshold_, sigma_);
}

SiftFeature::~SiftFeature(void)
{
    delete siftDetector_;
}

void SiftFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		throw ExceptionError("Setting XML does not exist for " + name_ + "!");

	fileStorage["nfeatures"] >> nfeatures_;
	fileStorage["nOctaveLayers"] >> nOctaveLayers_;
	fileStorage["contrastThreshold"] >> contrastThreshold_;
	fileStorage["edgeThreshold"] >> edgeThreshold_;
	fileStorage["sigma"] >> sigma_;
}

void SiftFeature::Process(void)
{
    // Detect the keypoints
    siftDetector_->detect(frame_, keyPoints);

    // Calculate descriptors (feature vectors)
    siftDetector_->compute(frame_, keyPoints, descriptors);
}

void SiftFeature::DrawFeatures(void)
{
	drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
