//#ifndef DOUBLELIST_H_INCLUDED
//#define DOUBLELIST_H_INCLUDED
//#endif // DOUBLELIST_H_INCLUDED

//#include "copyright.h"
class DoubleListElement;
class DoubleList {
  public:
    DoubleList();			// initialize the list
    ~DoubleList();			// de-allocate the list

    void Prepend(int value); 	// Put item at the beginning of the list
    int Remove(); 	 	// Take item off the front of the list

    bool Empty();		// is the list empty?

    void SelfTest();

  private:
    DoubleListElement *first;  	// Head of the list, NULL if list is empty
    DoubleListElement *last;		// Last element of list
};

//#endif // LIST_H

