/*
 * Z8_BandBelegt.h
 *
 * Created on: 17.12.2010
 *      Author: wehrin_d
 */

#ifndef Z8_BANDBELEGT_H_
#define Z8_BANDBELEGT_H_

#include "Zustand.h"
#include "Automat.h"

class Z8_BandBelegt: public Zustand {
public:
	Z8_BandBelegt(Automat* automat);
	void wsVomBandRunter();
	void WsVerschwunden();
	void tasteEStop(int flanke);
	void rutscheVoll(int flanke);
};

#endif /* Z8_BANDBELEGT_H_ */
