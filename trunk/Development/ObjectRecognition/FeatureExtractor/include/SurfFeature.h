#pragma once

#include "GlobalFeature.h"

//! Class for extracting SURF features.
/*!
	\ingroup FeatureExtractor

	Class for extracting Speeded Up Robust Features from an image.

	See paper:
	Bay, H. and Tuytelaars, T. and Van Gool, L. “SURF: Speeded Up Robust Features”, 9th European Conference on Computer Vision, 2006.
*/
extern "C++" class __declspec(dllexport) SurfFeature : public GlobalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	SurfFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~SurfFeature(void);

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

	cv::SurfFeatureDetector* surfDetector_;	//!< Wrapped OpenCV SURF object.

    double  hessianThreshold_;	//!< Threshold for the keypoint detector. Only features, whose hessian is larger than hessianThreshold are retained by the detector. Therefore, the larger the value, the less keypoints you will get. A good default value could be from 300 to 500, depending from the image contrast.
    int     octaves_;			//!< The number of a gaussian pyramid octaves that the detector uses. It is set to 4 by default. If you want to get very large features, use the larger value. If you want just small features, decrease it.
    int     octaveLayers_;		//!< The number of images within each octave of a gaussian pyramid. It is set to 2 by default.
	bool    extended_;			//!< False means that the basic descriptors (64 elements each) shall be computed. True means that the extended descriptors (128 elements each) shall be computed.
	bool    upright_;			//!< False means that detector computes orientation of each feature. True means that the orientation is not computed (which is much, much faster). For example, if you match images from a stereo pair, or do image stitching, the matched features likely have very similar angles, and you can speed up feature extraction by setting upright=true.
};

