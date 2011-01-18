/*
 * Z4_WsImHMIllegal.h
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#ifndef Z4_WSIMHMILLEGAL_H_
#define Z4_WSIMHMILLEGAL_H_
#include "Zustand.h"
#include "Automat.h"

class Z4_WsImHMIllegal: public Zustand {
public:
	Z4_WsImHMIllegal(Automat* automat);
	void tasteReset();
	void wsInHoehenMessung(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
	void fehlerGegangen();
private:
	bool quittiert;
};

#endif /* Z4_WSIMHMILLEGAL_H_ */
