/*
 * Z7_WsInMetallMessungIllegal.h
 *
 * Created on: 04.01.2011
 *      Author: wehrin_d
 */

#ifndef Z7_WSINMETALLMESSUNGILLEGAL_H_
#define Z7_WSINMETALLMESSUNGILLEGAL_H_

#include "Zustand.h"

class Z7_WsInMetallMessungIllegal: public Zustand {
public:
	Z7_WsInMetallMessungIllegal(Automat* automat);
	void tasteReset();
	void wsMetall(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
private:
	bool quittiert;

};

#endif /* Z7_WSINMETALLMESSUNGILLEGAL_H_ */
