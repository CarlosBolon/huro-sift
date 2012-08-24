#include "SurfFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

SurfFeature::SurfFeature(const string& name, const string& type)
:	GlobalFeature(name, type)
{
	LoadSettingsFromFileStorage();

    surfDetector_ = new SurfFeatureDetector(hessianThreshold_, octaves_, octaveLayers_, extended_, upright_);
}

SurfFeature::~SurfFeature(void)
{
    delete surfDetector_;
}

void SurfFeature::LoadSettingsFromFileStorage(void)
{
	string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
	FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

	if(!fileStorage.isOpened())
		throw ExceptionError("Setting XML does not exist for " + name_ + "!");

	string fsExtended, fsUpright;
	fileStorage["hessianThreshold"] >> hessianThreshold_;
	fileStorage["octaves"] >> octaves_;
	fileStorage["octaveLayers"] >> octaveLayers_;
	fileStorage["extended"] >> fsExtended;
	fileStorage["upright"] >> fsUpright;

	extended_= (fsExtended.compare("true") == 0 ? true : false);
	upright_ = (fsUpright.compare("true") == 0 ? true : false);
}

void SurfFeature::Process(void)
{
    // Detect the keypoints
    surfDetector_->detect(frame_, keyPoints);
}

void SurfFeature::DrawFeatures(void)
{
	drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT /*| DrawMatchesFlags::DRAW_RICH_KEYPOINTS*/); 
}
