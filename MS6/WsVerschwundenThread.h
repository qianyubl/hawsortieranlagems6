/*
 * WsVerschwundenThread.h
 *
 * Created on: 06.01.2011
 *      Author: wehrin_d
 */

#ifndef WSVERSCHWUNDENTHREAD_H_
#define WSVERSCHWUNDENTHREAD_H_
#include "HAWThread.h"

class WsVerschwundenThread:  public thread::HAWThread {
public:
	WsVerschwundenThread();
	virtual ~WsVerschwundenThread();
	virtual void execute(void*);
	virtual void shutdown();
	void setActiv(bool a);
	void wsIstVerschwunden();
private:
	bool activ;
};

#endif /* WSVERSCHWUNDENTHREAD_H_ */
