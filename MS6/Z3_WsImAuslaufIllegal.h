/*
 * Z3_WsImAuslaufIllegal.h
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#ifndef Z3_WSIMAUSLAUFILLEGAL_H_
#define Z3_WSIMAUSLAUFILLEGAL_H_

#include "Zustand.h"
#include "Automat.h"

class Z3_WsImAuslaufIllegal: public Zustand {
public:
	Z3_WsImAuslaufIllegal(Automat* automat);
	void tasteReset();
	void wsImAuslauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	bool quittiert;
};

#endif /* Z3_WSIMAUSLAUFILLEGAL_H_ */
