/***************************************************************************
 *
 *    Hochschule für Angewandte Wissenschaften Hamburg
 *
 *    WP
 *    Effiziente Datenstrukturen in C++ für verteilte Echtzeitprogrammierung
 *
 *	 Prof. Dr. Stephan Pareigis
 *
 *    Thread Class Implementation
 ****************************************************************************/
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

#include "HAWThread.h"

namespace thread {

volatile bool HAWThread::GLOBAL_EXIT = false;

HAWThread::HAWThread() :
	bRunning_(false), LOCAL_EXIT(false) {
}

/**
 * ~HAWThread is
 * 
 */
HAWThread::~HAWThread() {
	ThreadDestroy(tid_, 0, 0);
}

/**
 * start is
 * 
 */
void HAWThread::start(void * arg) {
	if (bRunning_)
		return;
	bRunning_ = true;
	Arg(arg); // store user data
	int code = pthread_create(&tid_, NULL, (HAWThread::entryPoint), this);
	if (code != 0)
		cout << "Thread could not be started." << endl;
}

/**
 * stop is
 * 
 */
void HAWThread::stop() {
	LOCAL_EXIT = true;
}

/**
 * hold is
 * 
 */
void HAWThread::hold() {
	ThreadCtl(_NTO_TCTL_ONE_THREAD_HOLD, (void*) tid_);
}
/**
 * cont is
 * 
 */
void HAWThread::cont() {

	ThreadCtl(_NTO_TCTL_ONE_THREAD_CONT, (void*) tid_);
}

/**
 * thread hold a time and compare to cpu time
 *
 * @int x: is arg to set the sleeping time of current thread
 */
/**
 * cont is
 * 
 */
void HAWThread::cont(int x) { // lasst diese funktion bitte drinne...ppppppp
	long difsec ;
	long difusec;
	 timeval start, end;
	gettimeofday(&start, 0);

	cout << start.tv_sec << ':' << start.tv_usec << endl;
	//printf("start : %d",start.tv_sec );fflush(stdout);

	sleep(x);
	ThreadCtl(_NTO_TCTL_ONE_THREAD_CONT, (void*) tid_);
	gettimeofday(&end, 0);
	cout << end.tv_sec << ':' << end.tv_usec << endl;

difsec  = end.tv_sec - start.tv_sec;
difusec = end.tv_usec - start.tv_usec;
	cout << difsec << ':' << difusec << endl;
	//printf("ende : %d",end.tv_sec );fflush(stdout);
}

/**
 * run is
 * 
 */
void HAWThread::run(void * arg) {
	execute(arg);
	shutdown();
}

/**
 * entryPoint is
 * 
 */
void* HAWThread::entryPoint(void* pthis) {
	HAWThread* pt = (HAWThread*) pthis;
	pt->run(pt->Arg());
	return NULL;
}

/**
 * join is
 * 
 */
void HAWThread::join() const {
	pthread_join(tid_, NULL);
}
}
;
