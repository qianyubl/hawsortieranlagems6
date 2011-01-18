/*
 * Z2_KeinWSImEinlauf.h
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#ifndef Z2_KEINWSIMEINLAUF_H_
#define Z2_KEINWSIMEINLAUF_H_

#include "Zustand.h"
#include "Automat.h"

class Z2_KeinWSImEinlauf: public Zustand {
public:
	Z2_KeinWSImEinlauf(Automat* automat);
	virtual ~Z2_KeinWSImEinlauf();
	void wsImEinlauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z2_KEINWSIMEINLAUF_H_ */
