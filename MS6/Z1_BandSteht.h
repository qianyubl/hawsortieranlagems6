/*
 * Z1_BandSteht.h
 *
 * Created on: 10.12.2010
 *      Author: wehrin_d
 */

#ifndef Z1_BANDSTEHT_H_
#define Z1_BANDSTEHT_H_

#include "Automat.h"
#include "Zustand.h"

class Z1_BandSteht : public Zustand {
public:
	Z1_BandSteht(Automat* automat);
	void wsImEinlauf(int flanke);
	void wsKommtVonBand1();
	void tasteStart();
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z1_BANDSTEHT_H_ */
