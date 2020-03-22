// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
// qinlonghu
#include "dllist_driver.h"

// testnum is set in main.cc
int testnum = 1;
int N = 1;

// qinlonghu
Dllist *list_t; 
int *new_items;
int index_it = 0;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 12; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");
    
    t->Fork(SimpleThread, 1);
    SimpleThread(0);
    
}


//----------------------dllist Test 2-----------------------------///
//qinlonghu 
void SimpleThread2(int which)
{
    ddlist_Genegate(list_t, N, which);
    currentThread->Yield();
    
    ddlist_Print_Remove(list_t, N, which);

}
void ThreadTest_Dllist2(int T_Thread){
    
    DEBUG('t', "Entering ThreadTest_Dllist");
    Thread **ts = (Thread **)malloc((T_Thread-1)*sizeof(Thread*));
    for(int i = 0;i< T_Thread-1;i++){
        ts[i] = new Thread("forked thread");
        ts[i]->Fork(SimpleThread2, i+2);
    }
    //t->Fork(SimpleThread2, 2);
    //t->Fork(SimpleThread2, 3);
    SimpleThread2(1);

}

//-----------------dllist Test 3(producer & consumer)---------------///
//qinlonghu 
void SimpleThread3_1(int which) //consumer
{   
    for (int i = 0; i < N; i++) {
        int *keyPtr = new int();
        int *item;
        item = (int *)list_t->Remove(keyPtr);
        printf("*** thread %d: remove %d from dllist\n:", which, *item);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}

void SimpleThread3_2(int which) //producer
{
    
    for (int i = 0; i < N; i++) {
        list_t->Prepend(&new_items[index_it]);
        printf("*** thread %d: Prepend %d to dllist\n:", which, new_items[index_it++]);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}

void ThreadTest_Dllist3(){
    //ddlist_Genegate(list_t,4);
    //ddlist_Print_Remove(list_t);
    new_items = (int *)malloc(3*sizeof(int));
    new_items[0] = 11;new_items[1] = 12;new_items[2] = 13;

    DEBUG('t', "Entering ThreadTest_Dllist");
    
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread3_1, 2);
    SimpleThread3_2(1);
}

//-------------------------Test 4----------------------------------------



//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest(int T_Test,int T_Thread,int T_Num)
{
    list_t = new Dllist();
    N = T_Num;

    switch (testnum) {
    case 1:
    {
        switch(T_Test){
            case 1:
                ThreadTest_Dllist2(T_Thread);     //ture, not finished
                break;
            case 2:
                ThreadTest_Dllist2(T_Thread);     //test
                break;
            case 3:
                ThreadTest_Dllist3(); //fake : T_Thread is 2
                break;
            default:
                printf("T_Test must be 1(right),2(bad1),3(bad2).\n");
                break;
        }
        //ThreadTest1(); //test-merged
        //ThreadTest_Dllist2();//test+3
        //ThreadTest_Dllist3()
        break;
    }
	
    default:
	printf("No test specified.\n");
	break;
    }
}

// tmp modify
