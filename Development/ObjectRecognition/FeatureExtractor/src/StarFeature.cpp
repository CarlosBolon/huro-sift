#include "StarFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

StarFeature::StarFeature(const string& name)
:	Feature(name)
{
    LoadSettingsFromFileStorage();
}

StarFeature::~StarFeature(void)
{
}

void StarFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ);

    // TODO: Read settings...
}

void StarFeature::Process(void)
{
	// TODO: implement.
}

void StarFeature::Visualize(void)
{
	circle(frame_, Point(frame_.cols / 2, frame_.rows / 2), 10, Scalar(255, 0, 0), -1);
	VisualizerPtr->ShowImage(name_, frame_);
}
