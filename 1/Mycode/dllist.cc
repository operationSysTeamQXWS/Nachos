extern "C" {
#include <assert.h>

#define ASSERT(expression)  assert(expression)
}

//#include "copyright.h"
#include "dllist.h"

const int NULL = 0;

class DoubleListElement {
   public:
     DoubleListElement(int value) { item = value; before = NULL; next=NULL;};
     					// constructor for list element
     DoubleListElement *before;
     DoubleListElement *next;		// next element on list,
				// NULL if this is the last
     int item; 	    	        // value of this element
};

DoubleList::DoubleList() {

    first = last = NULL;
}


DoubleList::~DoubleList() {

    while (!Empty())
	(void) Remove();	 // delete all the list elements
}


void DoubleList::Prepend(int value) {
    DoubleListElement *element = new DoubleListElement(value);

    if (Empty()) {		// list is empty
        first = element;
        last = element;
    } else {			// else put it before first
        last->next = element;
        element->before = last;

        last = element;
    }
}

int DoubleList::Remove() {
    DoubleListElement *element = last;
    int value;
    ASSERT(!Empty());

    value = element->item;

    if (first == last) {	// list had one item, now has none
        first = NULL;
        last = NULL;
    } else {
        last = element->before;
	last->next = NULL;
    }

    delete element;		// deallocate list element -- no longer needed
    return value;
}

bool DoubleList::Empty() {
    return (first == NULL);
}
