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

	cv::SurfFeatureDetector* surfDetector_;	//!< Wrapped OpenCV SURF object.

    double  hessianThreshold_;
    int     octaves_;
    int     octaveLayers_;
    bool    upright_;
};

