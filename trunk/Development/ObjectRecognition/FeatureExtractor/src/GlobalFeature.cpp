#include "GlobalFeature.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

GlobalFeature::GlobalFeature(const string& name, const string& type)
:	name_(name),
    type_(type),
	procTime_(0.0)
{
}

GlobalFeature::~GlobalFeature(void)
{
}

void GlobalFeature::SetFrame(const Mat& frame)
{
	frame_ = frame.clone();
}

void* GlobalFeature::Run(void)
{
	if(!frame_.empty())
	{
		procTime_ = (double)cvGetTickCount();
		Process();
		procTime_ = (double)cvGetTickCount() - procTime_;

		DrawFeatures();
        Visualize();
	}

	return reinterpret_cast<void*>(0);
}


void GlobalFeature::Visualize(void)
{
    char buffer[500];

    sprintf_s(buffer, 500, "Processing time of %s: %.2lf ms.", name_.c_str(), procTime_ / (cvGetTickFrequency() * 1000.0));
    VisualizerPtr->PutText(frame_, buffer, Point(10, 20));

    sprintf_s(buffer, 500, "Number of detected keypoints: %d.", keyPoints.size());
    VisualizerPtr->PutText(frame_, buffer, Point(10, 40));

    VisualizerPtr->ShowImage(name_, frame_);
}


const string& GlobalFeature::GetName(void)
{
    return name_;
}

const string& GlobalFeature::GetType(void)
{
    return type_;
}

double GlobalFeature::GetProcTime(void)
{
    return procTime_;
}
