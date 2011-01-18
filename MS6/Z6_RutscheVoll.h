/*
 * Z6_RutscheVoll.h
 *
 * Created on: 14.12.2010
 *      Author: wehrin_d
 */

#ifndef Z6_RUTSCHEVOLL_H_
#define Z6_RUTSCHEVOLL_H_

#include "Automat.h"
#include "Zustand.h"

class Z6_RutscheVoll : public Zustand  {
public:
	Z6_RutscheVoll(Automat* automat);
	virtual ~Z6_RutscheVoll();
	//void rutscheVoll(int flanke);
	void tasteReset();
	void rutscheVoll(int flanke);
	void rutscheNichtMehrVoll();
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z6_RUTSCHEVOLL_H_ */
