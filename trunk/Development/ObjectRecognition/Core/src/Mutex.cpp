#include "Mutex.h"

Mutex::Mutex(void) 
{
	pthread_mutex_init( &mutex_, NULL );
}

Mutex::~Mutex(void) 
{
	pthread_mutex_destroy(&mutex_);
}

void Mutex::Lock(void) 
{
	pthread_mutex_lock( &mutex_ );
}

void Mutex::Unlock(void) 
{
	pthread_mutex_unlock( &mutex_ );
}
