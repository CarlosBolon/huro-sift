#pragma once

#include "GlobalFeature.h"

//! Class for extracting FAST features.
/*!
	\ingroup FeatureExtractor

	Detects corners using the FAST algorithm.

    See paper:
    E. Rosten. Machine Learning for High-speed Corner Detection, 2006.
*/
extern "C++" class __declspec(dllexport) FastFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	FastFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~FastFeature(void);

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

	cv::FastFeatureDetector* fastDetector_;	//!< Wrapped OpenCV FAST object.

    int threshold_;             //!< Threshold on difference between intensity of the central pixel and pixels on a circle around this pixel.
    bool nonmaxSuppression_;    //!< If it is true, non-maximum suppression is applied to detected corners (keypoints).
};
