#pragma once

#include "GlobalFeature.h"

//! Class for extracting STAR features.
/*!
	\ingroup FeatureExtractor

	Class implementing the Star keypoint detector, a modified version of the CenSurE keypoint detector described in
	Agrawal, M. and Konolige, K. and Blas, M.R. “CenSurE: Center Surround Extremas for Realtime Feature Detection and Matching”, ECCV08, 2008.
*/
extern "C++" class __declspec(dllexport) StarFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	StarFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~StarFeature(void);

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

	cv::StarFeatureDetector* starDetector_;	//!< Wrapped OpenCV STAR object.

	int maxSize_;					//!< Maximum size of the features. The following values of the parameter are supported: 4, 6, 8, 11, 12, 16, 22, 23, 32, 45, 46, 64, 90, 128.
	int responseThreshold_;			//!< Threshold for the approximated laplacian, used to eliminate weak features. The larger it is, the less features will be retrieved.
	int lineThresholdProjected_;	//!< Another threshold for the laplacian to eliminate edges.
	int lineThresholdBinarized_;	//!< Another threshold for the feature size to eliminate edges.
    int suppressNonmaxSize_;		//!< Window size (n-by-n) to apply the non-maximal suppression. Increasing the window size remove feature points that are close to each other.
};

