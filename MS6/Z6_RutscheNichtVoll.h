/*
 * Z6_RutscheNichtVoll.h
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#ifndef Z6_RUTSCHENICHTVOLL_H_
#define Z6_RUTSCHENICHTVOLL_H_

#include "Zustand.h"
#include "Automat.h"
#include "Timer.h"

class Z6_RutscheNichtVoll: public Zustand {
public:
	Z6_RutscheNichtVoll(Automat* automat);
	virtual ~Z6_RutscheNichtVoll();
	void rutscheVoll(int flanke);
	void timerAbgelaufen();
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	Timer* timer;
	bool timerStarted;
};

#endif /* Z6_RUTSCHENICHTVOLL_H_ */
