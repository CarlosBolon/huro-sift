#include "OrbFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

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
	// TODO: implement.
}

void OrbFeature::Visualize(void)
{
	circle(frame_, Point(frame_.cols / 2, frame_.rows / 2), 10, Scalar(255, 0, 0), -1);
	VisualizerPtr->ShowImage(name_, frame_);
}
