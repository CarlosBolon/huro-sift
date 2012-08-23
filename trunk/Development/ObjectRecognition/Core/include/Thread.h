#pragma once
#pragma warning( disable: 4251 ) // Disable needs to have dll-interface warning.

#include <memory>
#include <pthread.h>

#include "Runnable.h"

//! Abstract class for handling threads.
/*!
	\ingroup Core

	Runnable classes can be derived from this class.

	Threads can be started and stopped with the Start() and Join() methods respectively.
	The new thread will enter the implemented Run() method.
*/
extern "C++" class __declspec(dllexport) Thread 
{
public:
	//! Constructor.
	/*!
		\param run Runnable object.
		\param isDetached Whether or not the thread is to be created in a detached state.
	*/
	Thread(
		std::auto_ptr<Runnable> run, 
		bool					isDetached = false);

	//! Constructor.
	/*!
		\param isDetached Whether or not the thread is to be created in a detached state.
	*/
	Thread(bool isDetached = false);

	//! Destructor.
	virtual ~Thread(void);

	//! Starts the thread.
	void Start(void);

	// A thread calling T.join() waits until thread T completes.
	void* Join(void);

private:
	// Called when run() completes
	void SetCompleted(void);

	//! Pure virtual thread main.
	virtual void* Run(void) = 0;

	//! Thread start function when a Runnable is involved.
	/*!
		\param pVoid
	*/
	static void* StartThreadRunnable(void* pVoid);

	//! Thread start function when no Runnable is involved.
	/*!
		\param pVoid
	*/
	static void* StartThread(void* pVoid);

	pthread_t threadID_;				//<! Thread ID.
	bool detached_;						//<! True if thread created in detached state.
	pthread_attr_t threadAttribute_;	//<! Thread attribute.
	std::auto_ptr<Runnable> runnable_;	//<! Runnable object will be deleted automatically.
	void* result_;						//<! Stores return value from run().
};