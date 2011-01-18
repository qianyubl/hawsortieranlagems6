/**
 * RotBlinktThread.h
 *
 * Created on: 09.11.2010
 *      Author: aav726
 */

#ifndef ROTBLINKTTHREAD_H_
#define ROTBLINKTTHREAD_H_

#include "HAWThread.h"
#include "HardwareLayer.h"

class RotBlinktThread: public thread::HAWThread {
public:
	RotBlinktThread();
	virtual ~RotBlinktThread();

	/**
		 * starts the thread
		 *
		 * @no Arg
		 */
	virtual void execute(void*);

	/**
	 * shuts the thread down
	 *
	 * @no Arg
	 */
	virtual void shutdown();
	void setFrequenz(int fr);
	bool isRunning();
	void threadSuspend();
	void threadResume();

	private:
	bool run;
	int frequenz;
};

#endif /* ROTBLINKTTHREAD_H_ */
