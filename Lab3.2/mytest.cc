// mytest.cc
// Test the priority scheduler for the threads assginment
#include "system.h"
#include "BoundedBuffer.h"

#define BOUNDEDBUFFERSIZE 10

extern BoundedBuffer* boundedbuffer;
extern int p_size;
extern int c_size;

void Buffer_producer(int size) {
    for (int i = 0; i < 10; ++i)
    {
        //int size = Random() % 20 + 1;
        ////int key=i;
        char *items = new char[size + 1];
        for (int i = 0; i < size; ++i)
        {
        	items[i] = 65 + i;
        }

        items[size] = '\0';
        boundedbuffer->Write(items, size);
        printf("%s in:%s\n size:%d usedsize:%d\n", currentThread->getName(), items, size, boundedbuffer->UsedSize);
        currentThread->Yield();

        //currentThread->Yield();
    }
}
void Buffer_consumer(int size) {
    for (int i = 0; i < 10; ++i)
    {
        //int size = 10;
        char* item = new char[size + 1];
        boundedbuffer->Read(item, size);
        item[size] = '\0';
        printf("%s out:%s\n size:%d usedsize:%d\n", currentThread->getName(), (char*)item, size, boundedbuffer->UsedSize);
        currentThread->Yield();
    }
}
void test1() {
    DEBUG('t', "Entering ThreadTest0 ");
    boundedbuffer = new BoundedBuffer(BOUNDEDBUFFERSIZE);
    for (int var = 0; var < 5; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "consumer thread ");
        strcat(name, No);

        Thread* t = new Thread(name, 5 - var);
        t->Fork(Buffer_consumer, c_size);
    }
    for (int var = 0; var < 2; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "producer thread ");
        strcat(name, No);
        if (var == 0)
        {
            Thread* t = new Thread(name, 0);
            t->Fork(Buffer_producer, p_size);
        }
        else if (var == 1)
        {
            Thread* t = new Thread(name, 0);
            t->Fork(Buffer_producer, p_size);
        }

    }
}
void test2() {
    DEBUG('t', "Entering ThreadTest0 ");
    boundedbuffer = new BoundedBuffer(BOUNDEDBUFFERSIZE);
    for (int var = 0; var < 2; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "producer thread ");
        strcat(name, No);
        if (var == 0)
        {
            Thread* t = new Thread(name, 1);
            t->Fork(Buffer_producer, p_size);
        }
        else if (var == 1)
        {
            Thread* t = new Thread(name, 0);
            t->Fork(Buffer_producer, p_size);
        }
    }
    for (int var = 0; var < 1; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "consumer thread ");
        strcat(name, No);

        Thread* t = new Thread(name, 1);
        t->Fork(Buffer_consumer, c_size);
    }
}
void test3() {
    DEBUG('t', "Entering ThreadTest0 ");
    boundedbuffer = new BoundedBuffer(BOUNDEDBUFFERSIZE);
    for (int var = 0; var < 2; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "producer thread ");
        strcat(name, No);
        if (var == 0)
        {
            Thread* t = new Thread(name, 1);
            t->Fork(Buffer_producer, p_size);
        }
        else if (var == 1)
        {
            Thread* t = new Thread(name, 1);
            t->Fork(Buffer_producer, p_size);
        }
    }
    for (int var = 0; var < 1; var++)
    {
        char No[4] = "1";
        sprintf(No, "%d", var);
        //char name[18]="forked thread ";	//error
        char* name = new char[25];			//必须分配新空间，否则新进程会覆盖掉原有name地址
        name[0] = '\0';
        strcat(name, "consumer thread ");
        strcat(name, No);

        Thread* t = new Thread(name, 0);
        t->Fork(Buffer_consumer, c_size);
    }
}
void ThreadTest0(int c=1){
    switch(c)
    {
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        default:
            printf("No test specified.\n");
            break;
    }
}
