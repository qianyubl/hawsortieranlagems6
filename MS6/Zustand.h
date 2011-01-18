/*
 * Zustand1.h
 *
 * Created on: 14.12.2010
 *      Author: wehrin_d
 */

#ifndef ZUSTAND1_H_
#define ZUSTAND1_H_

#include "Automat.h"
#include <iostream>
#include <string>
using namespace std;
class Automat;


class Zustand {
public:
	Zustand();
	virtual ~Zustand();
	virtual void returnFromErrorState();
	string name;
	// Ereignisse
	virtual void wsImEinlauf(int flanke);
	virtual void wsInHoehenMessung(int flanke);
	virtual void hoeheBereich1(int flanke);
	virtual void wsInWeiche(int flanke);
	virtual void wsMetall(int flanke);
	virtual void weicheOffen(int flanke);
	virtual void rutscheVoll(int flanke);
	virtual void wsImAuslauf(int flanke);
	virtual void tasteStart();
	virtual void tasteStop();
	virtual void tasteReset();
	virtual void tasteEStop(int flanke);
	virtual void band2Frei();
	virtual void band2Belegt();
	virtual void fehler();
	virtual void fehlerWeg();
	virtual void timerAbgelaufen();
	virtual void wsKommtVonBand1();
	virtual void wsVomBandRunter ();
	virtual void WsVerschwunden();


protected:
	Automat* owner;
};

#endif /* ZUSTAND1_H_ */
