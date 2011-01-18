/*
 * Z0_FehlerWarten.cpp
 *
 * Created on: 16.12.2010
 *      Author: wehrin_d
 */

#include "Z0_FehlerWarten.h"

/**
 * Z0_FehlerWarten stores the current owner and owner before
 * 
 */
Z0_FehlerWarten::Z0_FehlerWarten(Zustand* vorher,Automat* owner) {
	this->vorher=vorher;
	this->owner=owner;
	name="Z0_FehlerWarten";
}

/**
 * ~Z0_FehlerWarten is a destructor
 * 
 */
Z0_FehlerWarten::~Z0_FehlerWarten() {}


/**
 * fehlerWeg sets the state to the state before
 * and return from error state with returnFromErrorState
 *
 */
void Z0_FehlerWarten::fehlerWeg(){
	owner->setState(this->vorher);
	this->vorher->returnFromErrorState();
}

/**
 * tasteEStop sets the start state for the owner state
 * if flank is fallen
 *
 */
void Z0_FehlerWarten::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
