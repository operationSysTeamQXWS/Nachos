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
//----------------------Test 2-----------------------------///
//qinlonghu 
void SimpleThread2(int which)
{
    int N = 3;
    
    for (int i = 0; i < N; i++) {
        list_t->Append(&new_items[index_it]);
        printf("*** thread %d: insert %d to dllist\n:", which, new_items[index_it++]);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}
void ThreadTest_Dllist2(){
    list_t = ddlist_Genegate(5);
    //ddlist_Print_Remove(list_t);
    new_items = (int *)malloc(6*sizeof(int));
    new_items[0] = 11;new_items[1] = 11;new_items[2] = 12;
    new_items[3] = 12;new_items[4] = 13;new_items[5] = 13;

    DEBUG('t', "Entering ThreadTest_Dllist");
    
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread2, 3);
    SimpleThread2(2);
}

//----------------------Test 3-----------------------------///
//qinlonghu 
void SimpleThread3_1(int which) //Remove
{
    int N = 3;
    
    for (int i = 0; i < N; i++) {
        int *keyPtr = new int();
        int *item;
        item = (int *)list_t->Remove(keyPtr);
        printf("*** thread %d: remove %d to dllist\n:", which, *item);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}

void SimpleThread3_2(int which) //Prepend
{
    int N = 3;
    
    for (int i = 0; i < N; i++) {
        list_t->Prepend(&new_items[index_it]);
        printf("*** thread %d: Prepend %d to dllist\n:", which, new_items[index_it++]);
        list_t->ShowAll();
        //currentThread->Yield();
    }

}

void ThreadTest_Dllist3(){
    list_t = ddlist_Genegate(4);
    //ddlist_Print_Remove(list_t);
    new_items = (int *)malloc(3*sizeof(int));
    new_items[0] = 11;new_items[1] = 12;new_items[2] = 13;

    DEBUG('t', "Entering ThreadTest_Dllist");
    
    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread3_2, 2);
    SimpleThread3_1(1);
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	//ThreadTest1();
	//ThreadTest_Dllist2();
    ThreadTest_Dllist3();
    break;
    default:
	printf("No test specified.\n");
	break;
    }
}

