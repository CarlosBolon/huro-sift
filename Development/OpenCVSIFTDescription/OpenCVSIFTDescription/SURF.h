#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"

class KeyPoint;

extern "C++" class __declspec(dllexport) CvSURFParams
{
protected:
	int    extended;
	int    upright;
	double hessianThreshold;

	int    nOctaves;
	int    nOctaveLayers;

};

/*!
 SURF implementation.
 
 The class implements SURF algorithm by H. Bay et al.
 */
extern "C++" class __declspec(dllexport) SURF : public CvSURFParams
{
public:
    //! the default constructor
    CV_WRAP SURF();
    //! the full constructor taking all the necessary parameters
    CV_WRAP SURF(double _hessianThreshold, int _nOctaves=4,
         int _nOctaveLayers=2, bool _extended=false, bool _upright=false);

    //! returns the descriptor size in float's (64 or 128)
    CV_WRAP int descriptorSize() const;
    //! finds the keypoints using fast hessian detector used in SURF
    CV_WRAP_AS(detect) void operator()(const cv::Mat& img, const cv::Mat& mask,
                    CV_OUT std::vector<KeyPoint>& keypoints) const;
    //! finds the keypoints and computes their descriptors. Optionally it can compute descriptors for the user-provided keypoints
    CV_WRAP_AS(detect) void operator()(const cv::Mat& img, const cv::Mat& mask,
                    CV_OUT std::vector<KeyPoint>& keypoints,
                    CV_OUT std::vector<float>& descriptors,
                    bool useProvidedKeypoints=false) const;
};