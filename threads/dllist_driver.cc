#include "dllist_driver.h"
#include "dllist.h"
#include "synch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

DLList dllist = DLList();

void InsertDLLItem(DLList* list, void* item, int key) {
	list->SortedInsert(item, key);
}

int InsertDLLItem(DLList* list) {
	int key = 0;
	void* item = list->Remove(&key);
	return key;
}

static void DLListTest(int which) {
	srand(time(NULL));

    int num = 5;
    
    for (num = 0; num < ncnt; num++) {
    	int key = rand() % 50;
    	int c = 5;
    	InsertDLLItem(&dllist, &c, key);
    	cout << which << " inserts " << key << endl;
    	kernel->currentThread->Yield();
    }
    
    for (num = 0; num < ncnt; num++) {
    	int key = InsertDLLItem(&dllist);
    	cout << which << " pops " << key << endl;
    	kernel->currentThread->Yield();
    }
}

void DLListSelfTest() {
	for (int i = 0; i < tcnt; i ++) {
	    Thread *t = new Thread("dll thread");
	    t->Fork((VoidFunctionPtr) DLListTest, (void *) i + 1);
	}
    DLListTest(0);
}