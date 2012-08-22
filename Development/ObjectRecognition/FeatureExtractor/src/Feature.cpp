#include "Feature.h"

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
}

void* Feature::Run(void)
{
	if(!frame_.empty())
	{
		procTime_ = (double)cvGetTickCount();
		Process();
		procTime_ = (double)cvGetTickCount() - procTime_;

		Visualize();
	}

	return reinterpret_cast<void*>(0);
}
