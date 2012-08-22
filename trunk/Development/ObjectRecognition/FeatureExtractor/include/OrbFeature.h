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
		\sa Feature::Visualize()
	*/
	void Visualize(void);

	cv::ORB* orb;	//!< Wrapped OpenCV SURF object.
};

