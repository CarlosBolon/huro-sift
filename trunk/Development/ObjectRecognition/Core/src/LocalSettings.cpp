#include "LocalSettings.h"

#include <fstream>
#include <sstream>
#include <string>

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

	string dataDirectory;
	string processXmlFileName;

	getline(fileStream, dataDirectory);
	getline(fileStream, processXmlFileName);

	if (processXmlFileName.empty())
	{
		ExceptionDescriptor e = ExceptionWarning("No processXmlFileName was given in the local settings file.");
		e.TraceError();

		processXmlFileName = dataDirectory + "XML/Process.default.xml";
	} 
	else
	{
		processXmlFileName = dataDirectory + "XML/" + processXmlFileName;
	}

	dataDirectory_            = dataDirectory;
	processXmlFileName_       = processXmlFileName;

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
