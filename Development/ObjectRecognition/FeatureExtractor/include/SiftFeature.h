#pragma once

/*!
	\defgroup FeatureExtractor FeatureExtractor module.
*/

#include "Feature.h"

//! Class for extracting SIFT features.
/*!
	\ingroup FeatureExtractor
*/
extern "C++" class __declspec(dllexport) SiftFeature : public Feature
{
public:
	//! Constructor.
	/*!
		\param id
		\param frame
	*/
	SiftFeature(int id);

	//! Destructor.
	~SiftFeature(void);

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
};

