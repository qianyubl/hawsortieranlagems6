/*
 * Z4_Hoehenmessung.h
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#ifndef Z4_HOEHENMESSUNG_H_
#define Z4_HOEHENMESSUNG_H_

#include "Zustand.h"
#include "Automat.h"

class Z4_Hoehenmessung: public Zustand {
public:
	Z4_Hoehenmessung(Automat* automat);
	virtual ~Z4_Hoehenmessung();
	void wsInHoehenMessung(int flanke);
	void hoeheBereich1(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z4_HOEHENMESSUNG_H_ */
