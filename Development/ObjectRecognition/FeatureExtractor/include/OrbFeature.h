#pragma once

#include "Feature.h"

//! Class for extracting ORB features.
/*!
	\ingroup FeatureExtractor

	The class implements "Oriented FAST and Rotated BRIEF" ORB algorithm.
*/
extern "C++" class __declspec(dllexport) OrbFeature : public Feature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
	*/
	OrbFeature(const std::string& name);

	//! Destructor.
	~OrbFeature(void);

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

	cv::OrbFeatureDetector* orbDetector_;	//!< Wrapped OpenCV ORB object.

    int nFeatures_;
    float scaleFactor_;
    int nlevels_; 
    int edgeThreshold_;
    int firstLevel_;
    int wtaK_;
    int scoreType_;
    int patchSize_;
};
