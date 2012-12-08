#pragma once
#pragma warning(disable: 4251)

#include <string>
#include <vector>

#include "opencv2/opencv.hpp"

namespace ObjectRecognition
{

extern "C++" class __declspec(dllexport) Matcher
{
public:
    Matcher(const std::string& descriptorType, const std::string& matcherType);
    ~Matcher(void);
        
    void Process(const std::vector<std::string>& imageList, const cv::Mat& queryDescriptors);

    const std::vector<cv::DMatch>& GetMatches(void) const;

private:
    void FillTrainDescriptors(const std::vector<std::string>& imageList);

    std::string descriptorType_;
    std::string matcherType_;
    cv::Ptr<cv::DescriptorMatcher> descriptorMatcher_;
    std::vector<cv::Mat> trainDescriptors_;
    std::vector<cv::DMatch> matches_;
};

}
