/*
 * Z2_WsImEinlauf.cpp
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#include "Z2_WsImEinlauf.h"
#include "Werkstueck.h"
#include "WerkstueckListe.h"
#include "Z2_KeinWSImEinlauf.h"
#include "Timer.h"
#include <stdio.h>

/**
 * ~Z2_WsImEinlauf is destructor
 * 
 */
Z2_WsImEinlauf::~Z2_WsImEinlauf() {}


/**
 * Z2_WsImEinlauf sets the owner and name
 * 
 * @automat is needed to have the states owner
 */
Z2_WsImEinlauf::Z2_WsImEinlauf(Automat* automat){
	owner=automat;
	name="Z2_WsImEinlauf";
}

/**
 * wsImEinlauf creates a new ws and set the last station, take
 * a time stamp if flank is raising
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z2_WsImEinlauf::wsImEinlauf(int flanke){
	if(flanke>0){
		ws= new Werkstueck();
		WerkstueckListe* wsl=WerkstueckListe::getInstance();
		ws->setLetzteStation(STATION_EINLAUF);
		wsl->add(ws);
		ws->setTimestamp(Timer::getTimeStamp());
		//ws->printIt();
		owner->setState(new Z2_KeinWSImEinlauf(owner));
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z2_WsImEinlauf::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z2_WsImEinlauf::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}

