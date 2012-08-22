#include "Feature.h"

using namespace cv;

Feature::Feature(const string& name)
	: name_(name)
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
		Process();
	}

	return reinterpret_cast<void*>(0);
}
