#pragma once

#include "GlobalFeature.h"

//! Class for extracting MSER features.
/*!
	\ingroup FeatureExtractor

	The class implements Maximally-Stable Extremal Region Extractor algorithm.
    The class encapsulates all the parameters of MSER (see http://en.wikipedia.org/wiki/Maximally_stable_extremal_regions ) extraction algorithm.
*/
extern "C++" class __declspec(dllexport) MserFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	MserFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~MserFeature(void);

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

	cv::MserFeatureDetector* mserDetector_;	//!< Wrapped OpenCV MSER object.

    int		delta_;			//!< Delta in the code, it compares (size_{i} - size_{i - delta}) / size_{i - delta}.
    int		minArea_;		//!< Prune the area which smaller than minArea.
    int		maxArea_;		//!< Prune the area which bigger than maxArea.
    double	maxVariation_;	//!< Prune the area have simliar size to its children.
    double	minDiversity_;	//!< Trace back to cut off mser with diversity < min_diversity.

	// The next few params for MSER of color image:
    int		maxEvolution_;	//!< For color image, the evolution steps.
    double	areaThreshold_;	//!< The area threshold to cause re-initialize.
    double	minMargin_;		//!< Ignore too small margin.
    int		edgeBlurSize_;	//!< The aperture size for edge blur.
};
