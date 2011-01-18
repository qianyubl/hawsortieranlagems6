/*
 * Z5_WsInWeicheIllegal.cpp
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#include "Z5_WsInWeicheIllegal.h"
#include "Z5_WsNichtInWeiche.h"
#include "HardwareLayer.h"

/**
 * Z5_WsInWeicheIllegal communicates error to channel and show,
 * that the system is not ok
 *
 * @automat is needed to have the states owner
 */
Z5_WsInWeicheIllegal::Z5_WsInWeicheIllegal(Automat* automat) {
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	name="Z5_WsInWeicheIllegal";
	hal->motorAus();
	hal->ampelAnstehendUnquittiert();
	quittiert=false;
}

/**
 * tasteReset sets the red light and assin receipted with true
 * 
 */
void Z5_WsInWeicheIllegal::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
	quittiert=true;
}

/**
 * wsInWeiche communicate to channel, that the error is away and show
 * it with setted attributes, all if flank is raising
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z5_WsInWeicheIllegal::wsInWeiche(int flanke) {
	if (flanke > 0) {//kein  ws in weiche
		HardwareLayer::getInstance()->sendToChannelFehlerWeg();
		owner->setFehlerVonMir(false);
		// Der anderen Automaten aus dem Wartezustand holen
		owner->setState(new Z5_WsNichtInWeiche(owner));
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
void Z5_WsInWeicheIllegal::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z5_WsInWeicheIllegal::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
