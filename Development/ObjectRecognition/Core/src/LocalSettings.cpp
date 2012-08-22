#include "LocalSettings.h"

#include <fstream>
#include "opencv2/opencv.hpp"
#include "ExceptionDescriptor.h"

using namespace std;
using namespace cv;

LocalSettings::LocalSettings()
{
	string localSettings("../LocalSettings.txt");
	ifstream fileStream(localSettings.c_str());

	if (!fileStream.is_open()) 
		throw ExceptionError("Local settings file '" + localSettings + "' does not exist!");

	getline(fileStream, dataDirectory_);

	processXmlFileName_ = dataDirectory_ + "xml/Process.default.xml";
    settingsDirectory_  = dataDirectory_ + "xml/DetectorSettings/";

	fileStream.close();
}

LocalSettings::~LocalSettings()
{
}

LocalSettings* LocalSettings::GetInstance()
{
	static LocalSettings* localSettings = new LocalSettings();
	return localSettings;
}

string LocalSettings::GetDataDirectory() const
{
	return dataDirectory_;
}

string LocalSettings::GetSettingsDirectory() const
{
	return settingsDirectory_;
}
