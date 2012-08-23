#pragma once

#include "Feature.h"

//! Class for extracting MSER features.
/*!
	\ingroup FeatureExtractor

	The class implements Maximally-Stable Extremal Region Extractor algorithm.
    The class encapsulates all the parameters of MSER (see http://en.wikipedia.org/wiki/Maximally_stable_extremal_regions ) extraction algorithm.
*/
extern "C++" class __declspec(dllexport) MserFeature : public Feature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
	*/
	MserFeature(const std::string& name);

	//! Destructor.
	~MserFeature(void);

	//! Implemented virtual method for loading algorithm specific settings from the given storage.
	/*!
		\sa Feature::LoadSettingsFromFileStorage()
	*/
	void LoadSettingsFromFileStorage(void);

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa Feature::Process()
	*/
	void Process(void);

	//! Implemented virtual method for displaying the output.
	/*!
		\sa Feature::DrawFeatures()
	*/
	void DrawFeatures(void);

	cv::MserFeatureDetector* mserDetector_;	//!< Wrapped OpenCV MSER object.

    int delta_;
    int minArea_;
    int maxArea_;
    double maxVariation_;
    double minDiversity_;
    int maxEvolution_;
    double areaThreshold_;
    double minMargin_;
    int edgeBlurSize_;
};

