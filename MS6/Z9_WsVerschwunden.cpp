/*
 * Z9_WsVerwunden.cpp
 *
 * Created on: 13.01.2011
 *      Author: wehrin_d
 */

#include "Z9_WsVerschwunden.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"


/**
 * Z9_WsVerwunden sets the state owner and name
 * 
 */
Z9_WsVerwunden::Z9_WsVerwunden(Automat* automat) {
	owner = automat;
	wsVerschwunden=false;
	name="Z9_WsVerwunden";
}


/**
 * WsVerschwunden set wsVerschwunden to true and
 * call function blockierDieAnderen()
 */
void Z9_WsVerwunden::WsVerschwunden(){
	wsVerschwunden=true;
	blockierDieAnderen();
}

/**
 * blockierDieAnderen communicates to channel that error exists and
 * calls ampelAnstehendUnquittiert()
 *
 */
void Z9_WsVerwunden::blockierDieAnderen(){
	HardwareLayer* hal = HardwareLayer::getInstance();
	hal->motorStopAn();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	hal->ampelAnstehendUnquittiert();
}

/**
 * blockierungWegNehmen communicates with channel that error is away
 * if band number is 2, call function sendWsVomBandRunter()
 *
 */
void Z9_WsVerwunden::blockierungWegNehmen(){
	WerkstueckListe::getInstance()->clear();
	HardwareLayer* hal=HardwareLayer::getInstance();
	hal->sendToChannelFehlerWeg();
	owner->setFehlerVonMir(false);
	// Der anderen Automaten aus dem Wartezustand holen
	hal->motorStopAus();
	hal->ampelAus();
	if(hal->getBandNr()==2){
		HardwareLayer::getInstance()->sendWsVomBandRunter();
	}
}

/**
 * tasteReset stops the motor set wsVerschwunden to false
 * and calls the function blockierungWegNehmen()
 */
void Z9_WsVerwunden::tasteReset(){
	if(wsVerschwunden){
		wsVerschwunden=false;
		HardwareLayer::getInstance()->motorAus();
		blockierungWegNehmen();
	}
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z9_WsVerwunden::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
