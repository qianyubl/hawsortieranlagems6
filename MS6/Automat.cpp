#include "Automat.h"
#include "Z0_FehlerWarten.h"
#include "Z1_BandLaeuft.h"
#include "Z1_BandSteht.h"
#include "Z2_KeinWSImEinlauf.h"
#include "Z2_WsImEinlauf.h"
#include "Z3_KeinWsImAuslauf.h"
#include "Z3_Warten.h"
#include "Z4_Hoehenmessung.h"
#include "Z5_WsNichtInWeiche.h"
#include "Z6_RutscheNichtVoll.h"
#include "Z6_RutscheVoll.h"
#include "Z7_MetallMessung.h"
#include "Z8_BandBelegt.h"
#include "Z8_BandFrei.h"
#include "Z9_WsVerschwunden.h"
#include "Z10_Estop.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"
#include <stdio.h>



/**
 * Automat is
 * 
 */
Automat::Automat(int automatNr) {
	this->automatNr=automatNr;
	setStartState();
	fehlerVonMir=false;
}
/**
 * setStartState is
 * 
 */
void Automat::setStartState(){
	// Instanziierung des konkreten Automaten...
	fehlerVonMir=false;
	if(automatNr==1){
		theState=new Z1_BandSteht(this);
	}
	else if(automatNr==2){
		theState=new Z2_KeinWSImEinlauf(this);
	}
	else if(automatNr==3){
		theState=new Z3_KeinWsImAuslauf(this);
	}
	else if(automatNr==4){
		theState=new Z4_Hoehenmessung(this);
	}
	else if(automatNr==5){
		theState=new Z5_WsNichtInWeiche(this);
	}
	else if(automatNr==6){
		if(!(HardwareLayer::getInstance()->getRutscheVoll())){
			theState= new Z6_RutscheVoll(this);
		}
		else{
			theState= new Z6_RutscheNichtVoll(this);
		}
	}
	else if(automatNr==7){
		theState= new Z7_MetallMessung(this);
	}
	else if(automatNr==8){
		theState=new Z8_BandFrei(this);
	}
	else if(automatNr==9){
		theState=new Z9_WsVerwunden(this);
	}
	else if(automatNr==10){
		theState=new Z10_Estop(this);
	}
	else{
		printf("Automat mit der Nr %d existiert nicht!\n",automatNr);
	}
}

// ------------ Get / Set

/**
 * setState is
 * 
 */
void Automat::setState(Zustand* state){
	delete theState;
	theState=state;
}

/**
 * printState is
 * 
 */
void Automat::printState(){
	cout << theState->name << endl;
}

/**
 * setFehlerVonMir is
 * 
 */
void Automat::setFehlerVonMir(bool f){
	this->fehlerVonMir=f;
}
/**
 * getFehlerVonMir is
 * 
 */
bool Automat::getFehlerVonMir(){
	return this->fehlerVonMir;
}

/**
 * getAutomatNr is
 * 
 */
int Automat::getAutomatNr(){
	return this->automatNr;
}

// ------------------ Ereignisse - werden an konkreten aktuellen Zustand weitergereicht

/**
 * wsImEinlauf is a function to send the flank to the right state
 * 
 */
void Automat::wsImEinlauf(int flanke){
	theState->wsImEinlauf(flanke);
}

/**
 * wsInHoehenMessung is a function to send the flank to the right state
 * 
 */
void Automat::wsInHoehenMessung(int flanke){
	theState->wsInHoehenMessung(flanke);
}

/**
 * hoeheBereich1 is a function to send the flank to the right state
 * 
 */
void Automat::hoeheBereich1(int flanke){
	theState->hoeheBereich1(flanke);
}

/**
 * wsInWeiche is a function to send the flank to the right state
 * 
 */
void Automat::wsInWeiche(int flanke){
	theState->wsInWeiche(flanke);
}

/**
 * wsMetall is a function to send the flank to the right state
 * 
 */
void Automat::wsMetall(int flanke){
	theState->wsMetall(flanke);
}

/**
 * weicheOffen is a function to send the flank to the right state
 * 
 */
void Automat::weicheOffen(int flanke){
	theState->weicheOffen(flanke);
}

/**
 * rutscheVoll is a function to send the flank to the right state
 * 
 */
void Automat::rutscheVoll(int flanke){
	theState->rutscheVoll(flanke);
}

/**
 * wsImAuslauf is a function to send the flank to the right state
 * 
 */
void Automat::wsImAuslauf(int flanke){
	theState->wsImAuslauf(flanke);
}

/**
 * tasteStart is a function to start the function with the right state
 * 
 */
void Automat::tasteStart(){
	theState->tasteStart();
}

/**
 * tasteStop is a function to start the function with the right state
 * 
 */
void Automat::tasteStop(){
	theState->tasteStop();
}

/**
 * tasteReset is a funktion to start the function with the right state
 * 
 */
void Automat::tasteReset(){
	theState->tasteReset();
}

/**
 * tasteEStop is a function to send the flank to the right state
 * 
 */
void Automat::tasteEStop(int flanke){
	theState->tasteEStop(flanke);
}

/**
 * band2Frei is a function to start the function with the right state
 * 
 */
void Automat::band2Frei(){
	theState->band2Frei();
}

/**
 * band2Belegt is a function to start the function with the right state
 * 
 */
void Automat::band2Belegt(){
	theState->band2Belegt();
}

/**
 * fehler saves time stamps and goes into the "fehler" state
 * 
 */
void Automat::fehler(){
	if(automatNr==1)WerkstueckListe::getInstance()->saveTimestampAtStop();
	HardwareLayer::getInstance()->WsVerschwundenThreadActiv(false);
	if(!fehlerVonMir){
		//if(automatNr==1 || automatNr==5){ // bei Band_steht
		if(automatNr!=10 && automatNr!=8 ){ // bei Band_steht
			if(HardwareLayer::getInstance()->getBandNr()==2 && automatNr==2 ){
				return;
			}
			theState->fehler();
			theState=new Z0_FehlerWarten(theState,this);
		}
		// TODO für andere Automaten
	}
}

/**
 * fehlerWeg is a function to refresh the time stamps and go into a thread if vending machine is 1
 * also it goes into the "fehlerWeg" function with the right state
 */
void Automat::fehlerWeg(){
	if(automatNr==1){
		WerkstueckListe::getInstance()->refreshTimestamps();
		HardwareLayer::getInstance()->WsVerschwundenThreadActiv(true);
	}

	theState->fehlerWeg();
}

/**
 * timerAbgelaufen is a function to start the function with the right state
 * 
 */
void Automat::timerAbgelaufen(){
	theState->timerAbgelaufen();
}

/**
 * wsKommtVonBand1 is a function to start the function with the right state
 * 
 */
void Automat::wsKommtVonBand1(){
	theState->wsKommtVonBand1();
}

/**
 * wsVomBandRunter is a function to start the function with the right state
 * 
 */
void Automat::wsVomBandRunter (){
	theState->wsVomBandRunter();
}

/**
 * WsVerschwunden is a function to start the function with the right state
 * 
 */
void Automat::WsVerschwunden(){
	theState->WsVerschwunden();
}