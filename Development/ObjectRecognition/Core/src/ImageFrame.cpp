#include "ImageFrame.h"

#include "ExceptionDescriptor.h"

using namespace cv;

ImageFrame::ImageFrame(int cameraId = 0)
{
	cap_.open(cameraId);

	if(!cap_.isOpened())
		throw ExceptionError("Capture is not opened!");
}

ImageFrame::~ImageFrame(void)
{

}

const Mat& ImageFrame::GetFrame(void)
{
	cap_ >> frame_;

	if(frame_.empty())
		throw ExceptionError("Frame is empty!");

    return frame_;
}
