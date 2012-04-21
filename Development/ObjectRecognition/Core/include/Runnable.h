#pragma once

//! Abstract interface for runable objects.
/*!
	\ingroup Core
*/
extern "C++" class __declspec(dllexport) Runnable 
{
public:
	//! Destructor.
	virtual ~Runnable() = 0;

	//! Pure virtual thread main.
	virtual void* Run() = 0;
};
