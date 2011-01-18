/*
 * Werkstueck.h
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#ifndef WERKSTUECK_H_
#define WERKSTUECK_H_


#define STATION_EINLAUF 1
#define STATION_HOEHENMESSUNG 2
#define STATION_WEICHE 3
#define STATION_AUSLAUF 4
#define STATION_RUTSCHE 5

#define WS_OK 1
#define WS_NOK 2

class Werkstueck {
public:
	Werkstueck();
	virtual ~Werkstueck();
	void setLetzteStation(int letzteStation);
	int getLetzteStation();
	void setTimestamp(long timestamp);
	long getTimestamp();
	int ok;
	void printIt();
private:
	int letzteStation;
	long timestamp;
};

#endif /* WERKSTUECK_H_ */
