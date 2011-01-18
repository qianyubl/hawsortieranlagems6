/*
 * Z8_BandBelegt.cpp
 *
 * Created on: 17.12.2010
 *      Author: wehrin_d
 */

#include "Z8_BandBelegt.h"
#include "HardwareLayer.h"
#include "Z8_BandFrei.h"
#include "WerkstueckListe.h"

/**
 * Z8_BandBelegt sets the owner of automat
 * 
 * @automat is needed to have the states owner
 */
Z8_BandBelegt::Z8_BandBelegt(Automat* automat) {
	owner=automat;
	name="Z8_BandBelegt";

}
/**
 * wsVomBandRunter sends to the comport a 'r' and sets
 * state to "band frei"
 *
 */
void Z8_BandBelegt::wsVomBandRunter(){
		string s = "r";
		HardwareLayer::getInstance()->ComPortWrite(s.c_str());
		owner->setState(new Z8_BandFrei(owner));
}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z8_BandBelegt::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z8_BandBelegt::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}

/**
 * rutscheVoll if band number 2 check the station and 
 * send to comport a 'r' and erase ws, all if flank is raised
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z8_BandBelegt::rutscheVoll(int flanke) {
	if (flanke > 0) {
		if (HardwareLayer::getInstance()->getBandNr() == 2) {
			WerkstueckListe* liste = WerkstueckListe::getInstance();
			int wsPosi = liste->getLastWsWithStation(STATION_RUTSCHE);

			if (wsPosi >= 0) {
				string s = "r";
				HardwareLayer::getInstance()->ComPortWrite(s.c_str());
				liste->eraseWsAt(wsPosi);// ws löschen
				owner->setState(new Z8_BandFrei(owner));
			}
		}

	}
}
