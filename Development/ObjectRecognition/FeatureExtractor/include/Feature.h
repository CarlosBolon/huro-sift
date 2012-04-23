#pragma once

/*!
	\defgroup FeatureExtractor FeatureExtractor module.
*/

#include <string>

#include "opencv2/opencv.hpp"

#include "Thread.h"
#include "Mutex.h"

//! Abstract class for feature detection.
/*!
	\ingroup FeatureExtractor
*/
extern "C++" class __declspec(dllexport) Feature : public Thread
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
	*/
	Feature(const std::string& name);

	//! Destructor.
	~Feature(void);

	//! Virtual method for loading algorithm specific settings from the given storage.
	/*!
		\param fileStorage An already open storage from which anything specific can be read.
	*/
	virtual void LoadSettingsFromFileStorage(const cv::FileStorage& fileStorage) = NULL;

	//! Connects a frame to the feature extractor.
	/*!
		\param frame Output parameter for the current frame.
	*/
	void SetFrame(cv::Mat& frame);

	std::vector<cv::KeyPoint> keypoints;	//<! Stores keypoints, i.e. a point feature found by one of many available keypoint detectors.

protected:
	//! Virtual method for each feature extraction algorithm.
	virtual void Process(void) = NULL;

	//! Virtual method for feature point detection.
	virtual void detectImpl(void) = NULL;

	std::string name_;	//<! Name of the current feature extraction procedure.
	cv::Mat frame_;		//<! The current frame.	
	Mutex mutex_;		//<! Synchronization object.

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa Thread::Run()
	*/
	void* Run(void);
};
