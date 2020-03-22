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

void ddlist_Genegate(Dllist* randomDLL, int N, int thread_id);
void ddlist_Print_Remove(Dllist* list, int N, int thread_id);
