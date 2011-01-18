/*
 * Z5_WsInWeicheIllegal.h
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#ifndef Z5_WSINWEICHEILLEGAL_H_
#define Z5_WSINWEICHEILLEGAL_H_

#include "Zustand.h"
#include "Automat.h"

class Z5_WsInWeicheIllegal: public Zustand {
public:
	Z5_WsInWeicheIllegal(Automat* automat);
	void tasteReset();
	void wsInWeiche(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);

private:
	bool quittiert;
};

#endif /* Z5_WSINWEICHEILLEGAL_H_ */
