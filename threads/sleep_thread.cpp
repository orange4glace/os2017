#include "sleep_thread.h"

Thread* SleepThread::GetThread() {
	return thread;
}

int SleepThread::GetSleepTime() {
	return sleepTime;
}