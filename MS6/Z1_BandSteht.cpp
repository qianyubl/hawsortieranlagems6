/*
 * Z1_BandSteht.cpp
 *
 * Created on: 10.12.2010
 *      Author: wehrin_d
 */

#include "Z1_BandSteht.h"
#include "Z1_BandLaeuft.h"
#include "HardwareLayer.h"
#include "Z0_FehlerWarten.h"
#include "Automat.h"


/**
 * Z1_BandSteht set attributes to show that the machine stops
 * 
 */
Z1_BandSteht::Z1_BandSteht(Automat* automat){
	owner=automat;
	//Lampe grün aus
	//Motor aus
	if(!HardwareLayer::getInstance()->eStopGedrueckt())HardwareLayer::getInstance()->ampelAus();
	HardwareLayer::getInstance()->motorAus();
	name="Z1_BandSteht";

}

/**
 * wsImEinlauf set the attributes to show that the sysem is ok
 * set state to "band laeuft"
 */
void Z1_BandSteht::wsImEinlauf(int flanke){
	HardwareLayer::getInstance()->motorAn();
	HardwareLayer::getInstance()->ampelGruen();
	owner->setState(new Z1_BandLaeuft(owner));
}

/**
 * wsKommtVonBand1 starts the band 2 if note was send from band 1
 * 
 */
void Z1_BandSteht::wsKommtVonBand1(){
	if(HardwareLayer::getInstance()->getBandNr()==2){
		HardwareLayer::getInstance()->motorAn();
		HardwareLayer::getInstance()->ampelGruen();
		owner->setState(new Z1_BandLaeuft(owner));
	}
}

/**
 * tasteStart sets the state to "band laeuft"
 * 
 */
void Z1_BandSteht::tasteStart(){
	owner->setState(new Z1_BandLaeuft(owner));
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z1_BandSteht::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 */
void Z1_BandSteht::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}


