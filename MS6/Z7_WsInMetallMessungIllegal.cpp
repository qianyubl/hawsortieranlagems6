/*
 * Z7_WsInMetallMessungIllegal.cpp
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#include "Z7_WsInMetallMessungIllegal.h"
#include "Z7_MetallMessung.h"
#include "HardwareLayer.h"

/**
 * Z7_WsInMetallMessungIllegal communicate to channel that error exist,
 * red light is off and call function ampelAnstehendUnquittiert()
 * set receipted to false
 *
 * @automat is needed to have the states owner
 */
Z7_WsInMetallMessungIllegal::Z7_WsInMetallMessungIllegal(Automat* automat) {
	owner=automat;
	HardwareLayer* hal=HardwareLayer::getInstance();
	owner->setFehlerVonMir(true);
	hal->sendToChannelFehler();
	// Der anderen Automaten sagt geht in Wartezustand ich hab n Fehler nämlich RutscheVoll
	name="Z7_WsInMetallMessungIllegal";
	hal->motorAus();
	hal->ampelAnstehendUnquittiert();
	quittiert=false;
}

/**
 * tasteReset sets light red and receipted to true
 * 
 */
void Z7_WsInMetallMessungIllegal::tasteReset(){
	HardwareLayer::getInstance()->ampelRot();
	quittiert=true;
}

/**
 * wsMetall communicate with channel that error is away
 * and checks receipted and show it, all if flank is fallen
 *
 * @flanke is the pos or neg bit from the hardware MSG integer 
 */
void Z7_WsInMetallMessungIllegal::wsMetall(int flanke) {
	if (flanke == 0) {//kein  ws in weiche
		HardwareLayer::getInstance()->sendToChannelFehlerWeg();
		owner->setFehlerVonMir(false);
		// Der anderen Automaten aus dem Wartezustand holen
		owner->setState(new Z7_MetallMessung(owner));
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
void Z7_WsInMetallMessungIllegal::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z7_WsInMetallMessungIllegal::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
