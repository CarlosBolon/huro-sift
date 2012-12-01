#pragma once
#pragma warning(disable: 4251)

#include <memory>
#include "opencv2/opencv.hpp"

namespace ObjectRecognition
{

#define DEBUG_MODE 1

class GlobalFeature;
class LocalFeature;
class Thread;

typedef std::map<std::string, GlobalFeature*> GlobalFeaturePool;
typedef std::map<std::string, LocalFeature*> LocalFeaturePool;
typedef std::map<std::string, Thread*> ThreadPool;

extern "C++" class __declspec(dllexport) Algorithm
{
public:
	enum WorkMode
	{
		WORK_MODE_TRAIN = 0,
		WORK_MODE_TEST
	};

	Algorithm(void);
	~Algorithm(void);

	void Process(void);

private:
    //! Method for loading algorithm specific settings from the given storage.
	/*!
		\param fileStorage An already open storage from which anything specific can be read.
	*/
	void LoadSettingsFromFileStorage(void);

	bool ReadStringList(const std::string& filename);

	bool GrabFrame(cv::Mat& frame);

    void StartFeatureExtractors(const cv::Mat& frame);

    void VisualizeProcesses(void);

	void SaveData(void);

	ThreadPool			threadPool_;
    GlobalFeaturePool   globalFeaturePool_;	    //!< Stores all global feature extractor.   
    LocalFeaturePool    localFeaturePool_;      //!< Stores all local feature extractor.

	cv::VideoCapture videoCapture_;
	std::vector<std::string> imageList_;

	struct Detail;
	std::unique_ptr<Detail> detail_;
};

}
