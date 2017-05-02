#ifndef SLEEP_THREAD_H_
#define SLEEP_THREAD_H_

#include "thread.h"

class SleepThread {

private:
	Thread* thread;
	int sleepTime;

public:
	SleepThread(Thread* t, int time);

	Thread* GetThread();
	int GetSleepTime();
	void Consume(int time);
};

#endif