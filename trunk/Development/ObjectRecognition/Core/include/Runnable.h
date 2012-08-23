#pragma once

//! Abstract interface for runnable objects.
/*!
	\ingroup Core
*/
extern "C++" class __declspec(dllexport) Runnable 
{
public:
	//! Destructor.
	virtual ~Runnable(void) = 0;

	//! Pure virtual thread main.
	virtual void* Run(void) = 0;
};
