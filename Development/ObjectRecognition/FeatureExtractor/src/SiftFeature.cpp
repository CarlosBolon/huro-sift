#include "SiftFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(const string& name)
:	Feature(name),
    nfeatures_(0),
    nOctaveLayers_(3),
    contrastThreshold_(0.04),
    edgeThreshold_(10.0),
    sigma_(1.6)
{
    siftDetector_ = new SiftFeatureDetector(nfeatures_, nOctaveLayers_, contrastThreshold_, edgeThreshold_, sigma_);

    LoadSettingsFromFileStorage();
}

SiftFeature::~SiftFeature(void)
{
    delete siftDetector_;
}

void SiftFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ);

    // TODO: Read settings...
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
