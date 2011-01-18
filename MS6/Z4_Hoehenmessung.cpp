/*
 * Z4_Hoehenmessung.cpp
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#include "Z4_Hoehenmessung.h"
#include "Werkstueck.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"
#include "Timer.h"
#include <unistd.h>
#include "Z4_WsImHMIllegal.h"

/**
 * Z4_Hoehenmessung sets the state owner and name
 * 
 * @automat is needed to have the states owner
 */
Z4_Hoehenmessung::Z4_Hoehenmessung(Automat* automat) {
	owner=automat;
	name="Z4_Hoehenmessung";
}

/**
 * ~Z4_Hoehenmessung is destructor
 * 
 */
Z4_Hoehenmessung::~Z4_Hoehenmessung() {}

/**
 * hoeheBereich1 checks wheter ws is in time and mess the height if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z4_Hoehenmessung::hoeheBereich1(int flanke){
	if(flanke==0){
		WerkstueckListe* wsl = WerkstueckListe::getInstance();
		int wsPosi=wsl->getLastWsWithStation(STATION_EINLAUF);
		if(wsPosi>=0){
			Werkstueck* w=wsl->getWsAt(wsPosi);
			long delta = (Timer::getTimeStamp() - w->getTimestamp());
			if (delta <= 1800) {
				return;
			}
		}
		if(wsl->isEmpty())return;


		HardwareLayer::getInstance()->motorAus();
		usleep(1000* 200);
		int hoehe=HardwareLayer::getInstance()->readHeight();
		printf("Hoehe=%d\n",hoehe);
		HardwareLayer::getInstance()->motorAn();
		if( (hoehe>3300) && (hoehe<3800)){
			WerkstueckListe* wsl = WerkstueckListe::getInstance();
			int wsPosi=wsl->getLastWsWithStation(STATION_EINLAUF);
			if(wsPosi<0)wsPosi=wsl->getLastWsWithStation(STATION_HOEHENMESSUNG);
			if(wsPosi>=0){
				Werkstueck* w=wsl->getWsAt(wsPosi);
				w->ok=WS_OK;
				//w->setLetzteStation(STATION_HOEHENMESSUNG);
			}
			else{
					printf("Z4_Hoehenmessung-> ws nicht gefunden\n");
			}
		}
	}
}

/**
 * wsInHoehenMessung checks wheter ws is too early with time stamps or
 * go into state "ws im hm illegal", all when flank is fallen
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z4_Hoehenmessung::wsInHoehenMessung(int flanke){
	if(flanke==0){
		WerkstueckListe* wsl = WerkstueckListe::getInstance();
		int wsPosi=wsl->getLastWsWithStation(STATION_EINLAUF);
		if(wsPosi>=0){
			Werkstueck* w=wsl->getWsAt(wsPosi);
			long delta = (Timer::getTimeStamp() - w->getTimestamp());
			//printf("delta hoehenmessung : %ld\n",delta);
			if (delta <= 2000) {
				w->ok=WS_NOK;
				printf("ws zu frueh in hm\n");
				owner->setState(new Z4_WsImHMIllegal(owner));
				// fehler zustand
				// user sagen er solls runter nehmen
				// reset usw.
			}
			else{
				w->setLetzteStation(STATION_HOEHENMESSUNG);
				w->setTimestamp(Timer::getTimeStamp());
				//w->printIt();
			}
		}
		else{
			owner->setState(new Z4_WsImHMIllegal(owner));
		}
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z4_Hoehenmessung::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z4_Hoehenmessung::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}

