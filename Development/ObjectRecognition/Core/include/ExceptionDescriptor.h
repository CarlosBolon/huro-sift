#pragma once
#pragma warning( disable: 4251 ) // Disable needs to have dll-interface warning.

#include <exception>
#include <iostream>
#include <string>

//! Exception class.
/*!
	\ingroup Core

	Exception class whose instances store an error message, source file, function and line number.
*/
extern "C++" class __declspec(dllexport) ExceptionDescriptor : public std::exception
{
public:
	//! Constructor.
	/*!
		\param error    Error message.
		\param fileName Name of the file in which the exception was raised.
		\param funcName Name of the function in which the exception was raised.
		\param line     Number of line on which the exception was raised.
		\param isError  Error or abnormal operation.

		Should be used through the macro NewError(message) or NewWarning(message).
	*/
	ExceptionDescriptor(
		const std::string& error,
		const std::string& fileName,
		const std::string& funcName,
		int                line,
		bool               isError = true) throw();

	//! Copy constructor.
	/*!
		\param e Another ExceptionDescriptor.
	*/
	ExceptionDescriptor(const ExceptionDescriptor& e) throw();

	//! Destructor.
	~ExceptionDescriptor() throw();

	//! std::exception::what()
	const char* what() const throw();

	//! Write the exception description to stderr.
	void TraceError() throw();

private:
	std::string error_;    //!< Error message.
	std::string fileName_; //!< Name of the file.
	std::string funcName_; //!< Name of the function.
	int         line_;     //!< Line number.
	bool        isError_;  //!< Error or abnormal operation.
};

#define ExceptionError(message)   ExceptionDescriptor(message, std::string(__FILE__), std::string(__FUNCTION__), __LINE__, true)
#define ExceptionWarning(message) ExceptionDescriptor(message, std::string(__FILE__), std::string(__FUNCTION__), __LINE__, false)
