#include <fstream>
#include "opencv2/opencv.hpp"

#include "ObjectRecognition\LocalSettings.h"

using namespace std;
using namespace cv;

namespace ObjectRecognition
{


LocalSettings::LocalSettings(void)
{
	string localSettings("../LocalSettings.txt");
	ifstream fileStream(localSettings.c_str());

	if (!fileStream.is_open()) 
		CV_Error(1, "Local settings file '" + localSettings + "' does not exist!");

	getline(fileStream, dataDirectory_);

	inputDirectory_ = dataDirectory_ + "Input/";
	databaseDirectory_ = dataDirectory_ + "Database/";
	processXmlFileName_ = dataDirectory_ + "xml/Process.default.xml";
    featureExtractorDirectory_  = dataDirectory_ + "xml/FeatureExtractor/";

	fileStream.close();
}


LocalSettings::~LocalSettings(void)
{
}


LocalSettings* LocalSettings::GetInstance(void)
{
	static LocalSettings* localSettings = new LocalSettings();
	return localSettings;
}


string LocalSettings::GetInputDirectory(void) const
{
	return inputDirectory_;
}


string LocalSettings::GetDataBaseDirectory(void) const
{
	return databaseDirectory_;
}


string LocalSettings::GetFeatureExtractorDirectory(void) const
{
	return featureExtractorDirectory_;
}


string LocalSettings::GetProcessXmlFileName(void) const
{
    return processXmlFileName_;
}


}
