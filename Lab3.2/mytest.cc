//�������ȼ����Ȳ���
void TestPrioritySchedulerBasic() {
    DEBUG('t', "Entering TestPrioritySchedulerBasic");

    // �������в�ͬ���ȼ����߳�
    Thread *t1 = new Thread("thread 1", 10);
    Thread *t2 = new Thread("thread 2", 20);
    Thread *t3 = new Thread("thread 3", 15);

    t1->Fork(SimpleThread, 1);
    t2->Fork(SimpleThread, 2);
    t3->Fork(SimpleThread, 3);

    // ��֤�����ȼ����߳��Ƿ����ȱ�����
    SimpleThread(0);
}
//�����̲߳���
void TestLargeNumberOfThreads() {
    DEBUG('t', "Entering TestLargeNumberOfThreads");

    const int NUM_THREADS = 100;
    Thread *threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        int priority = Random() % 100;
        threads[i] = new Thread(std::string("thread ") + std::to_string(i), priority);
        threads[i]->Fork(SimpleThread, i);
    }

    // ��֤�������ڸ߸�������µ����ܺ��ȶ���
    SimpleThread(0);
}
//�߽���������
void TestEdgeConditions() {
    DEBUG('t', "Entering TestBoundaryConditions");

    // �����߳����ȼ���ͬ
    Thread *t1 = new Thread("thread 1", 10);
    Thread *t2 = new Thread("thread 2", 10);

    t1->Fork(SimpleThread, 1);
    t2->Fork(SimpleThread, 2);

    // ��֤�������������߳����ȼ���ͬ������µ���Ϊ
    SimpleThread(0);

    // ֻ��һ���߳�
    Thread *t3 = new Thread("thread 3", 20);
    t3->Fork(SimpleThread, 3);

    // ��֤��������ֻ��һ���̵߳�����µ���Ϊ
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
