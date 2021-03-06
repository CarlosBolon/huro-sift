#include "ObjectRecognition\Thread.h"

using namespace std;

namespace ObjectRecognition
{


Thread::Thread(auto_ptr<Runnable> r, bool isDetached) 
:	runnable_(r), 
	detached_(isDetached) 
{
	if(!runnable_.get())
		CV_Error(1, "Runnable is NULL!");
}


Thread::Thread(bool isDetached) 
:	runnable_(NULL), 
	detached_(isDetached) 
{
}


Thread::~Thread(void) 
{
}


void* Thread::StartThreadRunnable(void* pVoid) 
{
	// thread start function when a Runnable is involved
	Thread* runnableThread = static_cast<Thread*>(pVoid);

	runnableThread->result_ = runnableThread->runnable_->Run();
	runnableThread->SetCompleted();

	return runnableThread->result_;
}


void* Thread::StartThread(void* pVoid) 
{
	// thread start function when no Runnable is involved
	Thread* aThread = static_cast<Thread*>(pVoid);

	aThread->result_ = aThread->Run();
	aThread->SetCompleted();

	return aThread->result_;
}


void Thread::Start(void) 
{
	// initialize attribute object
	if(pthread_attr_init(&threadAttribute_))
		CV_Error(1, "pthread_attr_init failed at");

	// set the scheduling scope attribute
	if(pthread_attr_setscope(&threadAttribute_, PTHREAD_SCOPE_SYSTEM))
		CV_Error(1, "pthread_attr_setscope failed at");

	if(!detached_) 
	{
		if(!runnable_.get()) 
		{	
			if(pthread_create(&threadID_, &threadAttribute_, Thread::StartThread, (void*)this))
				CV_Error(1, "pthread_create failed at");
		}
		else 
		{	
			if(pthread_create(&threadID_, &threadAttribute_, Thread::StartThreadRunnable, (void*)this))
				CV_Error(1, "pthread_create failed at");
		}
	}
	else 
	{
		// set the detachstate attribute to detached	
		if(pthread_attr_setdetachstate(&threadAttribute_, PTHREAD_CREATE_DETACHED))
			CV_Error(1, "pthread_attr_setdetachstate failed at");

		if(!runnable_.get()) 
		{	
			if(pthread_create(&threadID_, &threadAttribute_, Thread::StartThread, (void*)this))
				CV_Error(1, "pthread_create failed at");
		}
		else 
		{	
			if(pthread_create(&threadID_, &threadAttribute_, Thread::StartThreadRunnable, (void*)this))
				CV_Error(1, "pthread_create failed at");
		}
	}

	if(pthread_attr_destroy(&threadAttribute_)) 
		CV_Error(1, "pthread_attr_destroy failed at");
}


void* Thread::Join(void) 
{
	// result was already saved by thread start function
	if(pthread_join(threadID_, NULL))
		CV_Error(1, "pthread_join failed at");

	return result_;
}


void Thread::SetCompleted(void) 
{
	// completion handled by pthread_join()
}


}
