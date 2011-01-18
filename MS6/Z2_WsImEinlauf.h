/*
 * Z2_WsImEinlauf.h
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#ifndef Z2_WSIMEINLAUF_H_
#define Z2_WSIMEINLAUF_H_

#include "Zustand.h"
#include "WerkstueckListe.h"
#include "Werkstueck.h"
#include "Automat.h"

class Z2_WsImEinlauf: public Zustand {
public:
	Z2_WsImEinlauf(Automat* automat);
	virtual ~Z2_WsImEinlauf();
	void wsImEinlauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	Werkstueck* ws;
};

#endif /* Z2_WSIMEINLAUF_H_ */
