/*
 * Werkstueck.cpp
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#include "Werkstueck.h"
#include <stdio.h>

/**
 * Werkstueck is constructor, set the ws to not ok
 * 
 */
Werkstueck::Werkstueck() {
	this->ok=WS_NOK;
}

/**
 * ~Werkstueck is destructor
 * 
 */
Werkstueck::~Werkstueck() {
	// TODO Auto-generated destructor stub
}

/**
 * setLetzteStation set the last station param
 * 
 * @letzteStation is the value that should be set to letzteStation
 */
void Werkstueck::setLetzteStation(int letzteStation) {
	this->letzteStation=letzteStation;
}

/**
 * getLetzteStation is getter
 * 
 * @return returns the last station
 */
int Werkstueck::getLetzteStation(){
	return letzteStation;
}
/**
 * setTimestamp is setter
 * 
 * @timestamp sets value to time stamp
 */
void Werkstueck::setTimestamp(long timestamp){
	this->timestamp=timestamp;
}
/**
 * getTimestamp getter
 * 
 * @return returns time stamp
 */
long Werkstueck::getTimestamp(){
	return timestamp;
}

/**
 * printIt prints the timestamps from stations and info about ws
 * 
 */
void Werkstueck::printIt(){
	printf("Timestamp = %ld, ",this->timestamp);
	if(this->letzteStation==STATION_EINLAUF){
		printf("letzteStation = STATION_EINLAUF, ");
	}
	else if(this->letzteStation==STATION_HOEHENMESSUNG){
		printf("letzteStation = STATION_HOEHENMESSUNG, ");
	}
	else if(this->letzteStation==STATION_WEICHE){
		printf("letzteStation = STATION_WEICHE, ");
	}
	else if(this->letzteStation==STATION_AUSLAUF){
		printf("letzteStation = STATION_AUSLAUF, ");
	}
	else if(this->letzteStation==STATION_RUTSCHE){
			printf("letzteStation = STATION_RUTSCHE, ");
	}
	else{
		printf("letzteStation = ##### ????? ##### --->%d, ",this->letzteStation);
	}
	if(this->ok==WS_OK){
		printf("OK\n");
	}
	else{
		printf("NOT OK\n");
	}
}
