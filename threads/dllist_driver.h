#ifndef DLLIST_DRIVER_H
#define DLLIST_DRIVER_H

#include "dllist.h"
#include "debug.h"

extern DLList dllist;

extern int tcnt;
extern int ncnt;

extern void InsertDLLItem(DLList* list, int value, int key);
extern int s(DLList* list);
extern void DLListSelfTest();

#endif