#include "OrbFeature.h"

#include <iostream>
#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

OrbFeature::OrbFeature(const string& name)
:	Feature(name)
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
	string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
	FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		throw ExceptionError("Setting XML does not exist for " + name_ + "!");

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

    // Calculate descriptors (feature vectors)
    orbDetector_->compute(frame_, keyPoints, descriptors);
}

void OrbFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
