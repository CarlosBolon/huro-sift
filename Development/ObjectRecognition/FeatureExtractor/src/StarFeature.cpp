#include "StarFeature.h"

#include <iostream>

using namespace std;
using namespace cv;

StarFeature::StarFeature(const string& name)
:	Feature(name)
{
}

StarFeature::~StarFeature(void)
{
}

void StarFeature::LoadSettingsFromFileStorage(const FileStorage& fileStorage)
{
}

void StarFeature::Process(void)
{
	cout << "Thread(" << name_ << "): " << frame_.cols << "x" << frame_.rows << endl;

	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow(name_, frame_);
	waitKey(0);
}

void StarFeature::detectImpl(void)
{
	
}
