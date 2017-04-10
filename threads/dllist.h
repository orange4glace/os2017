#ifndef DLLIST_H
#define DLLIST_H

#include "dll_element.h"

class DLList {

	public :

		DLList();
		~DLList();

		void Prepend(void* item);
		void Append(void* item);
		void* Remove(int *keyPtr);

		const bool IsEmpty() const;
		const int size() const;

		int SortedInsert(void* item, int sort_key);
		void* SortedRemove(int sort_key);

	private :

		static const int MIN_KEY;
		static const int MAX_KEY;
		static const int ERR_KEY;

		int size_;
		DLLElement* first_;
		DLLElement* last_;

};

#endif