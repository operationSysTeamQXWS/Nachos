#include "dllist_driver.h"


//产生N个item, 并使用 随机的 优先键 。
Dllist* ddlist_Genegate(int N){
	Dllist* randomDLL = new Dllist();
	srand(0);
	//RandomInit(0)
	int* Items = (int *)malloc(N*sizeof(int));
	int* Keys = (int *)malloc(N*sizeof(int));
	
	//产生 元素 和 优先键
	for (int i = 0; i <  N; i++)
	{
		Items[i] = i;
		Keys[i] = i;
	}
	for (int i = 0; i < N; i++)
	{
		int temp = Keys[i];
		int rand_index = rand() % N;
		//int rand_index = Random() % N; 
		Keys[i] = Keys[rand_index];
		Keys[rand_index] = temp;
	}
	
	printf("Inialization(item, key)...");
	// Buid Dllist
	for(int i =0;i<N;i++){
		randomDLL->SortedInsert(Items+i,Keys[i]);
	}
	printf("\n");
	randomDLL->ShowAll();
	return randomDLL;
}

void ddlist_Print_Remove(Dllist* list){
	printf("Remove all:\n");
	int *keyPtr = new int();
	int *item ;
	while(list->isEmpty() == false){
		//printf("xx\n");
		item = (int *)list->Remove(keyPtr);
		printf("(%d,%d) ",*item, *keyPtr);
	}
	printf("\n");
	return ;
}

