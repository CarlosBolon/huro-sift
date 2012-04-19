#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "SURF.h"
#include "FeatureDetector.h"

class KeyPoint;

extern "C++" class __declspec(dllexport) SurfFeatureDetector : public FeatureDetector
{
public:
	SurfFeatureDetector( double hessianThreshold=400., int octaves=3, int octaveLayers=4, bool upright=false );
	virtual void read( const cv::FileNode& fn );
	virtual void write( cv::FileStorage& fs ) const;

protected:
	virtual void detectImpl( const cv::Mat& image, std::vector<KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const;

	SURF surf;
};