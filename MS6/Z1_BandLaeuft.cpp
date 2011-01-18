/*
 * Z1_BandLaeuft.cpp
 *
 * Created on: 10.12.2010
 *      Author: wehrin_d
 */

#include "Z1_BandLaeuft.h"
#include "HardwareLayer.h"
#include "Z1_BandSteht.h"
#include "Z0_FehlerWarten.h"
#include "WerkstueckListe.h"

/**
 * Z1_BandLaeuft sets a timer and the right attributes to guarantee
 * that the user sees, that the system is ok now
 *
 */
Z1_BandLaeuft::Z1_BandLaeuft(Automat* automat) {
	owner=automat;
	name="Z1_BandLaeuft";
	HardwareLayer::getInstance()->motorAn();
	HardwareLayer::getInstance()->ampelGruen();
	timer= new Timer(this);
	timer->setMax(1000); // 10 sec
	timer->start(0);
	timer->hold();
	timer->reset();
	timer->cont();
	stateActiv=true;

	//Starte Timer
	//Lampe Grün
	//Motor rechts
}
/**
 * tasteStart restarts the timer
 * 
 */
void Z1_BandLaeuft::tasteStart(){
	timer->hold();
	timer->reset();
	timer->cont();
}


/**
 * wsImEinlauf restarts the timer
 * 
 */
void Z1_BandLaeuft::wsImEinlauf(int flanke){
	timer->hold();
	timer->reset();
	timer->cont();
}
/**
 * timerAbgelaufen sets the state to "band steht" if state activ
 * else timer reset
 *
 */
void Z1_BandLaeuft::timerAbgelaufen(){
	if(stateActiv){
		if(WerkstueckListe::getInstance()->isEmpty()){
			owner->setState(new Z1_BandSteht(owner));
		}
		else{
			timer->reset();
			timer->setMax(1000); // 10 sec
			timer->cont();
		}
	}

}

/**
 * tasteStop set all attributes, to see that the system is
 * not ok an go into state "band steht"
 * reset the timer
 * if band is not empty show a message
 *
 */
void Z1_BandLaeuft::tasteStop(){
	if(WerkstueckListe::getInstance()->isEmpty()){
		timer->hold();
		timer->reset();
		HardwareLayer::getInstance()->motorAus();
		owner->setState(new Z1_BandSteht(owner));
	}
	else{
		printf("Band kann nicht angehalten werden, es befinden sich noch Werkstuecke drauf\n");
	}

}
/**
 * fehler stops the timer and delete it
 * stateActiv assigned to false
 */
void Z1_BandLaeuft::fehler(){
	stateActiv=false;
	if(!owner->getFehlerVonMir()){
		timer->stop();
		timer->join();
		//timer->stopIt();
		delete timer;
	}
}
/**
 * returnFromErrorState sets the max time and restart the timer
 * stateActiv assigned to true
 *
 */
void Z1_BandLaeuft::returnFromErrorState(){
	stateActiv=true;
	timer= new Timer(this);
		timer->setMax(1000); // 10 sec
		timer->start(0);
		timer->hold();
		timer->reset();
		timer->cont();

	if(!WerkstueckListe::getInstance()->isEmpty()){
		timer->reset();
		timer->setMax(1000); // 10 sec
		timer->cont();
	}
	else{
		timer->reset();
		timer->setMax(700); // 7 sec
		timer->cont();
		//owner->setState(new Z1_BandSteht(owner));
	}
}

/**
 * WsVerschwunden sets the state to "start state"
 * 
 */
void Z1_BandLaeuft::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop sets the state to "start state"
 * 
 */
void Z1_BandLaeuft::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
