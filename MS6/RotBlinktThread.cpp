/**
 * RotBlinktThread.cpp
 *
 * Created on: 09.11.2010
 *      Author: aav726
 */

#include "RotBlinktThread.h"
#include <unistd.h>

/**
 * RotBlinktThread is constructor
 * 
 */
RotBlinktThread::RotBlinktThread() {

}

/**
 * ~RotBlinktThread is destructor
 * 
 */
RotBlinktThread::~RotBlinktThread() {
	// TODO Auto-generated destructor stub
}

/**
 * setFrequenz set the frequenzy for blinking
 * 
 */
void RotBlinktThread::setFrequenz(int fr) {
	frequenz=fr;
}

/**
 * execute is main routine for blinking with usleep command
 * 
 */
void RotBlinktThread::execute(void*){
	run=true;
	HardwareLayer* h= HardwareLayer::getInstance();
	while(!isStopped()) {
		h->ampelRotAn();
		usleep(1000*(frequenz/2));
		h->ampelRotAus();
		usleep(1000*(frequenz/2));
	}
	run=false;
}

/**
 * isRunning returns run
 * 
 * @return is running?
 */
bool RotBlinktThread::isRunning(){
	return run;
}

/**
 * shutdown have to implemented, because it's a virtual
 * 
 */
void RotBlinktThread::shutdown() {
	//shutdownAll();
}

/**
 * threadSuspend is NOP, older using history
 * 
 */
void RotBlinktThread::threadSuspend(){
//
//	//pthread_t tid=getThreadPointer();
//	ThreadCtl(_NTO_TCTL_ONE_THREAD_HOLD, (void *) tid);
}

/**
 * threadResume is NOP, older using history
 * 
 */
void RotBlinktThread::threadResume(){
//	pthread_t tid=getThreadPointer();
//	ThreadCtl(_NTO_TCTL_ONE_THREAD_CONT, (void *) tid);
}


