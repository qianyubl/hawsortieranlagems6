/*
 * Z2_KeinWSImEinlauf.cpp
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#include "Z2_KeinWSImEinlauf.h"
#include "Z2_WsImEinlauf.h"
#include "WerkstueckListe.h"
#include "Werkstueck.h"
#include "Timer.h"
#include "Z2_WsZuFruehImEinaluf.h"


/**
 * ~Z2_KeinWSImEinlauf is destructor
 * 
 */
Z2_KeinWSImEinlauf::~Z2_KeinWSImEinlauf() {}

/**
 * Z2_KeinWSImEinlauf sets the owner and name
 * 
 * @automat is needed to have the states owner
 */
Z2_KeinWSImEinlauf::Z2_KeinWSImEinlauf(Automat* automat){
	owner=automat;
	name="Z2_KeinWSImEinlauf";
}

/**
 * wsImEinlauf checks the time stamp to the last ws if flank is fallen
 * and go into "ws zu frueh im einlauf" or "ws im einlauf"
 * else set state to "ws im einlauf"
 *
 * @flanke that is the pos or neg bit of an integer that belongs to the hardware interrupt
 */
void Z2_KeinWSImEinlauf::wsImEinlauf(int flanke){
	if(flanke==0){
		WerkstueckListe* wsl = WerkstueckListe::getInstance();
		int wsPosi=wsl->getLifoWsWithStation(STATION_EINLAUF);
		long now = 0;
		if(wsPosi>=0){
			// abstand zum letzten ws pruefen
			Werkstueck* w=wsl->getWsAt(wsPosi);
			now = Timer::getTimeStamp();
			long delta=now - w->getTimestamp();
			if(    delta  < 1000  ){ // ms
				printf("Abstand nicht eingehalten! Werkstueck im Einlauf entfernen !\n");
				owner->setState(new Z2_WsZuFruehImEinaluf(owner));
			}
			else{
				owner->setState(new Z2_WsImEinlauf(owner));
			}
		}
		else{
			owner->setState(new Z2_WsImEinlauf(owner));
		}
	}
	else{
		printf("WS waehrend eines Fehlerzustand oder vorm starten rein gelegt bitte entfernen!\n");
		//owner->setState(new Z2_WsImEinlaufImFehlerZustandHizugefuegt(owner));
		//TODO Fehler Zustand
	}
}

/**
 * WsVerschwunden sets the state so start state
 * 
 */
void Z2_KeinWSImEinlauf::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state so start state
 * 
 */
void Z2_KeinWSImEinlauf::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
