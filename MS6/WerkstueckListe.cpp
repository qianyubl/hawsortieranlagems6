/*
 * WerkstueckListe.cpp
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#include "WerkstueckListe.h"
#include "Mutex.h"
#include <stdio.h>
#include "Timer.h"

Mutex* WerkstueckListe::wslMutex = new Mutex();
WerkstueckListe* WerkstueckListe::pInstance=0;


/**
 * WerkstueckListe is constructor
 * 
 */
WerkstueckListe::WerkstueckListe() {}

/**
 * ~WerkstueckListe is destructor
 * 
 */
WerkstueckListe::~WerkstueckListe() {}


/**
 * getInstance gets the instance of the ws list
 * 
 * @return returns the instance from ws list
 */
WerkstueckListe* WerkstueckListe::getInstance(){
	if ( !pInstance ){
		wslMutex->lock();
		if ( !pInstance )
			pInstance = new WerkstueckListe();
			wslMutex->unlock();
		}
		return pInstance ;
}

/**
 * isEmpty return wheter is empty
 * 
 * @return returns wheter ws list is empty
 */
bool WerkstueckListe::isEmpty(){
	if(this->liste.size()==0)return true;
	else return false;
}

/**
 * printIt prints the ws objekts
 * 
 */
void WerkstueckListe::printIt(){
	Werkstueck* ws=NULL;
	printf("************** WS LISTE *************************\n");
	printf("SIZE = %d\n",size());
	for(int i=this->liste.size()-1;i>=0;i--){
		ws=getWsAt(i);
		printf("%d:",i);
		ws->printIt();
	}
	printf("*************************************************\n");
}

/**
 * clear erases alle obj from ws list
 * 
 */
void WerkstueckListe::clear(){
	for(int i=this->liste.size()-1;i>=0;i--){
		eraseWsAt(i);
	}
}

/**
 * saveTimestampAtStop saves the time stamp at a stop
 * 
 */
void WerkstueckListe::saveTimestampAtStop(){
	this->timestampAtStop=Timer::getTimeStamp();
}

/**
 * refreshTimestamps subtract actual time stamps with older time stamps
 * 
 */
void WerkstueckListe::refreshTimestamps(){
	Werkstueck* ws=NULL;
	for(int i=this->liste.size()-1;i>=0;i--){
			ws=getWsAt(i);
			long delta=Timer::getTimeStamp()-this->timestampAtStop;
			ws->setTimestamp(ws->getTimestamp()+delta);
	}
}

/**
 * getWsAt gets a ws at a specific position
 * 
 * @positin is the position i want to watch in ws list
 * @return return the ws obj
 */
Werkstueck* WerkstueckListe::getWsAt(int position){
	return this->liste.at(position);
}

/**
 * add adds a ws to list at front
 * 
 */
void WerkstueckListe::add(Werkstueck* ws){
	this->liste.insert(this->liste.begin(),ws);
}

/**
 * eraseWsAt erases a ws in list, if ws list is empty set new start time
 *
 * @position is the position from the ws that should be deleted 
 */
void WerkstueckListe::eraseWsAt(int position){
	this->liste.erase(this->liste.begin()+position);
	if(isEmpty())Timer::setStartTime();
}

/**
 * size is getter
 * 
 * @return return the size of the list
 */
int WerkstueckListe::size(){
	return this->liste.size();
}

/**
 * getLastWsWithStation returns the ws index with the station
 * 
 * @station is the station that is aked in every ws
 * @return returns the index of ws that has this station, else -1
 */
int WerkstueckListe::getLastWsWithStation(int station){
	Werkstueck* ws=NULL;
	for(int i=this->liste.size()-1;i>=0;i--){
		ws=getWsAt(i);
		if(ws->getLetzteStation()==station){
			return i;
		}
	}
	return -1;
}

/**
 * getLifoWsWithStation
 * 
 * @station is the station that is requested
 * @return return the ws with stations with LIFO searching
 */
int WerkstueckListe::getLifoWsWithStation(int station){
	Werkstueck* ws=NULL;
		for(unsigned int i=0;i<this->liste.size();i++){
			ws=getWsAt(i);
			if(ws->getLetzteStation()==station){
				return i;
			}
		}
		return -1;
}
