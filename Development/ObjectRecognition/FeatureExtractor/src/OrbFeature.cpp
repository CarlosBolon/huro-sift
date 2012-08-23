#include "OrbFeature.h"

#include <iostream>
#include "LocalSettings.h"

using namespace std;
using namespace cv;

OrbFeature::OrbFeature(const string& name)
:	Feature(name),
    nFeatures_(500),
    scaleFactor_(1.2f),
    nlevels_(8), 
    edgeThreshold_(31),
    firstLevel_(0),
    wtaK_(2),
    scoreType_(ORB::HARRIS_SCORE),
    patchSize_(31)
{
    orbDetector_ = new OrbFeatureDetector(nFeatures_, scaleFactor_, nlevels_, edgeThreshold_, 
        firstLevel_, wtaK_, scoreType_, patchSize_);

    LoadSettingsFromFileStorage();
}

OrbFeature::~OrbFeature(void)
{
    delete orbDetector_;
}

void OrbFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ);

    // TODO: Read settings...
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
