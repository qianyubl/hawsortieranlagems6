/*
 * Z6_RutscheNichtVoll.cpp
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#include "Z6_RutscheNichtVoll.h"
#include "Z6_RutscheVoll.h"
#include "HardwareLayer.h"
#include "Werkstueck.h"
#include "WerkstueckListe.h"

/**
 * Z6_RutscheNichtVoll create and set max of timer and restart timer
 * 
 * @automat is needed to have the states owner
 */
Z6_RutscheNichtVoll::Z6_RutscheNichtVoll(Automat* automat) {
	name="Z6_RutscheNichtVoll";
	owner=automat;
	timer= new Timer(this);
	timer->setMax(50); // * 10ms
	timerStarted=false;
	timer->start(0);
	timer->hold();
	timer->reset();

}

/**
 * ~Z6_RutscheNichtVoll is destructor
 * 
 */
Z6_RutscheNichtVoll::~Z6_RutscheNichtVoll() {
	// TODO Auto-generated destructor stub
}
/**
 * timerAbgelaufen sets state to "rutsche voll" and timerStarted to true
 * 
 */
void Z6_RutscheNichtVoll::timerAbgelaufen(){
	owner->setState(new Z6_RutscheVoll(owner));
	timerStarted=true;
}

/**
 * rutscheVoll checks wheter ws is in rutsche ok and 
 * erase it, all if flank is fallen
 * else stop timer and set startedTimer to false
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z6_RutscheNichtVoll::rutscheVoll(int flanke){
	if(flanke==0){
		timer->cont();
		timerStarted=true;
		// starte thread der nach 0,5 nochmal guckt
		// wennn dann noch voll setzte automat in zustand rutsche voll
		WerkstueckListe* liste = WerkstueckListe::getInstance();
		int wsPosi=liste->getLastWsWithStation(STATION_WEICHE);
		if(wsPosi==-1){
				//printf("Z5_WsNichtInWeiche->EIN FEHLER ist aufgetreten! ws ist null\n");
				printf("unbekanntes Werkstueck in Rutschen-Sensor\n");
		}
		else{
			if(HardwareLayer::getInstance()->getBandNr()==1){
				liste->eraseWsAt(wsPosi);// ws löschen
			}
			else{
				liste->getWsAt(wsPosi)->setLetzteStation(STATION_RUTSCHE);
			}

		}

	}
	else{
		timer->hold();
		timer->reset();
		timerStarted=false;
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z6_RutscheNichtVoll::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z6_RutscheNichtVoll::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
