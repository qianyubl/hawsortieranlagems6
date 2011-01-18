/*
 * Z0_FehlerWarten.h
 *
 * Created on: 16.12.2010
 *      Author: wehrin_d
 */

#ifndef Z0_FEHLERWARTEN_H_
#define Z0_FEHLERWARTEN_H_

#include "Zustand.h"
#include "Automat.h"

class Z0_FehlerWarten : public Zustand {
public:
	Z0_FehlerWarten(Zustand* vorher,Automat* owner);
	virtual ~Z0_FehlerWarten();
	void fehlerWeg();
	void tasteEStop(int flanke);
private:
	Zustand* vorher;
};

#endif /* Z0_FEHLERWARTEN_H_ */
