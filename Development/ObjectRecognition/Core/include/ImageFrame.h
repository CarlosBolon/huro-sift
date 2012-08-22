#pragma once
#pragma warning(disable : 4251) 

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
	ImageFrame(int cameraId);

	//! Destructor.
	~ImageFrame(void);

	//! Gets a frame from somewhere.
	/*!
		\param frame Output argument for the frame.
	*/
	const cv::Mat& GetFrame(void);

private:
	cv::VideoCapture cap_;	//!< Temporary capture for getting frame.
    cv::Mat frame_;
};
