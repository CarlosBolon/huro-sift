#include "SiftFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(const string& name)
:	Feature(name)//,
    //siftDetectorParams_(0.006f, 100.0f),
    //siftCommonParams_(4, 3, -1, 1),
    //siftDescriptorParams_(3.0f, true, true)
{
    siftDetector_ = new SiftFeatureDetector(siftDetectorParams_, siftCommonParams_);

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
    SiftDescriptorExtractor siftDescriptor(siftDescriptorParams_, siftCommonParams_);

    // Detect the keypoints
    siftDetector_->detect(frame_, keyPoints);

    // Calculate descriptors (feature vectors)
    siftDescriptor.compute(frame_, keyPoints, descriptors);
}

void SiftFeature::Visualize(void)
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
