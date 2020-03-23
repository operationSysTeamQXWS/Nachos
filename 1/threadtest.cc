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
int Test_id;
int T_Thread;
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


//----------------------dllist remove Test Interupt-----------------------------///
//qinlonghu 
void SimpleThread123(int which)
{
    ddlist_Genegate(list_t, N, which);
    currentThread->Yield();
    
    ddlist_Print_Remove(list_t,Test_id,which,N);//int test_id ,int thread_id, int N

}
void ThreadTest_Dllist123(){
    
    DEBUG('t', "Entering ThreadTest_Dllist");
    Thread **ts = (Thread **)malloc((T_Thread-1)*sizeof(Thread*));
    for(int i = 0;i< T_Thread-1;i++){
        ts[i] = new Thread("forked thread");
        ts[i]->Fork(SimpleThread123, i+2);
    }
    SimpleThread123(1);

}

//-----------------dllist Test(producer & consumer)---------------///
//qinlonghu 
void SimpleThread4_1(int which) //consumer
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

void SimpleThread4_2(int which) //producer
{
    
    for (int i = 0; i < N; i++) {
        list_t->Prepend(&new_items[index_it]);
        printf("*** thread %d: Prepend %d to dllist\n:", which, new_items[index_it++]);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}

void ThreadTest_Dllist4(){
    //ddlist_Genegate(list_t,4);
    //ddlist_Print_Remove(list_t);
    new_items = (int *)malloc(3*sizeof(int));
    new_items[0] = 11;new_items[1] = 12;new_items[2] = 13;

    DEBUG('t', "Entering ThreadTest_Dllist");
    
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread4_1, 2);
    SimpleThread4_2(1);
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest(int T_test,int T_thread,int T_num)
{
    list_t = new Dllist();
    Test_id = T_test;
    T_Thread = T_thread;
    N = T_num;

    switch (testnum) {
    case 1:
    {
        switch(Test_id){
            case 1:
            case 2:
            case 3:
                ThreadTest_Dllist123(); //1:right,2:free error,3:null error
                break;
            default:
                printf("T_Test must be 1(right),2(free error),3(null error).\n");
                break;
        }
        //ThreadTest1(); //test-merged
        break;
    }
	
    default:
	printf("No test specified.\n");
	break;
    }
}

// tmp modify
