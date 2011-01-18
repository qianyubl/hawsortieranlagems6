/*
 * Z3_Warten.cpp
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#include "Z3_Warten.h"
#include "Z3_KeinWsImAuslauf.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"

/**
 * Z3_Warten sets the state owner and name
 * 
 * @owner is needed to have the states owner
 */
Z3_Warten::Z3_Warten(Automat* owner) {
	this->owner=owner;
	name="Z3_Warten";
	//motor aus
	// zeit lesen
}

/**
 * ~Z3_Warten is destructor
 * 
 */
Z3_Warten::~Z3_Warten() { }

/**
 * wsImAuslauf checks if ws is in auslauf and set attributes to show
 * that system is ok and communicates over channel, all when flank is fallen
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z3_Warten::wsImAuslauf(int flanke){
	if(flanke>0){
/**
 * getInstance()->getBandNr is
 * 
 */
		if(HardwareLayer::getInstance()->getBandNr()==2){
			bool wsGefunden=false;
			WerkstueckListe* wsl=WerkstueckListe::getInstance();
			for(int i=0;i<wsl->size();i++){
				if(!wsGefunden){
					Werkstueck* w=wsl->getWsAt(i);
					if(w->getLetzteStation()==STATION_AUSLAUF){
						wsl->eraseWsAt(i);
						wsGefunden=true;
					}
				}
				else{
					break;
				}
			}
			if(!wsGefunden){
				printf("Z3_Warten::wsImAuslauf Fehler -> ws nicht gefunden kann es nicht löschen!");
			}
			HardwareLayer::getInstance()->motorAn();
			HardwareLayer::getInstance()->sendToChannelFehlerWeg();
			owner->setFehlerVonMir(false);
			HardwareLayer::getInstance()->sendWsVomBandRunter();
			owner->setState(new Z3_KeinWsImAuslauf(owner));
		}
	}

}

/**
 * band2Frei deletes ws when state is in "station einlauf"
 * 
 */
void Z3_Warten::band2Frei(){
	//motor an
	//printf("Z3_Warten::band2Frei\n");
	HardwareLayer::getInstance()->motorAn();
	// timestamps aktualisierenTODO

	// ws aus list entfernen
	WerkstueckListe* liste=WerkstueckListe::getInstance();
	int stationsWert=0;
	bool wsGefunden=false;
	for(int i=0;i<liste->size();i++){
				if(!wsGefunden){
					Werkstueck* w=liste->getWsAt(i);
					stationsWert=w->getLetzteStation();
					if(stationsWert==STATION_AUSLAUF){
						liste->eraseWsAt(i);
						HardwareLayer::getInstance()->sendWsZuBand2();
						wsGefunden=true;
					}
				}
				else{
					break;
				}
	}
	HardwareLayer::getInstance()->sendToChannelFehlerWeg();
	owner->setFehlerVonMir(false);
	owner->setState(new Z3_KeinWsImAuslauf(owner));
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z3_Warten::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state
 * 
 */
void Z3_Warten::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}


