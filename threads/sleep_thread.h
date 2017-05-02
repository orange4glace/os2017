#ifndef SLEEP_THREAD_H_
#define SLEEP_THREAD_H_

#include "thread.h"

class SleepThread {

private:
	Thread* thread;
	int sleepTime;

public:
	Thread* GetThread();
	int GetSleepTime();

};

#endif