//基本优先级调度测试
void TestPrioritySchedulerBasic() {
    DEBUG('t', "Entering TestPrioritySchedulerBasic");

    // 创建具有不同优先级的线程
    Thread *t1 = new Thread("thread 1", 10);
    Thread *t2 = new Thread("thread 2", 20);
    Thread *t3 = new Thread("thread 3", 15);

    t1->Fork(SimpleThread, 1);
    t2->Fork(SimpleThread, 2);
    t3->Fork(SimpleThread, 3);

    // 验证高优先级的线程是否优先被调度
    SimpleThread(0);
}
//大量线程测试
void TestLargeNumberOfThreads() {
    DEBUG('t', "Entering TestLargeNumberOfThreads");

    const int NUM_THREADS = 100;
    Thread *threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        int priority = Random() % 100;
        threads[i] = new Thread(std::string("thread ") + std::to_string(i), priority);
        threads[i]->Fork(SimpleThread, i);
    }

    // 验证调度器在高负载情况下的性能和稳定性
    SimpleThread(0);
}
//边界条件测试
void TestEdgeConditions() {
    DEBUG('t', "Entering TestBoundaryConditions");

    // 所有线程优先级相同
    Thread *t1 = new Thread("thread 1", 10);
    Thread *t2 = new Thread("thread 2", 10);

    t1->Fork(SimpleThread, 1);
    t2->Fork(SimpleThread, 2);

    // 验证调度器在所有线程优先级相同的情况下的行为
    SimpleThread(0);

    // 只有一个线程
    Thread *t3 = new Thread("thread 3", 20);
    t3->Fork(SimpleThread, 3);

    // 验证调度器在只有一个线程的情况下的行为
    SimpleThread(0);
}
void ThreadTest0(){
    int c=1;
    switch(c)
    {
        case 1:
            TestPrioritySchedulerBasic();
            break;
        case 2:
            TestLargeNumberOfThreads();
            break;
        case 3:
            TestEdgeConditions();
            break;
        default:
            printf("No test specified\n");
            break;
    }
}
