#include "sleep_thread.h"

SleepThread::SleepThread(Thread* t, int time) {
	thread = t;
	sleepTime = time;;
}

Thread* SleepThread::GetThread() {
	return thread;
}

int SleepThread::GetSleepTime() {
	return sleepTime;
}

void SleepThread::Consume(int time) {
	sleepTime -= time;
}