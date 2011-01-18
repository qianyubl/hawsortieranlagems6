/*
 * Automat.h
 *
 * Created on: 10.12.2010
 *      Author: wehrin_d
 */

#ifndef AUTOMAT_H_
#define AUTOMAT_H_

#include "Zustand.h"

class Zustand;

class Automat{
public:
	Automat(int automatNr);
	void setState(Zustand* state);
	void setStartState();
	virtual void printState();
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
	void setFehlerVonMir(bool f);
	bool getFehlerVonMir();
	int getAutomatNr();
protected:
	bool fehlerVonMir;
	Zustand* theState;
	int automatNr;
};

#endif /* AUTOMAT_H_ */
