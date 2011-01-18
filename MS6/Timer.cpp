/*
 * Timer.cpp
 *
 * Created on: 14.12.2010
 *      Author: wehrin_d
 */

#include "Timer.h"
#include <unistd.h>
#include <iostream>
using namespace std;
#include <sys/time.h>

/**
 * Timer sets owner from Zustand and restart timer
 * set stopped to false
 *
 */
Timer::Timer(Zustand* owner) {
	this->owner=owner;
	this->start(0);
	this->hold();
	this->reset();
	stopped=false;

}

/**
 * ~Timer is destructor
 * 
 */
Timer::~Timer() {}

long Timer::starttime=0;

/**
 * setStartTime sets the starttime with accuracy of milliseconds second
 * 
 */
void Timer::setStartTime(){
	timeval t;
	gettimeofday(&t, NULL);
	usleep(1000000-t.tv_usec);
	starttime=t.tv_sec+1;
}

/**
 * stopIt sets stopped to true
 * 
 */
void Timer::stopIt(){
	stopped=true;
}

/**
 * setValue sets a value through parameter
 * 
 * @v is value to set
 */
void Timer::setValue(int v){
	this->value=v;
}

/**
 * execute is main routine to increment time
 * 
 */
void Timer::execute(void*){
	while(!isStopped()) {

		usleep(1000*10); // 10 ms
		value++;
			//if(max==80)printf("time: %d\n",value);
		if(value==max){
			owner->timerAbgelaufen();
			//return;
			//break;
		}
//		if(stopped){
//			return;
//		}
	}
}

/**
 * reset sets value to ZERO
 * 
 */
void Timer::reset(){
	value=0;
}

/**
 * setMax sets max value
 * 
 * @max value to set
 */
void Timer::setMax(int max){
	this->max=max;
}

/**
 * getValue is getter
 * 
 * @return the value
 */
int Timer::getValue(){
	return this->value;
}

/**
 * getTimeStamp gets the timestamp with accurace of milliseconds
 * 
 */
long Timer::getTimeStamp(){
	timeval now;
	long time;
	gettimeofday(&now, NULL);
	time=now.tv_sec-starttime;// sec seit sys start
	time=time*1000;// ms seit sys start
	time = time + (now.tv_usec/1000); // + tv_usec in ms
	return time;
}

/**
 * shutdown have to be implemented, because it's virtual
 * 
 */
void Timer::shutdown(){}
