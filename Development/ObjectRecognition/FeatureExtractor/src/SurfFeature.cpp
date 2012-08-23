#include "SurfFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

SurfFeature::SurfFeature(const string& name)
:	Feature(name),
    hessianThreshold_(400.0),
    octaves_(3),
    octaveLayers_(4),
    extended_(true),
    upright_(false)
{
    surfDetector_ = new SurfFeatureDetector(hessianThreshold_, octaves_, octaveLayers_, extended_, upright_);

    LoadSettingsFromFileStorage();
}

SurfFeature::~SurfFeature(void)
{
    delete surfDetector_;
}

void SurfFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ);

    // TODO: Read settings...
}

void SurfFeature::Process(void)
{
    // Detect the keypoints
    surfDetector_->detect(frame_, keyPoints);

    // Calculate descriptors (feature vectors)
    surfDetector_->compute(frame_, keyPoints, descriptors);
}

void SurfFeature::DrawFeatures(void)
{
	drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT | DrawMatchesFlags::DRAW_RICH_KEYPOINTS); 
}
