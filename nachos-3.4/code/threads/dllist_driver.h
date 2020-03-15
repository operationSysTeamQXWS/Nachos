#include "dllist.h"
extern "C" 
{
	#include <sys/time.h>
	#include <cstdio>
	void srand(unsigned seed);
	int rand(void);
	void *malloc(unsigned int num_bytes);
}

//#include <sys/time.h>

Dllist* ddlist_Genegate(int N);
void ddlist_Print_Remove(Dllist* list);
