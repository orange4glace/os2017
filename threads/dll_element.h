#ifndef DLL_ELEMENT_H
#define DLL_ELEMENT_H

class DLLElement {

	public :

		DLLElement(void* itemPtr, int sortKey);

		DLLElement* next;
		DLLElement* prev;

		int key;
		void* item;

};

#endif