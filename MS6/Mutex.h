#ifndef MUTEX_H_
#define MUTEX_H_

#include "pthread.h"

class Mutex {
public:
	Mutex() { pthread_mutex_init(&plock, NULL); }
	~Mutex() { pthread_mutex_unlock(&plock); }

	void lock() { pthread_mutex_lock(&plock); }
	void unlock() { pthread_mutex_unlock(&plock); }

private:
	pthread_mutex_t plock;
};


#endif /*MUTEX_H_*/
