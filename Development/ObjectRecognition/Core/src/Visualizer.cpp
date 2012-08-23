#include "Visualizer.h"

using namespace std;
using namespace cv;

Visualizer::Visualizer(void)
:   fontFace_(FONT_HERSHEY_SIMPLEX),
    fontScale_(0.5),
    fontColor_(Scalar::all(-1)),
    fontThickness_(1)
{
}

Visualizer::~Visualizer(void)
{
}

Visualizer* Visualizer::GetInstance(void)
{
    static Visualizer* visualizer = new Visualizer();
    return visualizer;
}

void Visualizer::ShowImage(const string& name, const Mat& image, bool waitForKey)
{
    imshow(name, image);

    if(waitForKey)
        waitKey(0);
}

void Visualizer::PutText(Mat& image, const string& text, Point& org)
{
    Scalar fgColor = (fontColor_ == Scalar::all(-1) ? Scalar::all(255) : fontColor_);
    Scalar bgColor = (fontColor_ == Scalar::all(-1) ? Scalar::all(0) : 
        Scalar( int(fontColor_[0] + 255) % 255, int(fontColor_[1] + 255) % 255, int(fontColor_[2] + 255) % 255, 0));

    putText(image, text, org, fontFace_, fontScale_, bgColor, fontThickness_ + 1);
    putText(image, text, org, fontFace_, fontScale_, fgColor, fontThickness_);
}

void Visualizer::SetTextProperties(int fontFace, double fontScale, Scalar fontColor, int fontThickness)
{
    fontFace_ = fontFace;
    fontScale_ = fontScale;
    fontColor_ = fontColor;
    fontThickness_ = fontThickness;
}
