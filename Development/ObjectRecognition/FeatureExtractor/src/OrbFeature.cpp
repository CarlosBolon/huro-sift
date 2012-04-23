#include "OrbFeature.h"

#include <iostream>

using namespace std;
using namespace cv;

OrbFeature::OrbFeature(const string& name)
:	Feature(name)
{
}

OrbFeature::~OrbFeature(void)
{
}

void OrbFeature::LoadSettingsFromFileStorage(const FileStorage& fileStorage)
{
}

void OrbFeature::Process(void)
{
	cout << "Thread(" << name_ << "): " << frame_.cols << "x" << frame_.rows << endl;

	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow(name_, frame_);
	waitKey(0);
}

void OrbFeature::detectImpl(void)
{

}
