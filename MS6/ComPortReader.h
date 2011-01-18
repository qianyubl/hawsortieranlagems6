/*
 * ComPortReader.h
 *
 * Created on: 13.12.2010
 *      Author: wehrin_d
 */

#ifndef COMPORTREADER_H_
#define COMPORTREADER_H_

#include "HAWThread.h"

class ComPortReader :public thread::HAWThread {
public:
	/**
	 * constructor
	 */
	ComPortReader();
	virtual ~ComPortReader();

	/**
	 * startet den Thread
	 */
	virtual void execute(void*);

	virtual void shutdown();
};

#endif /* COMPORTREADER_H_ */
