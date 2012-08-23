#include "LocalSettings.h"

#include <fstream>
#include "opencv2/opencv.hpp"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

LocalSettings::LocalSettings(void)
{
	string localSettings("../LocalSettings.txt");
	ifstream fileStream(localSettings.c_str());

	if (!fileStream.is_open()) 
		throw ExceptionError("Local settings file '" + localSettings + "' does not exist!");

	getline(fileStream, dataDirectory_);

	processXmlFileName_ = dataDirectory_ + "xml/Process.default.xml";
    settingsDirectory_  = dataDirectory_ + "xml/DetectorSettings/";
    imageDirectory_  = dataDirectory_ + "image/";

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

string LocalSettings::GetDataDirectory(void) const
{
	return dataDirectory_;
}

string LocalSettings::GetSettingsDirectory(void) const
{
    return settingsDirectory_;
}

string LocalSettings::GetImageDirectory(void) const
{
    return imageDirectory_;
}

string LocalSettings::GetProcessXmlFileName(void) const
{
    return processXmlFileName_;
}
