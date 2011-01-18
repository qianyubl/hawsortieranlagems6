#include "MsgRcvThread.h"
#include "HardwareLayer.h"
#include "ComPortReader.h"
#include "WerkstueckListe.h"
#include "Timer.h"


/**
 * MsgRcvThread insert vending machines into list
 * 
 */
MsgRcvThread::MsgRcvThread(){
	int bandNr=HardwareLayer::getInstance()->getBandNr();
	automatenListe.insert(automatenListe.begin(),new Automat(10));
	automatenListe.insert(automatenListe.begin(),new Automat(9));
	if(bandNr==1){
		automatenListe.insert(automatenListe.begin(),new Automat(1));//Ws auf dem Band Checker
		automatenListe.insert(automatenListe.begin(),new Automat(2));//Einlauf
		automatenListe.insert(automatenListe.begin(),new Automat(3));//Auslauf
		automatenListe.insert(automatenListe.begin(),new Automat(5));//Weiche
		automatenListe.insert(automatenListe.begin(),new Automat(6));//Rutsche
		automatenListe.insert(automatenListe.begin(),new Automat(7));//Metall
	}
	if(bandNr==2){
		automatenListe.insert(automatenListe.begin(),new Automat(1));//Ws auf dem Band Checker
		automatenListe.insert(automatenListe.begin(),new Automat(2));//Einlauf
		automatenListe.insert(automatenListe.begin(),new Automat(3));//Auslauf
		automatenListe.insert(automatenListe.begin(),new Automat(4));//Höhenmessung
		automatenListe.insert(automatenListe.begin(),new Automat(5));//Weiche
		automatenListe.insert(automatenListe.begin(),new Automat(6));//Rutsche
		automatenListe.insert(automatenListe.begin(),new Automat(8));//Band2 belegt/frei
	}
}

/**
 * MsgRcvThread is destructor
 * 
 */
MsgRcvThread::~MsgRcvThread()
{
}

/**
 * execute is main routine to get signals through the interrupt with MsgReceivePulse()
 * and decide the next states
 *
 */
void MsgRcvThread::execute(void*){

		//PortB in die unteren 8 bit , Port C in die oberen 4 bit
		//um den anfangswert der anlage zu haben
		msg=in8(PORT_B)|    ( (in8(PORT_C)<<4) & 0xF00 );
		//msg=0xACB;// startwert der anlage
		newMsg=0;
		switched=0;
		flanke=0;


		struct sigevent event;
		HardwareLayer* hal = HardwareLayer::getInstance();

		while(!isStopped()) {

				MsgReceivePulse(chid,&event,sizeof(event),NULL);
				newMsg=event.sigev_value.sival_int;
				//printf("newMsg=0x%x",newMsg);
				switched=msg^newMsg;

				if(   (newMsg& (1<<12)) == (1<<12)){
					// wenn port B sich geändert hat (13.bit gesetzt)
					//printf("Port B \n");
					if(   (switched&EINLAUF_WS) ==EINLAUF_WS){
						flanke=newMsg&EINLAUF_WS;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->wsImEinlauf(flanke);
						}
					}
					if(   (switched&WS_IN_HM)  == WS_IN_HM){
						flanke=newMsg&WS_IN_HM;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->wsInHoehenMessung(flanke);
						}
					}
					if( (switched&HOEHE_BEREICH1) ==HOEHE_BEREICH1){
						flanke=newMsg&HOEHE_BEREICH1;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->hoeheBereich1(flanke);
						}
					}
					if( (switched&WS_IN_WEICHE) ==WS_IN_WEICHE){
						flanke=newMsg&WS_IN_WEICHE;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->wsInWeiche(flanke);
						}

					}
					if( (switched&WS_METALL) ==WS_METALL){
						flanke=newMsg&WS_METALL;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->wsMetall(flanke);
						}
					}
					if( (switched&WEICHE_OFFEN) ==WEICHE_OFFEN){
						flanke=newMsg&WEICHE_OFFEN;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->weicheOffen(flanke);
						}
					}
					if( (switched&RUTSCHE_VOLL) ==RUTSCHE_VOLL){
						flanke=newMsg&RUTSCHE_VOLL;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->rutscheVoll(flanke);
						}
					}
					if( (switched&AUSLAUF_WS)==AUSLAUF_WS){
						flanke=newMsg&AUSLAUF_WS;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->wsImAuslauf(flanke);
						}
					}
				}
				if(   (newMsg& (1<<13)) == (1<<13)){
					//printf("Port c \n");
					// wenn port c sich geändert hat
					if(  ((switched>>4) &TASTE_START)==TASTE_START){
						flanke=newMsg&TASTE_START<<4;
						if(flanke>0){
							// steigende Flanke
							hal->LED_StartAn();
							for(unsigned int i=0;i<automatenListe.size();i++){
								automatenListe.at(i)->tasteStart();
							}
						}
						else{
							hal->LED_StartAus();
						}
					}
					if(  ((switched>>4) &TASTE_STOP)==TASTE_STOP){
						flanke=newMsg&TASTE_STOP<<4;
						if(flanke>0){
							hal->weicheZu();

							printf("------------------------------------------------\n");
					for (unsigned int i = 0; i < automatenListe.size(); i++) {
						automatenListe.at(i)->printState();
					}
					printf("------------------------------------------------\n");

						// steigende Flanke
							for(unsigned int i=0;i<automatenListe.size();i++){
								automatenListe.at(i)->tasteStop();
							}
						}
					}
					if(  ((switched>>4) &TASTE_RESET)==TASTE_RESET){
						if(  ((newMsg>>4) &TASTE_RESET)==TASTE_RESET){
							hal->LED_ResetAn();
							for(unsigned int i=0;i<automatenListe.size();i++){
								automatenListe.at(i)->tasteReset();
							}
						}
						else{
							printf("------------------------------------------------\n");
							for(unsigned int i=0;i<automatenListe.size();i++){
								automatenListe.at(i)->printState();
							}
							WerkstueckListe::getInstance()->printIt();
							printf("%ld\n",Timer::getTimeStamp());
							printf("------------------------------------------------\n");
							hal->LED_ResetAus();
						}
					}
					if(  ((switched>>4) &TASTE_E_STOP)==TASTE_E_STOP){
						flanke=(newMsg>>4)&TASTE_E_STOP;
						for(unsigned int i=0;i<automatenListe.size();i++){
							automatenListe.at(i)->tasteEStop(flanke);
						}
					}

				}
				if(   (newMsg& (1<<14)) == (1<<14)){
					// COM EVENT
					//printf("COM EVENT ---> %x\n",newMsg);
					for(unsigned int i=0;i<automatenListe.size();i++){
						if(newMsg&1==1){
							automatenListe.at(i)->band2Frei();
						}
						else{
							automatenListe.at(i)->band2Belegt();
						}
					}
				}
				if(   (newMsg& (1<<15)) == (1<<15)){
					for(unsigned int i=0;i<automatenListe.size();i++){
						if(newMsg&1==1){
								automatenListe.at(i)->fehler();
						}
						else{
							automatenListe.at(i)->fehlerWeg();
						}
					}
				}
				if(   (newMsg& (1<<16)) == (1<<16)){
					for(unsigned int i=0;i<automatenListe.size();i++){
						automatenListe.at(i)->wsKommtVonBand1();
					}
				}
				if ((newMsg & (1 << 17)) == (1 << 17)) {
					for (unsigned int i = 0; i < automatenListe.size(); i++) {
						automatenListe.at(i)->wsVomBandRunter();
					}
				}
				if ((newMsg & (1 << 18)) == (1 << 18)) {
					for (unsigned int i = 0; i < automatenListe.size(); i++) {
						automatenListe.at(i)->WsVerschwunden();
					}
				}
				if(newMsg<(1<<14))msg=newMsg;
		}
	}

/**
 * shutdown is implemented HAWThread method
 * 
 */
void MsgRcvThread::shutdown() {
	shutdownAll();
}

/**
 * init is neede to assign the channelID
 * 
 */
void MsgRcvThread::init(int channelID){
	chid=channelID;
}
