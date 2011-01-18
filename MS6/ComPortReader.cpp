/*
 * ComPortReader.cpp
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#include "ComPortReader.h"
#include "HardwareLayer.h"
#include <sys/neutrino.h>
#include "HAWThread.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

/**
 * ComPortReader is constructor
 * 
 */
ComPortReader::ComPortReader() {}

/**
 * ~ComPortReader is destructor
 * 
 */
ComPortReader::~ComPortReader() {
	// TODO Auto-generated destructor stub
}
/**
 * execute is main routine for comport reading
 * there is a decision between 'r' 'n' and 's'
 *
 */
void ComPortReader::execute(void*){
	HardwareLayer* hal = HardwareLayer::getInstance();
	int coid = hal->getChannelID();
	while (1) {
		int val = 1 << 14;
		char c = NULL;
		while (c == 0x0) {
			c = hal->ComPortRead();
		}
		//printf("COM EVENT 0x%x an COM1\n", c);
		if (c == 'r') {
			val = val | 1;
			hal->setBand2Ready(true);
			MsgSendPulse (coid, SIGEV_PULSE_PRIO_INHERIT, -2,val);
		} else if (c == 'n') {
			MsgSendPulse (coid, SIGEV_PULSE_PRIO_INHERIT, -2,val);
			hal->setBand2Ready(false);
		} else if (c == 's') {
			MsgSendPulse (coid, SIGEV_PULSE_PRIO_INHERIT, -2,(1<<16));
		} else {
			printf("Fehler nicht erwarteter Wert 0x%x an COM1\n", c);
			fflush(stdout);
		}

	}
}

/**
 * shutdown have to be implemented because it's virtual
 * 
 */
void ComPortReader::shutdown(){}
