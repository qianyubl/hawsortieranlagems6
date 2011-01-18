/*
 * Z3_KeinWsImAuslauf.h
 *
 * Created on: 13.12.2010
 *      Author: aas998
 */

#ifndef Z3_KEINWSIMAUSLAUF_H_
#define Z3_KEINWSIMAUSLAUF_H_

#include "Zustand.h"
#include "Automat.h"

class Z3_KeinWsImAuslauf: public Zustand {
public:
	Z3_KeinWsImAuslauf(Automat* owner);
	virtual ~Z3_KeinWsImAuslauf();
	void wsImAuslauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z3_KEINWSIMAUSLAUF_H_ */
