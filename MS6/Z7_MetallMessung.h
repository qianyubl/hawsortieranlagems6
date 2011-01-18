/*
 * Z7_MetallMessung.h
 *
 * Created on: 20.12.2010
 *      Author: wehrin_d
 */

#ifndef Z7_METALLMESSUNG_H_
#define Z7_METALLMESSUNG_H_

#include "Zustand.h"
#include "Automat.h"

class Z7_MetallMessung: public Zustand {
public:
	Z7_MetallMessung(Automat* automat);
	virtual ~Z7_MetallMessung();
	void wsMetall(int flanke);
	void WsVerschwunden();
	void tasteEStop(int flanke);
};

#endif /* Z7_METALLMESSUNG_H_ */
