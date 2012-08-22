#pragma once
#pragma warning( disable: 4251 ) // Disable needs to have dll-interface warning.

/*!
	\defgroup Core Core module.
*/

#include <string>

#define LocalSettingsPtr LocalSettings::GetInstance()

//! Singleton settings manager class.
/*!
	\ingroup Core

	Contains the paths of XMLs and video files.
*/
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
	std::string GetDataDirectory(void) const;

    //! Settings directory getter.
	/*!
		\return Settings directory root.
	*/
	std::string GetSettingsDirectory(void) const;

private:
	//! Constructor.
	LocalSettings();

	//! Destructor.
	~LocalSettings();

	std::string	dataDirectory_;			//!< Data directory root.
    std::string	settingsDirectory_;	    //!< Settings directory root.
	std::string	processXmlFileName_;	//!< The configuration file.
};
