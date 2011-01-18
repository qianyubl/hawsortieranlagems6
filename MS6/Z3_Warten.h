/*
 * Z3_Warten.h
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#ifndef Z3_WARTEN_H_
#define Z3_WARTEN_H_

#include "Zustand.h"
#include "Automat.h"

class Z3_Warten: public Zustand {
public:
	Z3_Warten(Automat* owner);
	virtual ~Z3_Warten();
	void band2Frei();
	void wsImAuslauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z3_WARTEN_H_ */
