#include "SiftFeature.h"

#include <windows.h>
#include <iostream>

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(int id, cv::Mat& frame)
:	id_(id)//,
	//updateMutex(PTHREAD_MUTEX_INITIALIZER)
{
	frame_ = frame.clone();
	//pthread_mutex_init(&updateMutex, NULL);
}

SiftFeature::~SiftFeature(void)
{
	//pthread_mutex_destroy(&updateMutex);
}

void* SiftFeature::Run() 
{
	cout << "Thread " << id_ << " is running!" << endl;
	cout << frame_.cols << ", " << frame_.rows << endl;

	//pthread_mutex_lock(&updateMutex);
	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	imshow("Thread" + id_, frame_);
	waitKey(0);
	//pthread_mutex_unlock(&updateMutex);


	Sleep(1);

	return reinterpret_cast<void*>(id_);
}
