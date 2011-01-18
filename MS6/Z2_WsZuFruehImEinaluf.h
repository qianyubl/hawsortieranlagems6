/*
 * Z2_WsZuFruehImEinaluf.h
 *
 * Created on: 03.01.2011
 *      Author: wehrin_d
 */

#ifndef Z2_WSZUFRUEHIMEINALUF_H_
#define Z2_WSZUFRUEHIMEINALUF_H_

#include "Zustand.h"
#include "Automat.h"

class Z2_WsZuFruehImEinaluf: public Zustand {
public:
	Z2_WsZuFruehImEinaluf(Automat* automat);

	void tasteReset();
	void wsImEinlauf(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);

private:
	bool quittiert;
};

#endif /* Z2_WSZUFRUEHIMEINALUF_H_ */
