/*
 * WsVerschwundenThread.cpp
 *
 * Created on: 06.01.2011
 *      Author: wehrin_d
 */

#include "WsVerschwundenThread.h"
#include <unistd.h>
#include "Werkstueck.h"
#include "WerkstueckListe.h"
#include "Timer.h"
#include "HardwareLayer.h"

/**
 * WsVerschwundenThread is constructor sets active to trueh
 * 
 */
WsVerschwundenThread::WsVerschwundenThread() {
	this->activ=true;

}

/**
 * ~WsVerschwundenThread is destructor
 * 
 */
WsVerschwundenThread::~WsVerschwundenThread() {
}

/**
 * setActiv sets activ to param
 * 
 * @a the value to set
 */
void WsVerschwundenThread::setActiv(bool a){
	this->activ=a;
}

/**
 * wsIstVerschwunden prints that a ws is dissapeared
 * 
 */
void WsVerschwundenThread::wsIstVerschwunden(){
	HardwareLayer* hal = HardwareLayer::getInstance();
	printf("Werkstueck verschwunden! Bitte die Anlage leer rauemen!\n");
	hal->sendWsVerschwunden();
}


/**
 * execute is main routine polling whether ws is over time
 * 
 */
void WsVerschwundenThread::execute(void*){
	WerkstueckListe* wsl = WerkstueckListe::getInstance();
	Werkstueck* w=NULL;
	HardwareLayer* hal = HardwareLayer::getInstance();
	long delta= 0;

	while(!isStopped()){
		if (activ) {
			for (int i = 0; i < wsl->size(); i++) {
				w = wsl->getWsAt(i);
				delta = (Timer::getTimeStamp() - w->getTimestamp());

				if ((delta >= 4200) && (w->getLetzteStation()
						== STATION_EINLAUF) && (hal->getBandNr() == 1)) {
					wsIstVerschwunden();
				}
				else if ((delta >= 2700) && (w->getLetzteStation()
						== STATION_WEICHE) && (hal->getBandNr() == 1)) {
					wsIstVerschwunden();
				}
				else if ((delta >= 3000) && (w->getLetzteStation()
						== STATION_EINLAUF) && (hal->getBandNr() == 2)) {
					wsIstVerschwunden();
				}
				else if ((delta >= 2000) && (w->getLetzteStation()
						== STATION_HOEHENMESSUNG) && (hal->getBandNr() == 2)) {
					wsIstVerschwunden();
				}
				else if ((delta >= 2600) && (w->getLetzteStation()
						== STATION_WEICHE) && (hal->getBandNr() == 2)) {
					wsIstVerschwunden();
				}

			}
			usleep(1000*10);// 10 ms
		}

	}
}

/**
 * shutdown have to implemented, because it's virtual
 * 
 */
void WsVerschwundenThread::shutdown(){}
