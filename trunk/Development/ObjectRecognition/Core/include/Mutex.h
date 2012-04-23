#pragma once

#include <pthread.h>

//! A synchronization primitive that can also be used for interprocess synchronization
/*!
	\ingroup Core

	When two or more threads need to access a shared resource at the same time, the system needs a synchronization mechanism to ensure that only one thread at a time uses the resource. Mutex is a synchronization primitive that grants exclusive access to the shared resource to only one thread.
*/
extern "C++" class __declspec(dllexport) Mutex 
{
public:
	//! Constructor.
	Mutex(void);

	//! Destructor.
	~Mutex(void);

	//! Blocks the current thread. 
	void Lock(void);

	//! Unblocks the current thread.
	void Unlock(void);

private:
	pthread_mutex_t mutex_; //!< Inner mutex object.
};
