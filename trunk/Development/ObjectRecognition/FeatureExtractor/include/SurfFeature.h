#pragma once

#include "Feature.h"

//! Class for extracting SURF features.
/*!
	\ingroup FeatureExtractor

	The class implements SURF algorithm by H. Bay et al.
*/
extern "C++" class __declspec(dllexport) SurfFeature : public Feature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
	*/
	SurfFeature(const std::string& name);

	//! Destructor.
	~SurfFeature(void);

	//! Implemented virtual method for loading algorithm specific settings from the given storage.
	/*!
		\sa Feature::LoadSettingsFromFileStorage()
	*/
	void LoadSettingsFromFileStorage(const cv::FileStorage& fileStorage);

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa Feature::Process()
	*/
	void Process(void);

	//! Implemented virtual method for feature point detection.
	void detectImpl(void);

	cv::SURF* surf;	//!< Wrapped OpenCV SURF object.
};

