#include "OrbFeature.h"

#include <iostream>

#include "LocalSettings.h"

using namespace std;
using namespace cv;

OrbFeature::OrbFeature(const string& name)
:	Feature(name)
{
    LoadSettingsFromFileStorage();
}

OrbFeature::~OrbFeature(void)
{
}

void OrbFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ);

    // TODO: Read settings...
}

void OrbFeature::Process(void)
{
	cout << "Thread(" << name_ << "): " << frame_.cols << "x" << frame_.rows << endl;

	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow(name_, frame_);
	waitKey(0);
}
