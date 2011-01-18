/**
 * HardwareLayer.h
 *
 * Created on: 02.11.2010
 *      Author: aav726
 */

#ifndef HARDWARELAYER_H_
#define HARDWARELAYER_H_
#include <pthread.h>

#include<inttypes.h>
#include<sys/neutrino.h>
#include<hw/inout.h>
#include "time.h"

#include "RotBlinktThread.h"
#include "Mutex.h"
#include "WsVerschwundenThread.h"


#define DIO_GROUP0_PA_STATE_CHANGED     0x01
#define DIO_GROUP0_PB_STATE_CHANGED     0x02
#define DIO_GROUP0_PC_LO_STATE_CHANGED  0x04
#define DIO_GROUP0_PC_HI_STATE_CHANGED  0x08

/* Change of state register for both port groups	*/
#define DIO_CHG_STATE_IRQ_ENABLE        0x0B
#define DIO_CHG_STATE_IRQ_STATUS        0x0F
#define DIO_CHG_STATE_IRQ_CLR	        0x0F



/* Register of IO-Port Group 0  DIO48 			    */
#define DIO_GROUP0_PA          		 0x00
#define DIO_GROUP0_PB				 0x01
#define DIO_GROUP0_PC				 0x02
#define DIO_GROUP0_CONTROL			 0x03


// --- Ports ---
#define BASE				(0x300)
#define PORT_A				(BASE + 0x00)
#define PORT_B				(BASE + 0x01)
#define PORT_C				(BASE + 0x02)
#define ANALOG_CARD_BASE	(0x320)

// --- Bits ---
// --- Port A ---
#define MOTOR_RECHTS 	0x01
#define MOTOR_LINKS		0x02
#define MOTOR_LANGSAM	0x04
#define MOTOR_STOP		0x08
#define WEICHE_AUF		0x10
#define AMPEL_GRUEN		0x20
#define AMPEL_GELB		0x40
#define AMPEL_ROT		0x80
// --- Port B ---
#define EINLAUF_WS		0x01
#define WS_IN_HM		0x02
#define HOEHE_BEREICH1	0x04
#define WS_IN_WEICHE	0x08
#define WS_METALL		0x10
#define WEICHE_OFFEN	0x20
#define RUTSCHE_VOLL	0x40
#define AUSLAUF_WS		0x80

// --- Port C ---
// --- Out ---
#define LED_START		0x01
#define LED_RESET		0x02
#define LED_Q1			0x04
#define LED_Q2			0x08
// --- In ---
#define TASTE_START		0x10
#define TASTE_STOP		0x20
#define TASTE_RESET		0x40
#define TASTE_E_STOP	0x80

// Abstände der Werkstücke in ms
#define ABSTAND_B1_EINLAUF_WEICHE_MIN 3300
#define ABSTAND_B1_EINLAUF_WEICHE_MAX 3700
#define ABSTAND_B1_WEICHE_AUSLAUF 2260


class HardwareLayer {

public:
	/**
	 * this function set the border on
	 *
	 * @no Arg
	 */
	void weicheAuf(); // set the border on

	/**
	 * this function set the border off
	 *
	 * @no Arg
	 */
	void weicheZu(); // set the border off

	/**
	 * this function stops the motor, when motor running rightside bit is on
	 *
	 * @no Arg
	 */
	void motorAn(); // starts motor to right side

	/**
	 * this function starts the motor slowly
	 *
	 * @no Arg
	 */
	void motorAus(); // starts motor to left side

	/**
	 * this function stops the motor, when motor slowly bit is on
	 *
	 * @no Arg
	 */
	void motorLangsamAn(); // starts motor slowly

	/**
	 * this function stops the motor
	 *
	 * @no Arg
	 */
	void motorLangsamAus(); // stops motor slowly

	/**
	 * this function stops the motor
	 *
	 * @no Arg
	 */
	void motorStopAn(); // stops the motor

	/**
	 * this function starts the motor
	 *
	 * @no Arg
	 */
	void motorStopAus(); // set the stop motor bit to 0??

	/**
	 * this function set the light green on
	 *
	 * @no Arg
	 */
	void ampelGruen(); // light green on

	/**
	 * this function set the light green off
	 *
	 * @no Arg
	 */
	void ampelGelb(); // light yellow on

	/**
	 * this function set the light yellow off
	 *
	 * @no Arg
	 */
	void ampelRot(); // light red on

	/**
	 * this function set the light red off
	 *
	 * @no Arg
	 */
	void ampelAus(); // light red off

	/**
	 * this function reads the comport and store it into Parameter one
	 *
	 * @char* c: is arg to store the result of the function with a
	 *           pointer in a var out of a function
	 */
    char ComPortRead();

	/**
	 * this function write an value to the comport
	 *
	 * @char* value: is arg to pass a value in the function with a
	 *               pointer to write it in the function to comport
	 */

	void ampelAnstehendUnquittiert();
	void ampelGegangenUnquittiert();
	void ampelRotOhneHold();
	void ampelRotAn();
	void ampelRotAus();

	void ComPortWrite(const char* value); // write on serial port

	void printInput(); // Ausgabe von Port B und C(High) auf der Konsole
	int readHeight(); // Wert der Hoehenmessung lesen

	// Port C
	void LED_StartAn();
	void LED_StartAus();
	void LED_ResetAn();
	void LED_ResetAus();
	void LED_Q1Hell();
	void LED_Q1Dunkel();
	void LED_Q2Hell();
	void LED_Q2Dunkel();

	// GET & SET

	bool getBand2Ready();
	void setBand2Ready(bool band2Ready);
	bool getRutscheVoll();
	bool getWsInToleranz();
	int getChannelID();
	void setChannel(int coid);
	int getBandNr();


	// PulseMessages um die anderen Automaten zu benachrichten

	void sendToChannel(int val);
	void sendToChannelFehler();
	void sendToChannelFehlerWeg();
	void sendWsZuBand2();
	void sendWsVomBandRunter();
	void sendWsVerschwunden();
	void WsVerschwundenThreadActiv(bool f);
	bool resetGedrueckt();
	bool eStopGedrueckt();
	bool motorRechtsIstAn();

	// Singelton Getter

	static HardwareLayer* getInstance();

private:
	WsVerschwundenThread* wvt;
	bool band2Ready;
	HardwareLayer(); 						// singleton constructor
	HardwareLayer(const HardwareLayer&);	//singleton copy constructor
	~HardwareLayer();						//Destructor
	static Mutex * HW_mutex;				// Singelton Mutex
	static HardwareLayer* pInstance;		// the one and only instance

	int coid;								// Channel ID
	uint8_t portA;							// port A value
	uint8_t portC;							// port C value
	int BAND;								// Band Nr wird im Konstructor gesetzt (1 oder 2)

};

#endif /* HARDWARELAYER_H_ */
