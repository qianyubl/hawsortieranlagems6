/*
 * Z3_KeinWsImAuslauf.cpp
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#include "Z3_KeinWsImAuslauf.h"
#include "WerkstueckListe.h"
#include "Werkstueck.h"
#include "HardwareLayer.h"
#include "Z3_Warten.h"
#include "Timer.h"
#include "Z3_WsImAuslaufIllegal.h"

/**
 * Z3_KeinWsImAuslauf sets the state owner and name
 * 
 * @automat is needed to have the states owner
 */
Z3_KeinWsImAuslauf::Z3_KeinWsImAuslauf(Automat* automat) {
	owner = automat;
	name = "Z3_KeinWsImAuslauf";

}

/**
 * ~Z3_KeinWsImAuslauf is destructor
 * 
 */
Z3_KeinWsImAuslauf::~Z3_KeinWsImAuslauf() {
}

/**
 * wsImAuslauf checks wheter ws is too early or it should be taken
 * away when flank is fallen
 *
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z3_KeinWsImAuslauf::wsImAuslauf(int flanke) {
	if (flanke == 0) {// ws im auslauf
		WerkstueckListe* liste = WerkstueckListe::getInstance();
		int wsPosi = liste->getLastWsWithStation(STATION_WEICHE);
		if (wsPosi >= 0) {
			Werkstueck* w = liste->getWsAt(wsPosi);
			long delta = (Timer::getTimeStamp() - w->getTimestamp());
			if (delta <= 1700) {
				printf("ws zu frueh in auslauf\n");
				owner->setState(new Z3_WsImAuslaufIllegal(owner));

				// fehler zustand
				// user sagen er solls runter nehmen
				// reset usw.
			} else {
				w->setLetzteStation(STATION_AUSLAUF);
				//printf(" auslauf timestamp: %ld\n",Timer::getTimeStamp());
				HardwareLayer* hal = HardwareLayer::getInstance();
				if (hal->getBandNr() == 1 && hal->getBand2Ready()) {
						liste->eraseWsAt(wsPosi);
						hal->sendWsZuBand2();

				} else {
					owner->setFehlerVonMir(true);
					hal->sendToChannelFehler();
					hal->motorAus();
					owner->setState(new Z3_Warten(owner));
				}
			}

		}
		else{
			printf("ws zu frueh in auslauf\n");
			owner->setState(new Z3_WsImAuslaufIllegal(owner));
		}

	}

}

/**
 * WsVerschwunden set state to start state
 * 
 */
void Z3_KeinWsImAuslauf::WsVerschwunden(){
	owner->setStartState();
}
/**
 * tasteEStop set state to start state if flank is fallen
 * 
 * @flanke is the pos or neg bit from the hardware MSG integer
 */
void Z3_KeinWsImAuslauf::tasteEStop(int flanke){
	if(flanke==0){
		owner->setStartState();
	}
}