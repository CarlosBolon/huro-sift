#pragma once

#include "LocalFeature.h"

//! Class for extracting LBP features.
/*!
	\ingroup FeatureExtractor

	Local Binary Pattern (LBP) is a simple yet very efficient texture operator which labels the pixels of an image by thresholding the neighborhood of each pixel and considers the result as a binary number.

    See paper:
    T. Ojala, M. Pietikäinen, and D. Harwood (1994), "Performance evaluation of texture measures with classification based on Kullback discrimination of distributions", Proceedings of the 12th IAPR International Conference on Pattern Recognition (ICPR 1994), vol. 1, pp. 582 - 585.
*/
extern "C++" class __declspec(dllexport) LbpFeature : public LocalFeature
{
public:
	//! Constructor.
	/*!
		\param name Name of the current feature extraction procedure.
        \param type Type of the current feature extraction procedure (global or local).
	*/
	LbpFeature(const std::string& name, const std::string& type);

	//! Destructor.
	~LbpFeature(void);

	//! Implemented virtual method for loading algorithm specific settings from the given storage.
	/*!
		\sa Feature::LoadSettingsFromFileStorage()
	*/
	void LoadSettingsFromFileStorage(void);

private:
	//! Implemented virtual method for the algorithm.
	/*!
		\sa LocalFeature::Process()
	*/
	void Process(void);

    //! Initalizing the variables.
    /*!
		\sa LocalFeature::ProcessInit()
	*/
    void ProcessInit(void);

    //! Generate feature vector with using uniform patterns.
    void ProcessWithUniformPatterns(void);

    //! Generate feature vector without using uniform patterns.
    void ProcessWithoutUniformPatterns(void);

	//! Implemented virtual method for displaying the output.
	/*!
		\sa LocalFeature::DrawFeatures()
	*/
	void DrawFeatures(void);

    cv::Mat grayFrame_;

    bool useUniformPatterns_;
};
