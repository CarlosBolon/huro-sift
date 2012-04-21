#include "SiftFeature.h"

#include <windows.h>
#include <iostream>

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(int id, cv::Mat& frame)
:	id_(id)
{
	frame_ = frame.clone();
}

SiftFeature::~SiftFeature(void)
{
}

void* SiftFeature::Run() 
{
	cout << "Thread " << id_ << " is running!" << endl;

	Sleep(id_);

	imshow("Thread" + id_, frame_);
	waitKey(1);

	return reinterpret_cast<void*>(id_);
}
