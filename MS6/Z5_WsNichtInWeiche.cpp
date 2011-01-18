/*
 * Z5_WsNichtInWeiche.cpp
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#include "Z5_WsNichtInWeiche.h"
#include "HardwareLayer.h"
#include "WerkstueckListe.h"
#include "Z0_FehlerWarten.h"
#include "Z5_WsInWeicheIllegal.h"
int TIME_OPEN =  80; // * 10ms = 800ms

/**
 * Z5_WsNichtInWeiche sets a new timer and restart it
 * 
 */
Z5_WsNichtInWeiche::Z5_WsNichtInWeiche(Automat* automat) {
	owner=automat;
	name="Z5_WsNichtInWeiche";
	timer= new Timer(this);
	timer->setMax(TIME_OPEN);
	timer->start(0);
	timer->hold();
	timerRest=0;
}

/**
 * ~Z5_WsNichtInWeiche is destructor
 * 
 */
Z5_WsNichtInWeiche::~Z5_WsNichtInWeiche() {}

/**
 * timerAbgelaufen call function weicheZu() and hold timer
 * 
 */
void Z5_WsNichtInWeiche::timerAbgelaufen(){
	HardwareLayer::getInstance()->weicheZu();
	timer->hold();
}

/**
 * fehler makes a timestamp and assign the rest of the timer
 * 
 */
void Z5_WsNichtInWeiche::fehler(){
	timerRest=(TIME_OPEN-timer->getValue());
	if(timerRest<0)timerRest=0;
	//printf("Z5_WsNichtInWeiche::fehler -> timerRest=%d",timerRest);
	timer->hold();

}

/**
 * returnFromErrorState continue timer rest
 * 
 */
void Z5_WsNichtInWeiche::returnFromErrorState(){
	if(timerRest>0 && timerRest<=TIME_OPEN){
		timer->setValue(timerRest); // * 10 ms
		timer->reset();
		timer->cont();
	}
	timerRest=0;

}

/**
 * wsInWeiche decide between number of band checks if ws is too early
 * and shows that the system is ok
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z5_WsNichtInWeiche::wsInWeiche(int flanke){
	if(flanke==0){
		HardwareLayer* hal = HardwareLayer::getInstance();
		WerkstueckListe* liste=WerkstueckListe::getInstance();
		Werkstueck* w=NULL;
		int wsPosi=0;
		if(hal->getBandNr()==1)wsPosi=liste->getLastWsWithStation(STATION_EINLAUF);
		else if(hal->getBandNr()==2) wsPosi=liste->getLastWsWithStation(STATION_HOEHENMESSUNG);
		else printf("Z5_WsNichtInWeiche-> FEHLER: BAND = %d\n",hal->getBandNr());
		if(wsPosi==-1){
			//printf("Z5_WsNichtInWeiche->EIN FEHLER ist aufgetreten! ws ist null\n");
			printf("ws zu frueh in weiche\n");
			owner->setState(new Z5_WsInWeicheIllegal(owner));
		}
		else if( (hal->getBandNr()==1) ){
			w=liste->getWsAt(wsPosi);
			if(w->ok==WS_OK){
				w->setLetzteStation(STATION_WEICHE);
				hal->ampelGruen();// anzeige Ws wird nicht aussortiert
				hal->weicheAuf();
				timer->reset();
				timer->cont();
				w->setTimestamp(Timer::getTimeStamp());
			}
			else{
				long delta= (Timer::getTimeStamp()-w->getTimestamp());
				//printf("weiche delta = %ld\n",delta);
				if( delta <=  3000 ){
					printf("ws zu frueh in weiche\n");
					owner->setState(new Z5_WsInWeicheIllegal(owner));
					// fehler zustand
					// user sagen er solls runter nehmen
					// reset usw.
				}
				else{
					w->setTimestamp(Timer::getTimeStamp());
					w->setLetzteStation(STATION_WEICHE);
					hal->ampelGelb();// anzeige Ws wird aussortiert

					//liste->eraseWsAt(wsPosi);// ws löschen
					//hal->sendWsVomBandRunter();
				}
			}
		}
		else if( (hal->getBandNr()==2) ){
				w=liste->getWsAt(wsPosi);
				long delta= (Timer::getTimeStamp()-w->getTimestamp());
				if(    (hal->getBandNr()==1) &&  (delta <=  3000)  ){
					printf("ws zu frueh in weiche\n");
					owner->setState(new Z5_WsInWeicheIllegal(owner));
					// fehler zustand
					// user sagen er solls runter nehmen
					// reset usw.
				}
				else{
					w->setLetzteStation(STATION_WEICHE);
					w->setTimestamp(Timer::getTimeStamp());
					//w->printIt();
					if(w->ok==WS_OK){
						hal->ampelGruen();// anzeige Ws wird nicht aussortiert
						hal->weicheAuf();
						timer->reset();
						timer->cont();
					}
					else{
						hal->ampelGelb();// anzeige Ws wird aussortiert
						//hal->sendWsVomBandRunter();
						//liste->eraseWsAt(wsPosi);// ws löschen
					}
				}
		}
	}

}

/**
 * WsVerschwunden sets the state to start state
 * 
 */
void Z5_WsNichtInWeiche::WsVerschwunden(){
	owner->setStartState();
}

/**
 * tasteEStop sets the state to start state if flank is fallen
 * 
 * @flanke sets the state to start state
 */
void Z5_WsNichtInWeiche::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}
