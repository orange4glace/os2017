#include <iostream>
#include "dllist.h"

using namespace std;

int main() {

	DLList dllist;

	int a = 5;
	dllist.SortedInsert(&a, 1);
	cout << "GO " << endl;

	int* got = (int*)dllist.SortedRemove(1);

	if (got != NULL) cout << *got << endl;

}