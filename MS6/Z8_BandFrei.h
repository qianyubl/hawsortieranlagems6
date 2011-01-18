/*
 * Z8_BandFrei.h
 *
 * Created on: 17.12.2010
 *      Author: wehrin_d
 */

#ifndef Z8_BANDFREI_H_
#define Z8_BANDFREI_H_

#include "Zustand.h"
#include "Automat.h"

class Z8_BandFrei: public Zustand {
public:
	Z8_BandFrei(Automat* automat);
	void wsImEinlauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
	void wsVomBandRunter();
};

#endif /* Z8_BANDFREI_H_ */
