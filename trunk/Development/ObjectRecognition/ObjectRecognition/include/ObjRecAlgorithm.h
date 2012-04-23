#pragma once

/*!
	\defgroup ObjectRecognition Object Recognition module.
*/

class Feature;
class ImageFrame;

//! Class for Object Recognition.
/*!
	\ingroup ObjectRecognition

	Object Recognition from Local and Global Features.
*/
extern "C++" class __declspec(dllexport) ObjRecAlgorithm
{
public:
	//! Constructor.
	ObjRecAlgorithm(void);

	//! Destructor.
	~ObjRecAlgorithm(void);

	//! Main algorithm.
	void Process(void);

private:
	//! Pass the frames to the feature extractors.
	void SetFrames(void);

	//! Starts all of the feature extractors.
	void StartFeatureExtractors(void);

	Feature* siftFeature_;		//!< For extracting SIFT features.
	Feature* surfFeature_;		//!< For extracting SURF features.
	Feature* orbFeature_;		//!< For extracting ORB features.	
	Feature* starFeature_;		//!< For extracting STAR features.

	ImageFrame* imageFrame_;	//!< For handling image frame getting.
};

