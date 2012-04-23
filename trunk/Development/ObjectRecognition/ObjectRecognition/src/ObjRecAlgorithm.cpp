#include "ObjRecAlgorithm.h"

#include <iostream>
#include "opencv2/opencv.hpp"

#include "SiftFeature.h"
#include "ExceptionDescriptor.h"
#include "LocalSettings.h"
#include "ImageFrame.h"

using namespace std;
using namespace cv;

ObjRecAlgorithm::ObjRecAlgorithm(void)
{
	siftFeature_ = new SiftFeature("SIFT");
	imageFrame_ = new ImageFrame();
}

ObjRecAlgorithm::~ObjRecAlgorithm(void)
{
	delete siftFeature_;
	delete imageFrame_;
}

void ObjRecAlgorithm::Process(void)
{
	Mat frame;

	imageFrame_->GetFrame(frame);

	siftFeature_->SetFrame(frame);

	siftFeature_->Start();

	int result1 = reinterpret_cast<int>(siftFeature_->Join());
}
