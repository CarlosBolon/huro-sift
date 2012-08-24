#pragma once

#include "GlobalFeature.h"

//! Class for extracting ORB features.
/*!
	\ingroup FeatureExtractor

	Class implementing the ORB (oriented BRIEF) keypoint detector and descriptor extractor. The algorithm uses FAST in pyramids to detect stable keypoints, selects the strongest features using FAST or Harris response, finds their orientation using first-order moments and computes the descriptors using BRIEF (where the coordinates of random point pairs (or k-tuples) are rotated according to the measured orientation).

	See paper:
	Ethan Rublee, Vincent Rabaud, Kurt Konolige, Gary R. Bradski: ORB: An efficient alternative to SIFT or SURF. ICCV 2011: 2564-2571.
*/
extern "C++" class __declspec(dllexport) OrbFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	OrbFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~OrbFeature(void);

	//! Implemented virtual method for loading algorithm specific settings from the given storage.
	/*!
		\sa GlobalFeature::LoadSettingsFromFileStorage()
	*/
	void LoadSettingsFromFileStorage(void);

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa GlobalFeature::Process()
	*/
	void Process(void);

	//! Implemented virtual method for displaying the output.
	/*!
		\sa GlobalFeature::DrawFeatures()
	*/
	void DrawFeatures(void);

	cv::OrbFeatureDetector* orbDetector_;	//!< Wrapped OpenCV ORB object.

    int		nFeatures_;		//!< The maximum number of features to retain.
    float	scaleFactor_;	//!< Pyramid decimation ratio, greater than 1. scaleFactor==2 means the classical pyramid, where each next level has 4x less pixels than the previous, but such a big scale factor will degrade feature matching scores dramatically. On the other hand, too close to 1 scale factor will mean that to cover certain scale range you will need more pyramid levels and so the speed will suffer.
    int		nlevels_;		//!< The number of pyramid levels. The smallest level will have linear size equal to input_image_linear_size/pow(scaleFactor, nlevels).
    int		edgeThreshold_;	//!< This is size of the border where the features are not detected. It should roughly match the patchSize parameter.
    int		firstLevel_;	//!< It should be 0 in the current implementation.
    int		wtaK_;			//!< The number of points that produce each element of the oriented BRIEF descriptor. The default value 2 means the BRIEF where we take a random point pair and compare their brightnesses, so we get 0/1 response. Other possible values are 3 and 4. For example, 3 means that we take 3 random points (of course, those point coordinates are random, but they are generated from the pre-defined seed, so each element of BRIEF descriptor is computed deterministically from the pixel rectangle), find point of maximum brightness and output index of the winner (0, 1 or 2). Such output will occupy 2 bits, and therefore it will need a special variant of Hamming distance, denoted as NORM_HAMMING2 (2 bits per bin). When WTA_K=4, we take 4 random points to compute each bin (that will also occupy 2 bits with possible values 0, 1, 2 or 3).
    int		scoreType_;		//!< he default HARRIS_SCORE means that Harris algorithm is used to rank features (the score is written to KeyPoint::score and is used to retain best nfeatures features); FAST_SCORE is alternative value of the parameter that produces slightly less stable keypoints, but it is a little faster to compute.
    int		patchSize_;		//!< Size of the patch used by the oriented BRIEF descriptor. Of course, on smaller pyramid layers the perceived image area covered by a feature will be larger.
};
