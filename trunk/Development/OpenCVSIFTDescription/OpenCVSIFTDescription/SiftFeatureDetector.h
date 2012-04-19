#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "SIFT.h"
#include "FeatureDetector.h"

class KeyPoint;

extern "C++" class __declspec(dllexport)  SiftFeatureDetector : public FeatureDetector
{
public:
	SiftFeatureDetector( const SIFT::DetectorParams& detectorParams=SIFT::DetectorParams(),
		const SIFT::CommonParams& commonParams=SIFT::CommonParams() );
	SiftFeatureDetector( double threshold, double edgeThreshold,
		int nOctaves=SIFT::CommonParams::DEFAULT_NOCTAVES,
		int nOctaveLayers=SIFT::CommonParams::DEFAULT_NOCTAVE_LAYERS,
		int firstOctave=SIFT::CommonParams::DEFAULT_FIRST_OCTAVE,
		int angleMode=SIFT::CommonParams::FIRST_ANGLE );
	virtual void read( const cv::FileNode& fn );
	virtual void write( cv::FileStorage& fs ) const;

protected:
	virtual void detectImpl( const cv::Mat& image, std::vector<KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const;

	SIFT sift;
};