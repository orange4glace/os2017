#include "dll_element.h"
#include <cstddef>

DLLElement::DLLElement(void* itemPtr, int sortKey) : 
	item(itemPtr),
	key(sortKey),
	next(NULL),
	prev(NULL) {
}