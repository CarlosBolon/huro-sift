#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"

class KeyPoint;

/*
 * Abstract base class for 2D image feature detectors.
 */
extern "C++" class __declspec(dllexport) FeatureDetector
{
public:
    virtual ~FeatureDetector();
    
    /*
     * Detect keypoints in an image.
     * image        The image.
     * keypoints    The detected keypoints.
     * mask         Mask specifying where to look for keypoints (optional). Must be a char
     *              matrix with non-zero values in the region of interest.
     */
    void detect( const cv::Mat& image, std::vector<KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const;
    
    /*
     * Detect keypoints in an image set.
     * images       Image collection.
     * keypoints    Collection of keypoints detected in an input images. keypoints[i] is a set of keypoints detected in an images[i].
     * masks        Masks for image set. masks[i] is a mask for images[i].
     */
    void detect( const std::vector<cv::Mat>& images, std::vector<std::vector<KeyPoint> >& keypoints, const std::vector<cv::Mat>& masks=std::vector<cv::Mat>() ) const;

    // Read detector object from a file node.
    virtual void read( const cv::FileNode& );
    // Read detector object from a file node.
    virtual void write( cv::FileStorage& ) const;

    // Return true if detector object is empty
    virtual bool empty() const;

    // Create feature detector by detector name.
    static cv::Ptr<FeatureDetector> create( const std::string& detectorType );

protected:
    virtual void detectImpl( const cv::Mat& image, std::vector<KeyPoint>& keypoints, const cv::Mat& mask=cv::Mat() ) const = 0;

    /*
     * Remove keypoints that are not in the mask.
     * Helper function, useful when wrapping a library call for keypoint detection that
     * does not support a mask argument.
     */
    static void removeInvalidPoints( const cv::Mat& mask, std::vector<KeyPoint>& keypoints );
};
