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
#include "dllist.h"
using namespace std ;
//#include "dllist-driver.cc"

// testnum is set in main.cc
int testnum = 1;//-qq 程序模式,1为原程序，2为自制程序
int N = 5;//-nn 增加链表节点数
int threadnum = 2;//-tt 线程数
int error_type = 0;//-ff bug类型
DLList *dllist;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

extern void GenerateN(DLList *dllist, int N);
extern void RemoveN(DLList *dllist, int N);

void
SimpleThread(int which)
{
    int num;

    for (num = 0; num < 5; num++) {
	    // printf("*** thread %d looped %d times. Now testnum=%d\n", which, num,testnum++);
        // currentThread->Print();
	    printf("\n*** thread %d looped %d times.\n", which, num);
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

    // while(threadnum--){
    //     Thread *t = new Thread("forked thread");
    //     t->Fork(SimpleThread, threadnum);
    // }
    char tname[20];
    for(int i = 1 ; i < threadnum; i++){
        sprintf(tname, "%d", i);
        Thread *t = new Thread(tname);
        t->Fork(SimpleThread, i);
    }
    SimpleThread(0);
}

void
GenerateAndRemove(int which){
    GenerateN(dllist,N);
    // Bug 1
    if(error_type==1)
    {

        printf("---[bug 1]--- Thread: ");
        currentThread->Print();
        printf("    Yield after insert N node. (dllist.cc line76)\n\n");
        fflush(stdout);
        currentThread->Yield();
    }
    RemoveN(dllist,N);
}
void
ThreadTest2()
{
    DEBUG('t', "Entering ThreadTest2");
    printf("thread: main start-up\n");

    dllist=new DLList();
    for(int i = 1; i < threadnum; i++){
        printf("thread: %d start-up\n",i);
	    char fork_name[5]="1   ";
	    fork_name[0]=i+'0';
        Thread *t = new Thread(fork_name);
        t->Fork(GenerateAndRemove,i);
    }
    GenerateAndRemove(0);

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
	ThreadTest1();
	break;
    case 2:
    ThreadTest2();
    break;
    default:
	printf("No test specified.\n");
	break;
    }
}
