#include <iostream>

#include "ObjectRecognition\OrbFeature.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{

OrbFeature::OrbFeature(const string& name, const string& type)
:	LocalFeature(name, type)
{
	LoadSettingsFromFileStorage();

    orbDetector_ = new OrbFeatureDetector(nFeatures_, scaleFactor_, nlevels_, edgeThreshold_, 
        firstLevel_, wtaK_, scoreType_, patchSize_);
}

OrbFeature::~OrbFeature(void)
{
    delete orbDetector_;
}

void OrbFeature::LoadSettingsFromFileStorage(void)
{
	string fileName = LocalSettingsPtr->GetFeatureExtractorDirectory() + "Settings." + name_ + ".xml";
	FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		CV_Error(1, "Setting XML does not exist for " + name_ + "!");

	string fsScoreType;
	fileStorage["nFeatures"] >> nFeatures_;
	fileStorage["scaleFactor"] >> scaleFactor_;
	fileStorage["nlevels"] >> nlevels_;
	fileStorage["edgeThreshold"] >> edgeThreshold_;
	fileStorage["firstLevel"] >> firstLevel_;
	fileStorage["wtaK"] >> wtaK_;
	fileStorage["scoreType"] >> fsScoreType;
	fileStorage["patchSize"] >> patchSize_;

	if(fsScoreType.compare("kBytes") == 0)
		scoreType_ = ORB::kBytes;
	else if(fsScoreType.compare("HARRIS_SCORE") == 0)
		scoreType_ = ORB::HARRIS_SCORE;
	else if(fsScoreType.compare("FAST_SCORE") == 0)
		scoreType_ = ORB::FAST_SCORE;
}

void OrbFeature::Process(void)
{
    // Detect the keypoints
    orbDetector_->detect(frame_, keyPoints);
}

void OrbFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT /*| DrawMatchesFlags::DRAW_RICH_KEYPOINTS*/); 
}

}
