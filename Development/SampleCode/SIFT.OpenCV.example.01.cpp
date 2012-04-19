// SIFTMemLeakTest.cpp : main project file.

#include "stdafx.h"

using namespace System;

#include <opencv2\opencv.hpp>
#include <opencv2\features2d\features2d.hpp>

int main(array<System::String ^> ^args)
{
	cv::Mat image;
	image = cv::imread("image.jpg", 0);
    
	cv::SIFT::DetectorParams siftDetectorParams;
	cv::SIFT::CommonParams siftCommonParams;
	cv::SIFT::DescriptorParams siftDescriptorParams;

	// the problem seems to be more prominent when using these parameters
	//cv::SIFT::DetectorParams siftDetectorParams(0.006f, 100.0f);
	//cv::SIFT::CommonParams siftCommonParams(4, 3, -1, 1);
	//cv::SIFT::DescriptorParams siftDescriptorParams(3.0f, true, true);

	cv::SiftFeatureDetector* siftDetector = new cv::SiftFeatureDetector(siftDetectorParams, siftCommonParams);
	cv::SiftDescriptorExtractor* siftDescriptor = new cv::SiftDescriptorExtractor(siftDescriptorParams, siftCommonParams);

	while(true)
	{
		std::vector<cv::KeyPoint> keypoints;
		cv::Mat siftDescriptors;

		siftDetector->detect(image, keypoints);
		siftDescriptor->compute(image, keypoints, siftDescriptors);

		printf("descriptors computed\n");

		keypoints.clear();
		siftDescriptors.release();
	}

    return 0;
}
