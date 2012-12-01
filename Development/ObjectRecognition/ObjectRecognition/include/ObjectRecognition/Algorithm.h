#pragma once
#pragma warning(disable: 4251)

#include "opencv2/opencv.hpp"

namespace ObjectRecognition
{

class GlobalFeature;
class LocalFeature;
class Thread;

typedef std::map<std::string, GlobalFeature*> GlobalFeaturePool;
typedef std::map<std::string, LocalFeature*> LocalFeaturePool;
typedef std::map<std::string, Thread*> ThreadPool;

class Algorithm
{
public:
	Algorithm(void);
	~Algorithm(void);

	void Process(void);

private:
    //! Method for loading algorithm specific settings from the given storage.
	/*!
		\param fileStorage An already open storage from which anything specific can be read.
	*/
	void LoadSettingsFromFileStorage(void);
    void StartFeatureExtractors(void);
    void VisualizeProcesses(void);

	ThreadPool			threadPool_;
    GlobalFeaturePool   globalFeaturePool_;	    //!< Stores all global feature extractor.   
    LocalFeaturePool    localFeaturePool_;      //!< Stores all local feature extractor.

    int cameraId_;				//!< ID of the camera to be analyzed.
	std::string fileName_;
    cv::Size resolution_;
    std::vector<cv::KeyPoint> keyPoints_;

	cv::VideoCapture videoCapture_;
	cv::Mat frame_;
};

}
