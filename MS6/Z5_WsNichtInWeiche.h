/*
 * Z5_WsNichtInWeiche.h
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#ifndef Z5_WSNICHTINWEICHE_H_
#define Z5_WSNICHTINWEICHE_H_

#include "Zustand.h"
#include "Automat.h"
#include "Timer.h"

class Z5_WsNichtInWeiche: public Zustand {
public:
	Z5_WsNichtInWeiche(Automat* automat);
	virtual ~Z5_WsNichtInWeiche();
	void wsInWeiche(int flanke);
	void timerAbgelaufen();
	void fehler();
	void returnFromErrorState();
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	Timer* timer;
	int timerRest;
	bool timerRunning;
};

#endif /* Z5_WSNICHTINWEICHE_H_ */
