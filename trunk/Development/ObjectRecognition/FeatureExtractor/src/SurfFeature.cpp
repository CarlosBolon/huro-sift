#include "SurfFeature.h"

#include <iostream>

using namespace std;
using namespace cv;

SurfFeature::SurfFeature(const string& name)
:	Feature(name)
{
}

SurfFeature::~SurfFeature(void)
{
}

void SurfFeature::LoadSettingsFromFileStorage(const FileStorage& fileStorage)
{
}

void SurfFeature::Process(void)
{
	cout << "Thread(" << name_ << "): " << frame_.cols << "x" << frame_.rows << endl;

	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow(name_, frame_);
	waitKey(0);
}

void SurfFeature::detectImpl(void)
{

}
