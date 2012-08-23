#pragma once
#pragma warning(disable : 4251)

#include <string>

#include "opencv2/opencv.hpp"

#define VisualizerPtr Visualizer::GetInstance()

//! Singleton window and image display manager class.
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

	//! Creates a window and show an image within it.
	/*!
		\param name Name of the window.
		\param image Image to be shown.
		\param waitForKey Waits for a pressed key.
	*/
    void ShowImage(const std::string& name, const cv::Mat& image, bool waitForKey = true);

	//! Renders the specified text string in the image.
	/*!
		\param image Image.
		\param text Text string to be drawn.
		\param org Bottom-left corner of the text string in the image.
	*/
    void PutText(cv::Mat& image, const std::string& text, cv::Point& org);

	//! Sets the text's properties.
	/*!
		\param fontFace Font type.
		\param fontScale Font scale factor that is multiplied by the font-specific base size.
		\param fontColor Text color.
		\param fontThickness Thickness of the lines used to draw a text.
	*/
    void SetTextProperties(int fontFace, double fontScale, cv::Scalar fontColor, int fontThickness);

private:
    //! Constructor.
    Visualizer(void);

    //! Destructor.
    ~Visualizer(void);

    int fontFace_;			//!< Font type.
    double fontScale_;		//!< Font scale factor that is multiplied by the font-specific base size.
    cv::Scalar fontColor_;	//!< Text color.
    int fontThickness_;		//!< Thickness of the lines used to draw a text.
};
