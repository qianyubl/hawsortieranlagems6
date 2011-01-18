#ifndef TESTCLASSSENSORIK_H_
#define TESTCLASSSENSORIK_H_

#include "HAWThread.h"

class TestClassSensorik : public thread::HAWThread
{
public:
	TestClassSensorik();
	virtual ~TestClassSensorik();
	virtual void execute(void*);

	/**
	 * shuts the thread down
	 *
	 * @no Arg
	 */
	virtual void shutdown();
	void init(int channelID);
	int chid;
	int msg;
};

#endif /*TESTCLASSSENSORIK_H_*/
