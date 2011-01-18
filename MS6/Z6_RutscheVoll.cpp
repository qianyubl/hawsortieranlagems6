/*
 * Z6_RutscheVoll.cpp
 *
 * Created on: 14.12.2010
 *      Author: wehrin_d
 */

#include "Z6_RutscheVoll.h"
#include "Z6_RutscheNichtVoll.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"

/**
 * Z6_RutscheVoll comminucate error to channel and stops motor
 * and go into function ampelAnstehendUnquittiert()
 *
 * @automat is needed to have the states owner
 */
Z6_RutscheVoll::Z6_RutscheVoll(Automat* automat) {
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	name="Z6_RutscheVoll";
	hal->motorStopAn();
	hal->ampelAnstehendUnquittiert();


}

/**
 * ~Z6_RutscheVoll is destructor
 * 
 */
Z6_RutscheVoll::~Z6_RutscheVoll() {}

/**
 * tasteReset sets the red light on
 * 
 */
void Z6_RutscheVoll::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
}
/**
 * rutscheNichtMehrVoll communicate with channel, that the error is away
 * go into state "rutsche nicht voll"
 * checks if motor is on and show that the system is ok
 * decide between band number and send a 'r' for ready to the comport, erase ws
 *
 */
void Z6_RutscheVoll::rutscheNichtMehrVoll(){
	HardwareLayer::getInstance()->sendToChannelFehlerWeg();
	owner->setFehlerVonMir(false);
	// Der anderen Automaten aus dem Wartezustand holen
	owner->setState(new Z6_RutscheNichtVoll(owner));
	HardwareLayer::getInstance()->motorStopAus();
	if(  ((in8(PORT_A)) &MOTOR_RECHTS)==MOTOR_RECHTS){
		HardwareLayer::getInstance()->ampelGruen();
	}
	else{
		HardwareLayer::getInstance()->ampelAus();
	}
	if (HardwareLayer::getInstance()->getBandNr() == 2) {
		WerkstueckListe* liste = WerkstueckListe::getInstance();
		int wsPosi = liste->getLastWsWithStation(STATION_RUTSCHE);

		if (wsPosi >= 0) {
			string s = "r";
			HardwareLayer::getInstance()->ComPortWrite(s.c_str());
			liste->eraseWsAt(wsPosi);// ws löschen
		}
	}
}

/**
 * rutscheVoll call function rutscheNichtMehrVoll() if flank is raising
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z6_RutscheVoll::rutscheVoll(int flanke) {
	if (flanke > 0) {
		rutscheNichtMehrVoll();
	}
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z6_RutscheVoll::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop call the function setFehlerVonMir(false) if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z6_RutscheVoll::tasteEStop(int flanke){
	if(flanke==0){
		owner->setFehlerVonMir(false);
	}
}
