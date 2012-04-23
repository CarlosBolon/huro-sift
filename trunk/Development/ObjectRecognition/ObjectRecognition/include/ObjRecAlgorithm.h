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
	Feature* siftFeature_;		//!< For extracting SIFT features.
	ImageFrame* imageFrame_;	//!< For handling image frame getting.
};

