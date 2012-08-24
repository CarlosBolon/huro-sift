#pragma once

/*!
	\defgroup FeatureExtractor FeatureExtractor module.
*/

#include <string>

#include "opencv2/opencv.hpp"

#include "Thread.h"

//! Abstract class for global feature extraction.
/*!
	\ingroup FeatureExtractor
*/
extern "C++" class __declspec(dllexport) GlobalFeature : public Thread
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	GlobalFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~GlobalFeature(void);

	//! Connects a frame to the feature extractor.
	/*!
		\param frame Output parameter for the current frame.
	*/
	void SetFrame(const cv::Mat& frame);

    //! Name getter.
    /*!
		\return Name of the current feature extraction procedure.
	*/
    const std::string& GetName(void);

    //! Type getter.
    /*!
		\return Type of the current feature extraction procedure.
	*/
    const std::string& GetType(void);

    //! Process time getter.
    /*!
		\return Processing time of the current feature extraction method.
	*/
    double GetProcTime(void);

    std::vector<cv::KeyPoint> keyPoints;	//!< Stores keypoints, i.e. a point feature found by one of many available keypoint detectors.

protected:
    //! Virtual method for loading algorithm specific settings from the given storage.
	virtual void LoadSettingsFromFileStorage(void) = NULL;

	//! Virtual method for each feature extraction algorithm.
	virtual void Process(void) = NULL;

	//! Virtual method for drawing the extracted features.
	virtual void DrawFeatures(void) = NULL;

	std::string name_;	//!< Name of the current feature extraction procedure.
    std::string type_;	//!< Type of the current feature extraction procedure.
	cv::Mat frame_;		//!< The current frame.
	double procTime_;	//!< Processing time of the current feature extraction method.

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa Thread::Run()
	*/
	void* Run(void);

    //! Visualizing the output of feature extractor.
    /*!
		\param keyPointsCount Number of the detected keypoints.
	*/
    void Visualize(void);
};
