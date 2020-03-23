#include "dllist_driver.h"


//产生N个item, 并使用 随机的 优先键。
void ddlist_Genegate(Dllist* randomDLL, int N, int thread_id){
	srand(thread_id);
	//RandomInit(0);
	int* Items = (int *)malloc(N*sizeof(int));
	int* Keys = (int *)malloc(N*sizeof(int));
	
	//产生 元素 和 优先键
	for (int i = 0; i <  N; i++)
	{
		Items[i] = rand() % 200;
		Keys[i] = rand() % 2000;
	}
	/*for (int i = 0; i < N; i++)
	{
		int temp = Keys[i];
		int rand_index = rand() % N;
		//int rand_index = Random() % N; 
		Keys[i] = Keys[rand_index];
		Keys[rand_index] = temp;
	}*/
	
	printf(" ========= Insert info in thread%d ========= \n", thread_id);
	// Buid Dllist
	for(int i =0;i<N;i++){
		randomDLL->SortedInsert(Items+i,Keys[i]);
	}
	randomDLL->ShowAll();
	return ;
}

void ddlist_Print_Remove(Dllist* list, int test_id ,int thread_id, int N){
	//printf("Remove N element...\n");
	int *keyPtr = new int();
	int *item, i = 0;
	while(i<N){
		//printf("xx\n");
		item = (int *)list->Remove(keyPtr, test_id, thread_id, i+1);
		//printf("Remove: (item %d, key %d) \n",*item, *keyPtr);
		i++;
	}
	//printf("\n");
	return ;
}

