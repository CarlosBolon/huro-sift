#include "FastFeature.h"

#include <iostream>

#include "LocalSettings.h"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

FastFeature::FastFeature(const string& name, const string& type)
:	GlobalFeature(name, type)
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
    string fileName = LocalSettingsPtr->GetSettingsDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

    if(!fileStorage.isOpened())
        throw ExceptionError("Setting XML does not exist for " + name_ + "!");

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
    drawKeypoints(frame_, keyPoints, frame_, Scalar::all(-1), DrawMatchesFlags::DEFAULT); 
}
