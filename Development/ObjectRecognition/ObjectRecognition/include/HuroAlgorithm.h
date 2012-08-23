#pragma once
#pragma warning(disable : 4251) 

#include "opencv2/opencv.hpp"

/*!
	\defgroup ObjectRecognition Object Recognition module.
*/

class Feature;
class ImageFrame;

typedef std::map<std::string, Feature*> FeaturePool;

//! Class for Object Recognition.
/*!
	\ingroup ObjectRecognition

	Object Recognition from Local and Global Features.
*/
extern "C++" class __declspec(dllexport) HuroAlgorithm
{
public:
	//! Constructor.
	HuroAlgorithm(void);

	//! Destructor.
	~HuroAlgorithm(void);

	//! Main algorithm.
	void Process(void);

private:
    //! Method for loading algorithm specific settings from the given storage.
	/*!
		\param fileStorage An already open storage from which anything specific can be read.
	*/
	void LoadSettingsFromFileStorage(void);

    FeaturePool featurePool_;
	ImageFrame* imageFrame_;	//!< For handling image frame getting.
};

