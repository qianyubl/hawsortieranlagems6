/*
 * Timer.h
 *
 * Created on: 14.12.2010
 *      Author: wehrin_d
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "Zustand.h"
#include "HAWThread.h"
#include <time.h>

class Timer: public thread::HAWThread {
public:
	Timer(Zustand* owner);
	virtual ~Timer();

	virtual void execute(void*);
	virtual void shutdown();
	void reset();
	void setMax(int max);
	static long getTimeStamp();
	void startIt();
	void stopIt();
	int getValue();
	void setValue(int v);
	static void setStartTime();


private:
	bool stopped;
	static long starttime;
	Zustand* owner;
	int value;
	int max;
};

#endif /* TIMER_H_ */
