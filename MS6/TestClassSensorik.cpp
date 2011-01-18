#include "TestClassSensorik.h"
#include "HardwareLayer.h"
#include "MsgRcvThread.h"

TestClassSensorik::TestClassSensorik()
{

}

TestClassSensorik::~TestClassSensorik()
{
}

/**
 * init is
 * 
 */
void TestClassSensorik::init(int channelID){
	chid=channelID;
}

/**
 * execute is
 * 
 */
void TestClassSensorik::execute(void*){
	struct sigevent event;
	HardwareLayer* hal = HardwareLayer::getInstance();
	//PortB in die unteren 8 bit , Port C in die oberen 4 bit
	msg=in8(PORT_B)|    ( (in8(PORT_C)<<4) & 0xF00 );
	//msg=0xACB;// startwert der anlage
	int newMsg=0;
	int switched=0;

	while(!isStopped()) {
			MsgReceivePulse(chid,&event,sizeof(event),NULL);
			newMsg=event.sigev_value.sival_int;
			switched=msg^newMsg;

			printf("Switched = %x",switched>>4);

			if(   (newMsg& (1<<12)) == (1<<12)){
				// wenn port B sich geändert hat
				printf("Port B \n");
				if(   (switched&EINLAUF_WS) ==EINLAUF_WS){
					hal->ampelRot();
				}
				if(   (switched&WS_IN_HM)  == WS_IN_HM){
					hal->ampelGelb();
				}
				if( (switched&HOEHE_BEREICH1) ==HOEHE_BEREICH1){
					hal->ampelGruen();
				}
				if( (switched&WS_IN_WEICHE) ==WS_IN_WEICHE){
					hal->ampelRot();
				}
				if( (switched&WS_METALL) ==WS_METALL){
					hal->ampelGelb();
				}
				if( (switched&WEICHE_OFFEN) ==WEICHE_OFFEN){
					hal->ampelGruen();
				}
				if( (switched&RUTSCHE_VOLL) ==RUTSCHE_VOLL){
					hal->ampelRot();
				}
				if( (switched&AUSLAUF_WS)==AUSLAUF_WS){
					hal->ampelGelb();
				}
			}
			if(   (newMsg& (1<<13)) == (1<<13)){
				printf("Port c \n");
				// wenn port c sich geändert hat
				if(  ((switched>>4) &TASTE_START)==TASTE_START){
//					hal->AmpelGruenAn();
//					hal->AmpelGelbAus();
//					hal->AmpelRotAus();
					printf("Taste start\n");
					hal->ampelAnstehendUnquittiert();
					hal->LED_ResetAus();
					hal->LED_StartAn();
					hal->LED_Q1Dunkel();
					hal->LED_Q2Hell();
				}



				if(  ((switched>>4) &TASTE_STOP)==TASTE_STOP){
					printf("Taste stop\n");
					hal->ampelAus();
					hal->LED_ResetAus();
					hal->LED_StartAus();
					hal->LED_Q1Dunkel();
					hal->LED_Q2Dunkel();
				}
				if(  ((switched>>4) &TASTE_RESET)==TASTE_RESET){
					hal->ampelAus();
					printf("Taste reset\n");
					hal->LED_ResetAn();
					hal->LED_StartAus();

					hal->LED_Q1Hell();
					hal->LED_Q2Dunkel();

				}
				if(  ((switched>>4) &TASTE_E_STOP)==TASTE_E_STOP){
					hal->ampelRot();
				}

			}
			msg=newMsg;
	}
}
/**
 * shutdown is
 * 
 */
void TestClassSensorik::shutdown(){}
