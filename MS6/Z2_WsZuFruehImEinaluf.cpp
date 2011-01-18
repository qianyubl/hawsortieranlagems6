/*
 * Z2_WsZuFruehImEinaluf.cpp
 *
 * Created on: 03.01.2011
 *      Author: wehrin_d
 */

#include "Z2_WsZuFruehImEinaluf.h"
#include "HardwareLayer.h"
#include "Z2_KeinWSImEinlauf.h"

/**
 * Z2_WsZuFruehImEinaluf sets communication for error, shows
 * that the system is not ok and goes into a not receipted state
 *
 * @automat is needed to have the states owner
 */
Z2_WsZuFruehImEinaluf::Z2_WsZuFruehImEinaluf(Automat* automat) {
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	name="Z2_WsZuFruehImEinaluf";
	hal->motorAus();
	hal->ampelAnstehendUnquittiert();
	quittiert=false;
}

/**
 * tasteReset reset and set the not receipted to receipted
 * 
 */
void Z2_WsZuFruehImEinaluf::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
	quittiert=true;
	// Fehler quittiert
}

/**
 * wsImEinlauf communicate that the error is away and sets the
 * new state to "kein ws im einlauf"
 * shows that system can run and start the motor again
 *
 *
 */
void Z2_WsZuFruehImEinaluf::wsImEinlauf(int flanke){
	if(flanke>0){
		HardwareLayer::getInstance()->sendToChannelFehlerWeg();
		owner->setFehlerVonMir(false);
		// Der anderen Automaten aus dem Wartezustand holen
		owner->setState(new Z2_KeinWSImEinlauf(owner));
		HardwareLayer::getInstance()->motorAn();
		if(quittiert){
				HardwareLayer::getInstance()->ampelGruen();
		}
		else{
			HardwareLayer::getInstance()->ampelGegangenUnquittiert();
		}
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z2_WsZuFruehImEinaluf::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z2_WsZuFruehImEinaluf::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}

