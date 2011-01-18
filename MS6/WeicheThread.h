/*
 * WeicheThread.h
 *
 * Created on: 08.12.2010
 *      Author: wehrin_d
 */

#ifndef WEICHETHREAD_H_
#define WEICHETHREAD_H_

#include "HAWThread.h"

class WeicheThread: public thread::HAWThread {
public:
	WeicheThread();
	virtual ~WeicheThread();
	virtual void execute(void*);
	virtual void shutdown();
	bool isRunning();
	void setActiv();
private:
	bool running_;
};

#endif /* WEICHETHREAD_H_ */
