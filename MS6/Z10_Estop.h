/*
 * Z10_Estop.h
 *
 * Created on: 13.01.2011
 *      Author: wehrin_d
 */

#ifndef Z10_ESTOP_H_
#define Z10_ESTOP_H_

#include "Zustand.h"
#include "Automat.h"

class Z10_Estop: public Zustand {
public:
	Z10_Estop(Automat* automat);

	void tasteEStop(int flanke);

	void blockierDieAnderen();
	void blockierungWegNehmen();

private:
	bool estop;




};

#endif /* Z10_ESTOP_H_ */
