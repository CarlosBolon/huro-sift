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
    upright_(false)
{
    surfDetector_ = new SurfFeatureDetector(hessianThreshold_, octaves_, octaveLayers_, upright_);

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
    SurfDescriptorExtractor extractor;
    
    // Detect the keypoints
    surfDetector_->detect(frame_, keyPoints);

    // Calculate descriptors (feature vectors)
    extractor.compute(frame_, keyPoints, descriptors);
}

void SurfFeature::Visualize(void)
{
	char buffer[500];

	drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
	sprintf_s(buffer, 500, "Processing time of %s: %.2lf ms.", name_.c_str(), procTime_ / (cvGetTickFrequency() * 1000.0));
	putText(frame_, buffer, Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
	putText(frame_, buffer, Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));

	sprintf_s(buffer, 500, "Number of detected keypoints: %d.", keyPoints.size());
	putText(frame_, buffer, Point(10, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 2);
	putText(frame_, buffer, Point(10, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));

	VisualizerPtr->ShowImage(name_, frame_);
}
