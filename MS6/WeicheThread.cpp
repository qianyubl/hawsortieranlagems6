/*
 * WeicheThread.cpp
 *
 * Created on: 08.12.2010
 *      Author: wehrin_d
 */

#include "WeicheThread.h"
#include "HardwareLayer.h"
#include <unistd.h>
#include <stdio.h>

#define TIME_OPEN 700//ms

/**
 * WeicheThread sets running_ to false
 * 
 */
WeicheThread::WeicheThread() {
	running_=false;

}

/**
 * ~WeicheThread is destructor
 * 
 */
WeicheThread::~WeicheThread() {
}

/**
 * isRunning getter
 * 
 * @return returns running_
 */
bool WeicheThread::isRunning(){
	return running_;
}

/**
 * setActiv sets running_ to true
 * 
 */
void WeicheThread::setActiv(){
	if(!running_){
		running_=true;
	}

}

/**
 * execute is main routine, it opens and closes
 * the weiche
 */
void WeicheThread::execute(void*){
	HardwareLayer* h= HardwareLayer::getInstance();

	while(!isStopped()) {
		if(running_){
			h->weicheAuf();
			printf("h->weicheAuf();");
			usleep(1000*TIME_OPEN);
			h->weicheZu();
			printf("h->weicheZu();");
			running_=false;
		}
		hold();

	}
}

/**
 * shutdown have to be implemented because it's virtual
 * 
 */
void WeicheThread::shutdown() {
	//shutdownAll();
}
