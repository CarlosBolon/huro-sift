#include "SiftFeature.h"

#include <iostream>

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(const string& name)
:	Feature(name)
{
}

SiftFeature::~SiftFeature(void)
{
}

void SiftFeature::LoadSettingsFromFileStorage(const FileStorage& fileStorage)
{
}

void SiftFeature::Process(void)
{
	cout << "Thread(" << name_ << "): " << frame_.cols << "x" << frame_.rows << endl;

	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow(name_, frame_);
	waitKey(0);
}

void SiftFeature::detectImpl(void)
{
	
}
