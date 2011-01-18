/*
 * Z8_BandFrei.cpp
 *
 * Created on: 17.12.2010
 *      Author: wehrin_d
 */

#include "Z8_BandFrei.h"
#include "HardwareLayer.h"
#include "Z8_BandBelegt.h"

/**
 * Z8_BandFrei sets the state owner and name
 * 
 * @automat is needed to have the states owner
 */
Z8_BandFrei::Z8_BandFrei(Automat* automat){
	owner=automat;
	name="Z8_BandFrei";
//	string s = "r";
//	HardwareLayer::getInstance()->ComPortWrite(s.c_str());

}
/**
 * wsImEinlauf send with comport a 'n' and set state
 * to "band belegt" if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z8_BandFrei::wsImEinlauf(int flanke){
	if(flanke==0){
		string s ="n";
		HardwareLayer::getInstance()->ComPortWrite(s.c_str());
		owner->setState(new Z8_BandBelegt(owner));
	}
}
/**
 * wsVomBandRunter send with comport a 'r' and set state
 * to "band frei"
 */
void Z8_BandFrei::wsVomBandRunter(){
		string s = "r";
		HardwareLayer::getInstance()->ComPortWrite(s.c_str());
		owner->setState(new Z8_BandFrei(owner));
}
/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z8_BandFrei::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z8_BandFrei::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
