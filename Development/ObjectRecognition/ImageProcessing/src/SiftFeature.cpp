#include <iostream>

#include "ObjectRecognition\SiftFeature.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{

SiftFeature::SiftFeature(const string& name, const string& type)
:	LocalFeature(name, type)
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
    string fileName = LocalSettingsPtr->GetFeatureExtractorDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		CV_Error(1, "Setting XML does not exist for " + name_ + "!");

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
}

void SiftFeature::DrawFeatures(void)
{
	drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT /*| DrawMatchesFlags::DRAW_RICH_KEYPOINTS*/); 
}

}
