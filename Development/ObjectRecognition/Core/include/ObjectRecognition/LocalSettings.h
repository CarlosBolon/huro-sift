#pragma once
#pragma warning( disable: 4251 ) // Disable needs to have dll-interface warning.

/*!
	\defgroup Core Core module.
*/

#include <string>

//! Singleton settings manager class.
/*!
	\ingroup Core

	Contains the paths of XMLs and video files.
*/
namespace ObjectRecognition
{

#define LocalSettingsPtr LocalSettings::GetInstance()

extern "C++" class __declspec(dllexport) LocalSettings
{
public:
	//! Instance getter.
	/*!
		\return The instance.
	*/
	static LocalSettings* GetInstance(void);

	//! Data directory getter.
	/*!
		\return Data directory root.
	*/
	std::string GetDataBaseDirectory(void) const;

    //! Settings directory getter.
	/*!
		\return Settings directory root.
	*/
	std::string GetFeatureExtractorDirectory(void) const;

    //! Process xml filename getter.
	/*!
		\return Settings directory root.
	*/
	std::string GetProcessXmlFileName(void) const;

private:
	//! Constructor.
	LocalSettings(void);

	//! Destructor.
	~LocalSettings(void);

	std::string	dataDirectory_;				//!< Data directory root
	std::string	databaseDirectory_;			//!< Database directory.
    std::string	featureExtractorDirectory_;	//!< Settings directory root.
	std::string	processXmlFileName_;		//!< The configuration file.
};

}
