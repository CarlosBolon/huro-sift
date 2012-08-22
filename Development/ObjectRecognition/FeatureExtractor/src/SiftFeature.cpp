#include "SiftFeature.h"

#include <iostream>

#include "LocalSettings.h"

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

    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 

	imshow(name_, frame_);
	waitKey(0);
}
