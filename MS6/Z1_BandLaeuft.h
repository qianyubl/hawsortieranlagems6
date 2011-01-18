/*
 * Z1_BandLaeuft.h
 *
 * Created on: 10.12.2010
 *      Author: wehrin_d
 */

#ifndef Z1_BANDLAEUFT_H_
#define Z1_BANDLAEUFT_H_

#include "Timer.h"
#include "Automat.h"

class Z1_BandLaeuft: public Zustand {
public:
	Z1_BandLaeuft(Automat* automat);
	// Ereignisse
	void wsImEinlauf(int flanke);
	void timerAbgelaufen();
	void tasteStart();
	void tasteStop();
	void fehler();
	void returnFromErrorState();
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	bool stateActiv;
	Timer* timer;
};

#endif /* Z1_BANDLAEUFT_H_ */
