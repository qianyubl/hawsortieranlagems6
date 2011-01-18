/*
 * Z7_MetallMessung.cpp
 *
 * Created on: 20.12.2010
 *      Author: wehrin_d
 */

#include "Z7_MetallMessung.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"
#include "Werkstueck.h"
#include "Timer.h"
#include "Z7_WsInMetallMessungIllegal.h"

/**
 * Z7_MetallMessung sets the owner of automat
 * 
 * @automat is needed to have the states owner
 */
Z7_MetallMessung::Z7_MetallMessung(Automat* automat) {
	owner=automat;
}
/**
 * ~Z7_MetallMessung is destructor
 * 
 */
Z7_MetallMessung::~Z7_MetallMessung() {}

/**
 * wsMetall checks wheter ws is too slow, go into state "ws in metall messung illegal"
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z7_MetallMessung::wsMetall(int flanke){
	if(flanke>0){
			WerkstueckListe* wsl = WerkstueckListe::getInstance();
			//printf("Zeit: %ld\n",Timer::getTimeStamp());
			int wsPosi=wsl->getLastWsWithStation(STATION_EINLAUF);
			if(wsPosi>=0){
				Werkstueck* w=wsl->getWsAt(wsPosi);
				long delta= (Timer::getTimeStamp()-w->getTimestamp());
				if(    (HardwareLayer::getInstance()->getBandNr()==1) &&  (delta <=  2500)  ){
						printf("ws zu frueh in metallmessung\n");
						owner->setState(new Z7_WsInMetallMessungIllegal(owner));
						// fehler zustand
						// user sagen er solls runter nehmen
						// reset usw.
				}
				else{
					w->ok=WS_OK;
				}
			}
			else{
				printf("ws zu frueh in metallmessung\n");
				owner->setState(new Z7_WsInMetallMessungIllegal(owner));
			}
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z7_MetallMessung::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z7_MetallMessung::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
