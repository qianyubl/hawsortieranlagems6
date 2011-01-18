/*
 * WerkstueckListe.h
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#ifndef WERKSTUECKLISTE_H_
#define WERKSTUECKLISTE_H_
#include "Mutex.h"
#include <vector>
#include "Werkstueck.h"


class WerkstueckListe {
public:
	static WerkstueckListe* getInstance();
	bool isEmpty();
	Werkstueck* getWsAt(int position);
	void add(Werkstueck* ws);
	void eraseWsAt(int position);
	int size();
	int getLastWsWithStation(int station);
	int getLifoWsWithStation(int station);
	void printIt();
	void clear();
	void saveTimestampAtStop();
	void refreshTimestamps();


private:
	WerkstueckListe();
	virtual ~WerkstueckListe();
	static WerkstueckListe* pInstance;
	static Mutex* wslMutex;
	std::vector<Werkstueck*> liste;
	long timestampAtStop;


};

#endif /* WERKSTUECKLISTE_H_ */
