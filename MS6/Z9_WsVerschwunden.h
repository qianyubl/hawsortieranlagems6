/*
 * Z9_WsVerwunden.h
 *
 * Created on: 13.01.2011
 *      Author: wehrin_d
 */

#ifndef Z9_WSVERWUNDEN_H_
#define Z9_WSVERWUNDEN_H_

#include "Zustand.h"

class Z9_WsVerwunden: public Zustand {
public:
	Z9_WsVerwunden(Automat* automat);
	void WsVerschwunden();
	void blockierDieAnderen();
	void blockierungWegNehmen();
	void tasteReset();
	void tasteEStop(int flanke);
private:
	bool wsVerschwunden;

};

#endif /* Z9_WSVERWUNDEN_H_ */
