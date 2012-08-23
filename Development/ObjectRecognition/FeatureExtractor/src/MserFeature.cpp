#include "MserFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

MserFeature::MserFeature(const string& name)
:	Feature(name),
    delta_(5),
    minArea_(60),
    maxArea_(14400),
    maxVariation_(0.25),
    minDiversity_(0.2),
    maxEvolution_(200),
    areaThreshold_(1.01),
    minMargin_(0.003),
    edgeBlurSize_(5)
{
    mserDetector_ = new MserFeatureDetector(delta_, minArea_, maxArea_, maxVariation_, minDiversity_, 
        maxEvolution_, areaThreshold_, minMargin_, edgeBlurSize_);

    LoadSettingsFromFileStorage();
}

MserFeature::~MserFeature(void)
{
    delete mserDetector_;
}

void MserFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

    // TODO: Read settings...
}

void MserFeature::Process(void)
{
    // Detect the keypoints
    mserDetector_->detect(frame_, keyPoints);
}

void MserFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
