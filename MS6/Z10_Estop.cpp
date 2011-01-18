/*
 * Z10_Estop.cpp
 *
 * Created on: 13.01.2011
 *      Author: wehrin_d
 */

#include "Z10_Estop.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"

/**
 * Z10_Estop set the state in blocking state
 * 
 */
Z10_Estop::Z10_Estop(Automat* automat) {
	owner = automat;

	if(HardwareLayer::getInstance()->eStopGedrueckt()){
		estop=true;
		blockierDieAnderen();
	}
	else{
		estop=false;
		blockierungWegNehmen();
	}
	name="Z10_Estop";
}

/**
 * tasteEStop is
 * 
 */
void Z10_Estop::tasteEStop(int flanke){
	if(flanke>0){
		estop=false;
		blockierungWegNehmen();
	}
	else{
		estop=true;
		blockierDieAnderen();
	}
}

/**
 * blockierDieAnderen stops motor and set a bit, that
 * is requested by the MsgReceivePulse, that every state knows it
 *
 */
void Z10_Estop::blockierDieAnderen(){
	HardwareLayer* hal = HardwareLayer::getInstance();
	hal->setBand2Ready(true);
	hal->motorStopAn();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	hal->ampelAnstehendUnquittiert();
}
/**
 * blockierungWegNehmen is called, when the e stop bit is unset
 * 
 */
void Z10_Estop::blockierungWegNehmen(){
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
