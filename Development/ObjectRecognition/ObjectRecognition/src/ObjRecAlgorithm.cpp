#include "ObjRecAlgorithm.h"

#include <iostream>
#include "opencv2/opencv.hpp"

#include "SiftFeature.h"
#include "SurfFeature.h"
#include "OrbFeature.h"
#include "StarFeature.h"

#include "ExceptionDescriptor.h"
#include "LocalSettings.h"
#include "ImageFrame.h"

using namespace std;
using namespace cv;

ObjRecAlgorithm::ObjRecAlgorithm(void)
{
	// TODO: MSER, FAST classes.
	siftFeature_ = new SiftFeature("SIFT");
	surfFeature_ = new SurfFeature("SURF");
	orbFeature_  = new OrbFeature("ORB");
	starFeature_  = new StarFeature("STAR");

	imageFrame_ = new ImageFrame();
}

ObjRecAlgorithm::~ObjRecAlgorithm(void)
{
	delete siftFeature_;
	delete surfFeature_;
	delete orbFeature_;
	delete starFeature_;

	delete imageFrame_;
}

void ObjRecAlgorithm::Process(void)
{
	SetFrames();
	StartFeatureExtractors();

	int resultSift = reinterpret_cast<int>(siftFeature_->Join());
	int resultSurf = reinterpret_cast<int>(surfFeature_->Join());
	int resultOrb = reinterpret_cast<int>(orbFeature_->Join());
	int resultStar = reinterpret_cast<int>(starFeature_->Join());
}

void ObjRecAlgorithm::SetFrames(void)
{
	Mat frame;

	imageFrame_->GetFrame(frame);

	siftFeature_->SetFrame(frame);
	surfFeature_->SetFrame(frame);
	orbFeature_->SetFrame(frame);
	starFeature_->SetFrame(frame);
}

void ObjRecAlgorithm::StartFeatureExtractors(void)
{
	siftFeature_->Start();
	surfFeature_->Start();
	orbFeature_->Start();
	starFeature_->Start();
}
