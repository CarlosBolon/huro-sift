#pragma once
#pragma warning(disable : 4251) 

#include "opencv2/opencv.hpp"

/*!
	\defgroup ObjectRecognition Object Recognition module.
*/

class GlobalFeature;
class LocalFeature;
class ImageFrame;

typedef std::map<std::string, GlobalFeature*> GlobalFeaturePool;
typedef std::map<std::string, LocalFeature*> LocalFeaturePool;

//! Class for handling feature extraction.
/*!
	\ingroup ObjectRecognition

	Getting Local and Global Features.
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

    GlobalFeaturePool   globalFeaturePool_;	    //!< Stores all global feature extractor.   
    LocalFeaturePool    localFeaturePool_;      //!< Stores all local feature extractor.
	ImageFrame*         imageFrame_;	        //!< For handling image frame getting.

	std::string mediaType_;		//!< Type of the incoming media.
	std::string imageName_;		//!< Name of the image to be analyzed.
	int cameraId_;				//!< ID of the camera to be analyzed.
};
