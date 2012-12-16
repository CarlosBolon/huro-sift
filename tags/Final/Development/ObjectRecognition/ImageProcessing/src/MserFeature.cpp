#include <iostream>

#include "ObjectRecognition\MserFeature.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{


MserFeature::MserFeature(const string& name, const string& type)
:	LocalFeature(name, type)
{
	LoadSettingsFromFileStorage();

    mserDetector_ = new MserFeatureDetector(delta_, minArea_, maxArea_, maxVariation_, minDiversity_, 
        maxEvolution_, areaThreshold_, minMargin_, edgeBlurSize_);
}


MserFeature::~MserFeature(void)
{
    delete mserDetector_;
}


void MserFeature::LoadSettingsFromFileStorage(void)
{
	string fileName = LocalSettingsPtr->GetFeatureExtractorDirectory() + "Settings." + name_ + ".xml";
	FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		CV_Error(1, "Setting XML does not exist for " + name_ + "!");

	fileStorage["delta"] >> delta_;
	fileStorage["minArea"] >> minArea_;
	fileStorage["maxArea"] >> maxArea_;
	fileStorage["maxVariation"] >> maxVariation_;
	fileStorage["minDiversity"] >> minDiversity_;
	fileStorage["maxEvolution"] >> maxEvolution_;
	fileStorage["areaThreshold"] >> areaThreshold_;
	fileStorage["minMargin"] >> minMargin_;
	fileStorage["edgeBlurSize"] >> edgeBlurSize_;
}


void MserFeature::Process(void)
{
    // Detect the keypoints
    mserDetector_->detect(frame_, keyPoints);
}


void MserFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT /*| DrawMatchesFlags::DRAW_RICH_KEYPOINTS*/); 
}


}
