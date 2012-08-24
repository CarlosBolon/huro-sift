#pragma once

#include "GlobalFeature.h"

//! Class for extracting SIFT features.
/*!
	\ingroup FeatureExtractor

	Class for extracting keypoints and computing descriptors using the Scale Invariant Feature Transform (SIFT) algorithm by D. Lowe.

	See paper:
	Lowe, D. G., “Distinctive Image Features from Scale-Invariant Keypoints”, International Journal of Computer Vision, 60, 2, pp. 91-110, 2004.
*/
extern "C++" class __declspec(dllexport) SiftFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	SiftFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~SiftFeature(void);

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

	cv::SiftFeatureDetector* siftDetector_;	//!< Wrapped OpenCV SIFT object.

    int		nfeatures_;			//!< The number of best features to retain. The features are ranked by their scores (measured in SIFT algorithm as the local contrast).
    int		nOctaveLayers_;		//!< The number of layers in each octave. 3 is the value used in D. Lowe paper. The number of octaves is computed automatically from the image resolution.
    double	contrastThreshold_;	//!< The contrast threshold used to filter out weak features in semi-uniform (low-contrast) regions. The larger the threshold, the less features are produced by the detector.
    double	edgeThreshold_;		//!< The threshold used to filter out edge-like features. Note that the its meaning is different from the contrastThreshold, i.e. the larger the edgeThreshold, the less features are filtered out (more features are retained).
    double	sigma_;				//!< The sigma of the Gaussian applied to the input image at the octave #0. If your image is captured with a weak camera with soft lenses, you might want to reduce the number.
};

