#include "Feature.h"
#include "Visualizer.h"

#define GETTICKCOUNT        (double)cvGetTickCount()
#define GETTICKFREQUENCY    cvGetTickFrequency()

using namespace std;
using namespace cv;

Feature::Feature(const string& name)
:	name_(name),
	procTime_(0.0)
{
}

Feature::~Feature(void)
{
}

void Feature::SetFrame(const Mat& frame)
{
	frame_ = frame.clone();

    keyPoints.clear();
    procTime_ = 0.0;
    descriptors = Mat();
}

void* Feature::Run(void)
{
	if(!frame_.empty())
	{
		procTime_ = GETTICKCOUNT;
		Process();
		procTime_ = GETTICKCOUNT - procTime_;

		DrawFeatures();
        Visualize();
	}

	return reinterpret_cast<void*>(0);
}

void Feature::Visualize(void)
{
    char buffer[500];
    sprintf_s(buffer, 500, "Processing time of %s: %.2lf ms.", name_.c_str(), procTime_ / (GETTICKFREQUENCY * 1000.0));
    VisualizerPtr->PutText(frame_, buffer, Point(10, 20));

    sprintf_s(buffer, 500, "Number of detected keypoints: %d.", keyPoints.size());
    VisualizerPtr->PutText(frame_, buffer, Point(10, 40));

    VisualizerPtr->ShowImage(name_, frame_);
}
