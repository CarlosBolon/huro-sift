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
extern "C++" class __declspec(dllexport) Algorithm
{
public:
	//! Constructor.
	Algorithm(void);

	//! Destructor.
	~Algorithm(void);

	//! Main algorithm.
	void Process(void);

private:
    void ProcessInit(void);

    FeaturePool featurePool_;
	ImageFrame* imageFrame_;	//!< For handling image frame getting.
};

