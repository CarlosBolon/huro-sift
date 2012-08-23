#pragma once
#pragma warning(disable : 4251)

#include <string>

#include "opencv2/opencv.hpp"

#define VisualizerPtr Visualizer::GetInstance()

//! Singleton window manager class.
/*!
	\ingroup Core
*/
extern "C++" class __declspec(dllexport) Visualizer
{
public:
    //! Instance getter.
	/*!
		\return The instance.
	*/
	static Visualizer* GetInstance(void);

    void ShowImage(const std::string& name, const cv::Mat& image, bool waitForKey = true);

    void PutText(cv::Mat& image, const std::string& text, cv::Point& org);

    void SetTextProperties(int fontFace, double fontScale, cv::Scalar fontColor, int fontThickness);

private:
    //! Constructor.
    Visualizer(void);

    //! Destructor.
    ~Visualizer(void);

    int fontFace_;
    double fontScale_;
    cv::Scalar fontColor_;
    int fontThickness_;
};
