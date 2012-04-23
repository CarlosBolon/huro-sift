#include "ExceptionDescriptor.h"

#include <iostream>

using namespace std;

ExceptionDescriptor::ExceptionDescriptor(
	const string& error,
	const string& fileName,
	const string& funcName,
	int           line,
	bool          isError /*= true*/) throw()
	: error_   (error),
	fileName_(fileName),
	funcName_(funcName),
	line_    (line),
	isError_ (isError)
{
}

ExceptionDescriptor::ExceptionDescriptor(const ExceptionDescriptor& e) throw()
	: error_   (e.error_),
	fileName_(e.fileName_),
	funcName_(e.funcName_),
	line_    (e.line_),
	isError_ (e.isError_)
{
}

ExceptionDescriptor::~ExceptionDescriptor() throw()
{
}

const char* ExceptionDescriptor::what() const throw()
{
	return "ExceptionDescriptor";
}

void ExceptionDescriptor::TraceError() throw()
{
	if (isError_)
	{
		cerr << "An error occurred!" << endl;
		cerr << "  Error location  : " << fileName_  << endl; 
		cerr << "  Function name   : " << funcName_  << endl; 
		cerr << "  Line number     : " << line_      << endl;  
		cerr << "  Error Message   : " << error_     << endl; 
	} else
	{
		cerr << "An abnormal operation occurred!" << endl;
		cerr << "  Warning location: " << fileName_  << endl; 
		cerr << "  Function name   : " << funcName_  << endl; 
		cerr << "  Line number     : " << line_      << endl; 
		cerr << "  Warning Message : " << error_     << endl; 
	}
}
