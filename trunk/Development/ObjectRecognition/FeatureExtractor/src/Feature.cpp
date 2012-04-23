#include "Feature.h"

using namespace cv;

Feature::Feature(const string& name)
	: name_(name)
{
}

Feature::~Feature(void)
{
}

void Feature::SetFrame(Mat& frame)
{
	mutex_.Lock();
	frame_ = frame.clone();
	mutex_.Unlock();
}

void* Feature::Run(void)
{
	if(!frame_.empty())
	{
		Process();
	}

	return reinterpret_cast<void*>(0);
}
