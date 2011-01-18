#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
//#include <cpt_terminal.h>

#include "HardwareLayer.h"
#include "MsgRcvThread.h"
#include "TestClassSensorik.h"
#include "ComPortReader.h"


// main routine to start the machine with threads
int main(int argc, char *argv[]) {
	// set channel
	int chid=ChannelCreate(42);
	MsgRcvThread mt;
	HardwareLayer::getInstance()->setChannel(chid);
	ComPortReader cpr;
	cpr.start(0);
	mt.init(chid);

	mt.start(0);
	mt.join();

	return EXIT_SUCCESS;
}
