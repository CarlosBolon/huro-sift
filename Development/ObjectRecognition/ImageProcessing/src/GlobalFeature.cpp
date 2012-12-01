#include "ObjectRecognition\GlobalFeature.h"
#include "ObjectRecognition\Visualizer.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{

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

	if(frame_.channels() != 3)
		cvtColor(frame_, frame_, CV_GRAY2BGR);

    features.clear();
}

void* GlobalFeature::Run(void)
{
	procTime_ = (double)cvGetTickCount();
	if(!frame_.empty())
	{
        ProcessInit();
		Process();
		DrawFeatures();
	}
	procTime_ = (double)cvGetTickCount() - procTime_;

	return reinterpret_cast<void*>(0);
}


void GlobalFeature::Visualize(void)
{
    stringstream ss;

    ss << "Processing time of " << name_ << ": " << procTime_ / (cvGetTickFrequency() * 1000.0);
    VisualizerPtr->PutText(frame_, ss.str(), Point(10, 20));
    ss.str("");

    ss << "Number of features: " << features.size();
    VisualizerPtr->PutText(frame_, ss.str(), Point(10, 40));
    ss.str("");

    VisualizerPtr->ShowImage(name_, outputFrame_);
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

}
