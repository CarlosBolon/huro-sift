#include "SiftFeature.h"

//#include <windows.h>
#include <iostream>

using namespace std;
using namespace cv;

SiftFeature::SiftFeature(int id)
:	Feature(id)
{
}

SiftFeature::~SiftFeature(void)
{
}

void SiftFeature::LoadSettingsFromFileStorage(const FileStorage& fileStorage)
{
}

void SiftFeature::Process(void)
{
	cout << frame_.cols << ", " << frame_.rows << endl;
	//string str = "Thread1111 " + id_;
	circle(frame_, Point(100, 100), 10, Scalar(255, 0, 0), -1);
	//imshow(str, frame_);
	//waitKey(0);
}
