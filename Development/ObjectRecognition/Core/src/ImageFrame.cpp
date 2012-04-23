#include "ImageFrame.h"

#include "ExceptionDescriptor.h"

using namespace cv;

ImageFrame::ImageFrame(void)
{
	cap_.open(1);

	if(!cap_.isOpened())
		throw ExceptionError("Capture is not opened!");
}

ImageFrame::~ImageFrame(void)
{

}

void ImageFrame::GetFrame(Mat& frame)
{
	cap_ >> frame;

	if(frame.empty())
		throw ExceptionError("Frame is empty!");
}
