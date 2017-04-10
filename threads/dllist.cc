#include "dllist.h"

#include <iostream>
using namespace std;

const int DLList::MIN_KEY = -2147483646;
const int DLList::MAX_KEY = 2147483646;
const int DLList::ERR_KEY = -2147483647;

DLList::DLList() : 
	size_(0) {
	first_ = new DLLElement(NULL, DLList::MIN_KEY - 1);
	last_ = new DLLElement(NULL, DLList::MAX_KEY + 1);
	first_->next = last_;
	last_->prev = first_;
}

DLList::~DLList() {

}

void DLList::Prepend(void* item) {
	SortedInsert(item, DLList::MIN_KEY);
}

void DLList::Append(void* item) {
	SortedInsert(item, DLList::MAX_KEY);
}

void* DLList::Remove(int *keyPtr) {
	*keyPtr = DLList::ERR_KEY;
	if (size_ == 0) return NULL;
	DLLElement* ret = first_->next;
	*keyPtr = ret->key;
	return SortedRemove(ret->key);
}

const bool DLList::IsEmpty() const {
	return size_ == 0;
}

const int DLList::size() const {
	return size_;
}

int DLList::SortedInsert(void* item, int sort_key) {
	if (sort_key > DLList::MAX_KEY || sort_key < DLList::MIN_KEY) return -1;
	DLLElement* el = new DLLElement(item, sort_key);
	DLLElement* cur = first_;
	while (cur != NULL) {
		if (cur->key >= sort_key) {
			DLLElement* ne = cur->prev;
			el->prev = ne;
			el->next = cur;
			cur->prev = el;
			ne->next = el;
			break;
		}
		cur = cur->next;
	}
	size_++;
	return 0;
}

void* DLList::SortedRemove(int sort_key) {
	if (sort_key > DLList::MAX_KEY || sort_key < DLList::MIN_KEY || size_ == 0) return NULL;
	DLLElement* cur = first_;
	while (cur != NULL) {
		if (cur->key == sort_key) {
			DLLElement* prev = cur->prev;
			DLLElement* next = cur->next;
			prev->next = next;
			next->prev = prev;
			size_ --;
			return cur->item;
		}
		cur = cur->next;
	}
	return NULL;
}