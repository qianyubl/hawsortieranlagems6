/*
 * Z4_WsImHMIllegal.cpp
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#include "Z4_WsImHMIllegal.h"
#include "Z4_Hoehenmessung.h"
#include "HardwareLayer.h"

/**
 * Z4_WsImHMIllegal communicate with channel and set error,
 * stops motor and execute function "ampel anstehend unquittiert", receipted is assigned
 * to false
 *
 * @automat is needed to have the states owner
 */
Z4_WsImHMIllegal::Z4_WsImHMIllegal(Automat* automat) {
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll ////////WHAT?
	name="Z4_WsImHMIllegal";
	hal->motorStopAn();
	hal->ampelAnstehendUnquittiert();
	quittiert=false;
}

/**
 * tasteReset sets the ligth red and receipted to true
 * 
 */
void Z4_WsImHMIllegal::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
	quittiert=true;
}
/**
 * fehlerGegangen communicate to channel that error is away
 * set state to "hoehenmessung"
 *
 */
void Z4_WsImHMIllegal::fehlerGegangen(){
	HardwareLayer::getInstance()->motorStopAus();
	HardwareLayer::getInstance()->sendToChannelFehlerWeg();
	owner->setFehlerVonMir(false);
	// Der anderen Automaten aus dem Wartezustand holen
	owner->setState(new Z4_Hoehenmessung(owner));

	if(HardwareLayer::getInstance()->motorRechtsIstAn()){
		HardwareLayer::getInstance()->ampelGruen();
	}
	else{
		HardwareLayer::getInstance()->ampelAus();
	}
}

/**
 * wsInHoehenMessung execute function fehlerGegangen if flank is fallen
 *
 * @flanke is the pos or neg bit from the hardware MSG integer 
 */
void Z4_WsImHMIllegal::wsInHoehenMessung(int flanke) {
	if (flanke > 0) {//kein  ws im auslauf
		fehlerGegangen();
	}
}
/**
 * WsVerschwunden sets state "ws verschwunden"
 * 
 */
void Z4_WsImHMIllegal::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z4_WsImHMIllegal::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
