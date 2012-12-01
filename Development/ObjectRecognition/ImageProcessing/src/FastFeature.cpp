#include <iostream>

#include "ObjectRecognition\FastFeature.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{


FastFeature::FastFeature(const string& name, const string& type)
:	LocalFeature(name, type)
{
    LoadSettingsFromFileStorage();

    fastDetector_ = new FastFeatureDetector(threshold_, nonmaxSuppression_);
}


FastFeature::~FastFeature(void)
{
    delete fastDetector_;
}


void FastFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetFeatureExtractorDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

    if(!fileStorage.isOpened())
        CV_Error(1, "Setting XML does not exist for " + name_ + "!");

    string fsNonmaxSuppression;
    fileStorage["threshold"] >> threshold_;
    fileStorage["nonmaxSuppression"] >> fsNonmaxSuppression;
   
    nonmaxSuppression_ = (fsNonmaxSuppression.compare("true") == 0 ? true : false);
}


void FastFeature::Process(void)
{
    fastDetector_->detect(frame_, keyPoints);
}


void FastFeature::DrawFeatures(void)
{
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT /*| DrawMatchesFlags::DRAW_RICH_KEYPOINTS*/); 
}


}
