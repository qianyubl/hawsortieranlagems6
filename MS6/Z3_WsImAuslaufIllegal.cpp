/*
 * Z3_WsImAuslaufIllegal.cpp
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#include "Z3_WsImAuslaufIllegal.h"
#include "Z3_KeinWsImAuslauf.h"
#include "HardwareLayer.h"

/**
 * Z3_WsImAuslaufIllegal communicate that error has been found,
 * communicates with channel and set attributes to show that the
 * system is not ok
 *
 * @automat is needed to have the states owner
 */
Z3_WsImAuslaufIllegal::Z3_WsImAuslaufIllegal(Automat* automat){
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	name="Z3_WsImAuslaufIllegal";
	hal->motorStopAn();
	hal->ampelAnstehendUnquittiert();
	quittiert=false;
}

/**
 * tasteReset set receipted true and attribut to show there was somethin wrong
 * 
 */
void Z3_WsImAuslaufIllegal::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
	quittiert=true;
}

/**
 * wsImAuslauf communicate that error is away with the channel
 * set attributes to show that system is ok again, all if flank is raising
 */
void Z3_WsImAuslaufIllegal::wsImAuslauf(int flanke) {
	if (flanke > 0) {//kein  ws im auslauf
		HardwareLayer::getInstance()->sendToChannelFehlerWeg();
		owner->setFehlerVonMir(false);
		// Der anderen Automaten aus dem Wartezustand holen
		owner->setState(new Z3_KeinWsImAuslauf(owner));
		HardwareLayer::getInstance()->motorStopAus();
		if(quittiert){
			if(HardwareLayer::getInstance()->motorRechtsIstAn()){
				HardwareLayer::getInstance()->ampelGruen();
			}
			else{
				HardwareLayer::getInstance()->ampelAus();
			}
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
void Z3_WsImAuslaufIllegal::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flank is the pos or neg bit from the hardware MSG integer
 */
void Z3_WsImAuslaufIllegal::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
