#pragma once

#include "opencv2/opencv.hpp"

//! Image frame wrapper class.
/*!
	\ingroup Core

	Gets image frames as cv::Mat objects.
*/
extern "C++" class __declspec(dllexport) ImageFrame 
{
public:
	//! Constructor.
	ImageFrame(void);

	//! Destructor.
	~ImageFrame(void);

	//! Gets a frame from somewhere.
	/*!
		\param frame Output argument for the frame.
	*/
	void GetFrame(cv::Mat& frame);

private:
	cv::VideoCapture cap_;	//!< Temporary capture for getting frame.
};
