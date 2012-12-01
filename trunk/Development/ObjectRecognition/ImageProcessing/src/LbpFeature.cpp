#include <iostream>

#include "ObjectRecognition\LbpFeature.h"
#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{

LbpFeature::LbpFeature(const string& name, const string& type)
:	GlobalFeature(name, type)
{
    LoadSettingsFromFileStorage();
}

LbpFeature::~LbpFeature(void)
{
}

void LbpFeature::LoadSettingsFromFileStorage(void)
{
    string fileName = LocalSettingsPtr->GetFeatureExtractorDirectory() + "Settings." + name_ + ".xml";
    FileStorage fileStorage(fileName, FileStorage::READ, "UTF-8");

    if(!fileStorage.isOpened())
        CV_Error(1, "Setting XML does not exist for " + name_ + "!");

    string fsUseUniformPatterns;
    fileStorage["useUniformPatterns"] >> fsUseUniformPatterns;

    useUniformPatterns_ = (fsUseUniformPatterns.compare("true") == 0 ? true : false);
}

void LbpFeature::ProcessInit(void)
{
    grayFrame_ = Mat(frame_.rows, frame_.cols, CV_8UC1);
    outputFrame_ = Mat(frame_.rows - 2, frame_.cols - 2, CV_8UC1);

    cvtColor(frame_, grayFrame_, CV_BGR2GRAY, 0);
	equalizeHist(grayFrame_, grayFrame_);
}

void LbpFeature::Process(void)
{
    if(useUniformPatterns_)
    {
        features.resize(944, 0);
        ProcessWithUniformPatterns();
    }
    else
    {
        features.resize(frame_.rows * frame_.cols, 0);
        ProcessWithoutUniformPatterns();
    }
}

void LbpFeature::ProcessWithUniformPatterns(void)
{
    int uniform[58] = {	0,1,2,3,4,6,7,8,12,14,15,16,24,28,30,31,32,48,56,60,62,63,64,96,112,120,124,126,127,128,129,
        131,134,135,140,143,159,191,192,199,207,223,224,225,227,231,239,240,241,243,247,248,249,251,
        252,253,254,255 }; // the uniform patterns that we use in mode 2.

    for(int i = 1; i < frame_.rows-1; i++)
    {
        for(int j = 1; j < frame_.cols-1; j++)
        {
            uchar center = 0;
            uchar lbp_center = grayFrame_.at<uchar>(i,j);

            if(grayFrame_.at<uchar>(i-1, j-1) > lbp_center) center += 128;
            if(grayFrame_.at<uchar>(i-1, j+0) > lbp_center) center += 64;
            if(grayFrame_.at<uchar>(i-1, j+1) > lbp_center) center += 32;
            if(grayFrame_.at<uchar>(i+0, j+1) > lbp_center) center += 16;
            if(grayFrame_.at<uchar>(i+1, j+1) > lbp_center) center += 8;
            if(grayFrame_.at<uchar>(i+1, j+0) > lbp_center) center += 4;
            if(grayFrame_.at<uchar>(i+1, j-1) > lbp_center) center += 2;
            if(grayFrame_.at<uchar>(i+0, j-1) > lbp_center) center += 1;

            outputFrame_.at<uchar>(i-1, j-1) = center;
            // ----------------------------------------------------------------------------------------
            // Filling the LBP vector with frequency values: the picture is divided into 16 partitions.

            int r = i/16;
            int c = j/16;
            int tmp = 0;
            
            if ((r == 0) && (c == 0)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1]++; tmp = 1;}
                }
                if (tmp == 0) features[0]++;
            }	
            else if ((r == 0) && (c == 1)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+59]++;
            }	
            else if ((r == 0) && (c == 2)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+2*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+2*59]++;
            }	
            else if ((r == 0) && (c == 3)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+3*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+3*59]++;
            }	
            else if ((r == 1) && (c == 0)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+4*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+4*59]++;
            }	
            else if ((r == 1) && (c == 1)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+5*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+5*59]++;
            }	
            else if ((r == 1) && (c == 2)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+6*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+6*59]++;
            }	
            else if ((r == 1) && (c == 3)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+7*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+7*59]++;
            }	
            else if ((r == 2) && (c == 0)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+8*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+8*59]++;
            }	
            else if ((r == 2) && (c == 1)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+9*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+9*59]++;
            }	
            else if ((r == 2) && (c == 2)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+10*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+10*59]++;
            }	
            else if ((r == 2) && (c == 3)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+11*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+11*59]++;
            }	
            else if ((r == 3) && (c == 0)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+12*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+12*59]++;
            }	
            else if ((r == 3) && (c == 1)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+13*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+13*59]++;
            }	
            else if ((r == 3) && (c == 2)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+14*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+14*59]++;
            }	
            else if ((r == 3) && (c == 3)){
                for(int i = 0; i < 58; i++){
                    if (uniform[i] == center) {features[i+1+15*59]++; tmp = 1;}
                }
                if (tmp == 0) features[0+15*59]++;
            }
        }
    }    
}

void LbpFeature::ProcessWithoutUniformPatterns(void)
{
    for(int i = 1; i < frame_.rows-1; i++)
    {
        for(int j = 1; j < frame_.cols-1; j++)
        {
            uchar center = 0;
            uchar lbp_center = grayFrame_.at<uchar>(i,j);

            if(grayFrame_.at<uchar>(i-1, j-1) > lbp_center) center += 128;
            if(grayFrame_.at<uchar>(i-1, j+0) > lbp_center) center += 64;
            if(grayFrame_.at<uchar>(i-1, j+1) > lbp_center) center += 32;
            if(grayFrame_.at<uchar>(i+0, j+1) > lbp_center) center += 16;
            if(grayFrame_.at<uchar>(i+1, j+1) > lbp_center) center += 8;
            if(grayFrame_.at<uchar>(i+1, j+0) > lbp_center) center += 4;
            if(grayFrame_.at<uchar>(i+1, j-1) > lbp_center) center += 2;
            if(grayFrame_.at<uchar>(i+0, j-1) > lbp_center) center += 1;

            outputFrame_.at<uchar>(i-1, j-1) = center;
            // ----------------------------------------------------------------------------------------
            // Filling the LBP vector with frequency values: the picture is divided into 16 partitions.

            int r = i/16;
            int c = j/16;

            features[center + (r * 4 + c) * 256]++; 
        }
    }
}

void LbpFeature::DrawFeatures(void)
{
}

}
