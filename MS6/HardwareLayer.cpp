/**
 * HardwareLayer.cpp
 *
 * Created on: 02.11.2010
 *      Author: aav726
 */

#include "HardwareLayer.h"
#include <iostream.h>
#include <pthread.h>

#include<inttypes.h>
#include<sys/neutrino.h>
#include<hw/inout.h>
#include <stdio.h>

#include "Mutex.h"
#include <unistd.h>
#include <string>
#include "Timer.h"



using namespace std;

RotBlinktThread rt;
Mutex * HardwareLayer::HW_mutex = new Mutex();
HardwareLayer* HardwareLayer::pInstance = 0;


/**
 * HardwareLayer is
 * the interface for the states
 * to access the hardware 
 */
HardwareLayer::HardwareLayer() {
	Timer::setStartTime();
	band2Ready=true;
	this->BAND=1;
	ThreadCtl(_NTO_TCTL_IO,0);
	out8(BASE+3, 0x8a);
	out8(BASE, 0xff);
	out8(BASE, 0x0);
	wvt= new WsVerschwundenThread();
	wvt->start(0);
	portA=0x0;
	rt.start(0);
	rt.hold();
}

/**
 * ampelAnstehendUnquittiert
 * shows a fast flashing red light
 * on the traffic light to advice the user that an error happend
 * 
 */
void HardwareLayer::ampelAnstehendUnquittiert(){
	ampelAus();
	rt.setFrequenz(200);
	rt.cont();
}
/**
 * ampelGegangenUnquittiert is
  * shows a slow flashing red light
 * on the traffic light to advice that an
 * an error is gone without confirmation
 * 
 */
void HardwareLayer::ampelGegangenUnquittiert(){
	ampelAus();
	rt.setFrequenz(2000);
	rt.cont();
}


/**
 * motorAn
 * turns on the engine
 * 
 */
void HardwareLayer::motorAn() {
	portA=portA|MOTOR_RECHTS;
	out8(PORT_A, portA);
}


/**
 * motorAus turns off the engine
 * 
 */
void HardwareLayer::motorAus() {
	portA=portA&(~MOTOR_RECHTS);
	out8(PORT_A, portA);
}

/**
 * motorLangsamAn cause that 
 *  band moves slow
 * 
 */
void HardwareLayer::motorLangsamAn() {
	portA=portA|MOTOR_LANGSAM;
	out8(PORT_A,portA);
}

/**
 * motorLangsamAus turns slow moving off
 * 
 */
void HardwareLayer::motorLangsamAus() {
	portA=portA&(~MOTOR_LANGSAM);
	out8(PORT_A, portA);
}

/**
 * motorStopAn causes that the band can´t move
 * even if the engine is on bit is set
 * 
 */
void HardwareLayer::motorStopAn() {
	portA=portA|MOTOR_STOP;
	out8(PORT_A,portA);
}

/**
 * motorStopAus removes the stop-bit
 * 
 */
void HardwareLayer::motorStopAus() {
	portA=portA&(~MOTOR_STOP);
	out8(PORT_A, portA);
}

/**
 * weicheAuf opens the gate
 * 
 */
void HardwareLayer::weicheAuf() {
	portA=portA|WEICHE_AUF;
	out8(PORT_A,portA);
}

/**
 * weicheZu close the gat
 * 
 */
void HardwareLayer::weicheZu() {
	portA=portA&(~WEICHE_AUF);
	out8(PORT_A, portA);
}

/**
 * ampelGruen sets the green
* light on the traffic light
* and turn all other off
 * 
 */
void HardwareLayer::ampelGruen() {
	rt.hold();
	portA=portA&(~AMPEL_ROT);
	portA=portA&(~AMPEL_GELB);
	portA=portA|AMPEL_GRUEN;
	out8(PORT_A, portA);
}

/**
 * ampelGelb sets the yellow
* light on the traffic light
* and turn all other off
 * 
 */
void HardwareLayer::ampelGelb() {
	rt.hold();
	portA=portA&(~AMPEL_ROT);
	portA=portA&(~AMPEL_GRUEN);
	portA=portA|AMPEL_GELB;
	out8(PORT_A,portA);
}

/**
 * ampelGelb sets the red
* light on the traffic light
* and turn all other off
 * 
 */
void HardwareLayer::ampelRot() {
	rt.hold();
	portA=portA&(~AMPEL_GELB);
	portA=portA&(~AMPEL_GRUEN);
	portA=portA|AMPEL_ROT;
	out8(PORT_A, portA);
}
/**
 * ampelRotAn sets the red
* light on the traffic light
 * 
 */
void HardwareLayer::ampelRotAn() {
	portA=portA|AMPEL_ROT;
	out8(PORT_A, portA);
}
/**
 * ampelRotAn turns off the red
* light on the traffic light
 * 
 */
void HardwareLayer::ampelRotAus() {
	portA=portA&(~AMPEL_ROT);
	out8(PORT_A, portA);
}

/**
 * ampelAus turns off all
 * traffic lights
 * 
 */
void HardwareLayer::ampelAus() {
	rt.hold();
	portA=portA&(~AMPEL_ROT);
	portA=portA&(~AMPEL_GELB);
	portA=portA&(~AMPEL_GRUEN);
	out8(PORT_A, portA);
}

/**
 * ComPortRead read a char from the COM1
 * 
 */
char HardwareLayer::ComPortRead() {
	FILE* fp;
	char c = 0x0;
	fp = fopen("/dev/ser1", "rb");
	if(fp != NULL){
		c = getc(fp);
		fclose(fp);
	}
	return c;
}

/**
 * ComPortWrite writes a char to the com1
 * 
 */
void HardwareLayer::ComPortWrite(const char* value) {
	FILE * fp;
	fp = fopen("/dev/ser1", "w");
	fputs(value, fp);

	fflush(fp);
	fclose(fp);
}

// ..................... Port C .................................
//// Out
/**
 * LED_StartAn turns on the LED on the start button
 * 
 */
void HardwareLayer::LED_StartAn() {
	portC=portC|LED_START;
	out8(PORT_C,portC);
}

/**
 * LED_StartAus turns off the LED on the start button
 * 
 */
void HardwareLayer::LED_StartAus() {
	portC=portC&(~LED_START);
	out8(PORT_C, portC);
}

/**
 * LED_ResetAn turns on the LED on the reset button
 * 
 */
void HardwareLayer::LED_ResetAn() {
	portC=portC|LED_RESET;
	out8(PORT_C,portC);
}

/**
 * LED_ResetAus turns off the LED on the reset button
 * 
 */
void HardwareLayer::LED_ResetAus() {
	portC=portC&(~LED_RESET);
	out8(PORT_C, portC);
}
/**
 * LED_Q1Hell 
 * turns on the Q1 Light
 * 
 */
void HardwareLayer::LED_Q1Hell() {
	portC=portC|LED_Q1;
	out8(PORT_C,portC);
}

/**
 * LED_Q1Dunkel is
 *turns off the Q1 Light
 * 
 */
void HardwareLayer::LED_Q1Dunkel() {
	portC=portC&(~LED_Q1);
	out8(PORT_C, portC);
}
/**
 * LED_Q2Hell is
 * turns on the Q2 Light
 * 
 */
void HardwareLayer::LED_Q2Hell() {
	portC=portC|LED_Q2;
	out8(PORT_C,portC);
}

/**
 * LED_Q2Dunkel is
 * turns off the Q2 Light
 * 
 */
void HardwareLayer::LED_Q2Dunkel() {
	portC=portC&(~LED_Q2);
	out8(PORT_C, portC);
}


/**
 * printInput shows 
 * signals on the input port
 * 
 */
void HardwareLayer::printInput() {
	printf("-------------PortB------------------\n");
	printf("Einlauf WS: %s\n",((in8(PORT_B)&EINLAUF_WS)==EINLAUF_WS)?"true":"false");
	printf("Einlauf Hoehenmessung: %s\n",((in8(PORT_B)&WS_IN_HM)==WS_IN_HM)?"true":"false");
	printf("Hoehe B1: %s\n",((in8(PORT_B)&HOEHE_BEREICH1)==HOEHE_BEREICH1)?"true":"false");
	printf("WS in Weiche: %s\n",((in8(PORT_B)&WS_IN_WEICHE)==WS_IN_WEICHE)?"true":"false");
	printf("WS Metall: %s\n",((in8(PORT_B)&WS_METALL)==WS_METALL)?"true":"false");
	printf("Weiche offen: %s\n",((in8(PORT_B)&WEICHE_OFFEN)==WEICHE_OFFEN)?"true":"false");
	printf("Rutsche voll: %s\n",((in8(PORT_B)&RUTSCHE_VOLL)==RUTSCHE_VOLL)?"true":"false");
	printf("Auslauf WS: %s\n",((in8(PORT_B)&AUSLAUF_WS)==AUSLAUF_WS)?"true":"false");
	printf("-------------PortC------------------\n");
	printf("Taste Start: %s\n",((in8(PORT_C)&TASTE_START)==TASTE_START)?"true":"false");
	printf("Taste Stop: %s\n",((in8(PORT_C)&TASTE_STOP)==TASTE_STOP)?"true":"false");
	printf("Taste Reset: %s\n",((in8(PORT_C)&TASTE_RESET)==TASTE_RESET)?"true":"false");
	printf("Taste E-Stop: %s\n",((in8(PORT_C)&TASTE_E_STOP)==TASTE_E_STOP)?"true":"false");
	printf("-------------------------------------\n\n\n");
}





/**
 * getInstance is
 * a getter for this singelton
 * 
 */
HardwareLayer* HardwareLayer::getInstance() {
	if ( !pInstance ){
			HW_mutex->lock();
			if ( !pInstance )
				pInstance = new HardwareLayer();
			HW_mutex->unlock();
		}

		return pInstance ;
}
/**
* ISR is the Interrupt Service Funktion
 * 
 */

const struct sigevent * ISR (void *arg,int interruptId){

	struct sigevent *event = (struct sigevent *)arg;
	int status = in8(BASE + DIO_CHG_STATE_IRQ_STATUS);
	int portB=0;
	int portC=0;
	int out=0;


	if ( ((status & DIO_GROUP0_PB_STATE_CHANGED) == DIO_GROUP0_PB_STATE_CHANGED)
	|| ((status & DIO_GROUP0_PC_HI_STATE_CHANGED) == DIO_GROUP0_PC_HI_STATE_CHANGED) ) {
		out8(BASE + DIO_CHG_STATE_IRQ_CLR, 0);
		portB=in8(PORT_B);
		portC=in8(PORT_C)&0xf0; // untere 4 bit löschen
		portC=portC<<4;
		out=portB|portC;
		if((status & DIO_GROUP0_PB_STATE_CHANGED) == DIO_GROUP0_PB_STATE_CHANGED) {
			out=out | (1)<<12;
		}
		if((status & DIO_GROUP0_PC_HI_STATE_CHANGED) == DIO_GROUP0_PC_HI_STATE_CHANGED) {
			out=out | (1)<<13;
		}
		event->sigev_value.sival_int=out;
		return (event);
	}
	else{
		out8(BASE + DIO_CHG_STATE_IRQ_CLR, 0);
		return (NULL);
	}

}
/**
 * getWsInToleranz return 
 * the state of HOEHE_BEREICH1
 * 
 */
bool HardwareLayer::getWsInToleranz(){
	if(   (in8(PORT_B)&HOEHE_BEREICH1) == HOEHE_BEREICH1 ){
		return true;
	}
	else{
		return false;
	}
}
/**
 * getRutscheVoll returns
 * the state of RUTSCHE_VOLL input bit
 *
 * 
 */
bool HardwareLayer::getRutscheVoll(){
	if(   (in8(PORT_B)&RUTSCHE_VOLL) == RUTSCHE_VOLL ){
			return true;
	}
	else{
		return false;
	}
}

/**
 * setChannel attaches an interrupt channel
 * for the ISR
 * 
 */
void HardwareLayer::setChannel(int conID){
	static volatile struct sigevent event;
	coid=ConnectAttach(0,0,conID,_NTO_SIDE_CHANNEL,0);
	SIGEV_PULSE_INIT( &event, coid, SIGEV_PULSE_PRIO_INHERIT,0, 0 );
	InterruptAttach(11, ISR, (const void*)&event, sizeof(event),_NTO_INTR_FLAGS_END);//
	//interrupt enable
	out8(BASE+0x0B,~6);
}
/**
 * getChannelID is
 * returns the channel ID if another thread would like
 * to write something on it
 * 
 */
int HardwareLayer::getChannelID(){
	return this->coid;
}
/**
 * getBand2Ready returns if the secound
 * band is ready. this is only immportant
 * for band 1
 * 
 */
bool HardwareLayer::getBand2Ready(){
	return this->band2Ready;
}
/**
 * setBand2Ready set if the band 2 ist ready or not
 * 
 */
void HardwareLayer::setBand2Ready(bool band2Ready){
	this->band2Ready=band2Ready;
}

/**
 * ~HardwareLayer is the destructor of HardwareLayer
 * 
 */
HardwareLayer::~HardwareLayer() {
	// TODO Interrupt De-attach
}
/**
 * readHeight 
 * reads the height of a working piece
 * in the HM
 * 
 */
int HardwareLayer::readHeight(){
	//Ergebnis
	unsigned short ergebnis;
	//low-Byte Ergebnis
	unsigned char low=0;
	//high-byte Ergebnis
	unsigned char high=0;
	//Zustandsregister, prüfen ob Ergebnis fertig
	unsigned char byte=0;
	//Bitmaske zum Prüfen des Bit7 des Zustandsregisters
	unsigned char mask=0x80;
	//starte Messung
	//range 10 von 0-10V (HEX: 0x10)
	out8(ANALOG_CARD_BASE+0x02,0x10);
	//Pollen, warten auf Ergebnis
	do{
		byte=in8(ANALOG_CARD_BASE);
	}while((byte&mask)!=mask);
	//Auslesen
	low=in8(ANALOG_CARD_BASE+0x02);
	high=in8(ANALOG_CARD_BASE+0x03);
	//Low und High Byte zusammenführen
	//12 Bit unsigned Value
	ergebnis=((short)high)<<8|low;
	return ergebnis;
}
/**
 * sendToChannel 
 * writes a value to the ISR channel
 * 
 */
void HardwareLayer::sendToChannel(int val){
	MsgSendPulse (this->coid, SIGEV_PULSE_PRIO_INHERIT, -2,val);
}
/**
 * sendToChannelFehler 
 * writes the code for an error to the channel
 * 
 */
void HardwareLayer::sendToChannelFehler(){
	sendToChannel(  ((1<<15)+1) );
}
/**
 * sendToChannelFehlerWeg writes the code for 
 * the error was been gone  to the channel
 * 
 */
void HardwareLayer::sendToChannelFehlerWeg(){
	sendToChannel(  (1<<15) );
}
/**
 * getBandNr returns the band Number
 * 
 */
int HardwareLayer::getBandNr(){
	return this->BAND;
}
/**
 * sendWsZuBand2 write flag to the COM-POrt
 * which starts the band 2
 * 
 */
void HardwareLayer::sendWsZuBand2(){
	string s="s";
	ComPortWrite(s.c_str());
}

/**
 * sendWsVomBandRunter write an event to the ISR
 * channel which show that the work piece is gone from the band
 * 
 */
void HardwareLayer::sendWsVomBandRunter(){
	sendToChannel(  (1<<17) );
}
/**
 * sendWsVerschwunden writes on the channel
 * code which shows that a work piece is missed
 * 
 */
void HardwareLayer::sendWsVerschwunden(){
	sendToChannel(  (1<<18) );
}
/**
 * WsVerschwundenThreadActiv activates or 
 * deactivates the thread which is looking for work
 * pieces that are missed
 * 
 */
void HardwareLayer::WsVerschwundenThreadActiv(bool f){
	this->wvt->setActiv(f);
}

/**
 * resetGedrueckt returns if the reset button is pressed 
 * down
 * 
 */
bool HardwareLayer::resetGedrueckt(){
	if(  ((in8(PORT_B)) &TASTE_RESET)==TASTE_RESET){
		return true;
	}
	else{
		return false;
	}
}
/**
 * eStopGedrueckt returns if the 
 * estop-button is pressed
 * 
 */
bool HardwareLayer::eStopGedrueckt(){
	if(  ((in8(PORT_C)) &TASTE_E_STOP)==TASTE_E_STOP){
		return false;
	}
	else{
		return true;
	}
}
/**
 * motorRechtsIstAn returns if the engine on bit is set
 * 
 */
bool HardwareLayer::motorRechtsIstAn(){
	if(  ((in8(PORT_A)) &MOTOR_RECHTS)==MOTOR_RECHTS){
		return true;
	}
	else{
		return false;
	}
}


