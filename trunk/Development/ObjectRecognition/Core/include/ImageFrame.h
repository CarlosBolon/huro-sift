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
	/*!
		\param cameraId ID of the camera.
	*/
    ImageFrame(int cameraId);

    //! Constructor.
	/*!
		\param imageName Name of the image, which from the features will be extracted.
	*/
    ImageFrame(const std::string& imageName);

	//! Destructor.
	~ImageFrame(void);

	//! Gets a frame from somewhere.
	/*!
		\return frame Output argument for the frame.
	*/
	const cv::Mat& GetFrame(void);

private:
	cv::VideoCapture cap_;	//!< Temporary capture for getting frame.
    cv::Mat frame_;			//!< Loaded or captured image.
};
