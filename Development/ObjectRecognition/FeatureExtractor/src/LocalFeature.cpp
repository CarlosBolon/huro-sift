#include "LocalFeature.h"
#include "Visualizer.h"

using namespace std;
using namespace cv;

LocalFeature::LocalFeature(const string& name, const string& type)
:	name_(name),
    type_(type),
    procTime_(0.0)
{
}

LocalFeature::~LocalFeature(void)
{
}

void LocalFeature::SetFrame(const Mat& frame)
{
    frame_ = frame.clone();
}

void* LocalFeature::Run(void)
{
    if(!frame_.empty())
    {
        ProcessInit();

        procTime_ = (double)cvGetTickCount();
        Process();
        procTime_ = (double)cvGetTickCount() - procTime_;

        DrawFeatures();
        Visualize();
    }

    return reinterpret_cast<void*>(0);
}


void LocalFeature::Visualize(void)
{
    char buffer[500];

    sprintf_s(buffer, 500, "Processing time of %s: %.2lf ms.", name_.c_str(), procTime_ / (cvGetTickFrequency() * 1000.0));
    VisualizerPtr->PutText(outputFrame_, buffer, Point(10, 20));

    sprintf_s(buffer, 500, "Number of features: %d.", features.size());
    VisualizerPtr->PutText(outputFrame_, buffer, Point(10, 40));

    VisualizerPtr->ShowImage(name_, outputFrame_);
}


const string& LocalFeature::GetName(void)
{
    return name_;
}

const string& LocalFeature::GetType(void)
{
    return type_;
}

double LocalFeature::GetProcTime(void)
{
    return procTime_;
}
