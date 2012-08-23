#include "StarFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

StarFeature::StarFeature(const string& name)
:	Feature(name),
    maxSize_(45), 
    responseThreshold_(30), 
    lineThresholdProjected_(10),
    lineThresholdBinarized_(8),
    suppressNonmaxSize_(5)
{
    starDetector_ = new StarFeatureDetector(maxSize_, responseThreshold_, 
        lineThresholdProjected_, lineThresholdBinarized_, suppressNonmaxSize_);
       
    LoadSettingsFromFileStorage();
}

StarFeature::~StarFeature(void)
{
    delete starDetector_;
}

void StarFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

    // TODO: Read settings...
}

void StarFeature::Process(void)
{
    starDetector_->detect(frame_, keyPoints);
}

void StarFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
