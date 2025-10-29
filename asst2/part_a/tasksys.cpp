#include "tasksys.h"
#include <vector>
#include <cassert>
IRunnable::~IRunnable() {}

ITaskSystem::ITaskSystem(int num_threads) {}
ITaskSystem::~ITaskSystem() {}

/*
 * ================================================================
 * Serial task system implementation
 * ================================================================
 */

const char* TaskSystemSerial::name() {
    return "Serial";
}

TaskSystemSerial::TaskSystemSerial(int num_threads): ITaskSystem(num_threads) {
}

TaskSystemSerial::~TaskSystemSerial() {}

void TaskSystemSerial::run(IRunnable* runnable, int num_total_tasks) {
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemSerial::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                          const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemSerial::sync() {
    // You do not need to implement this method.
    return;
}


/*
 * ================================================================
 * Parallel Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelSpawn::name() {
    return "Parallel + Always Spawn";
}

TaskSystemParallelSpawn::TaskSystemParallelSpawn(int num_threads): ITaskSystem(num_threads),
    _num_threads(num_threads),_threads_worker(new std::thread[num_threads]){//��Ա������ʼ��
    //
    // TODO: CS149 student implementations may decide to perform setup
    // operations (such as thread pool construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
}

TaskSystemParallelSpawn::~TaskSystemParallelSpawn() {
    delete[] _threads_worker;//����
}

//�߳�ִ��
void TaskSystemParallelSpawn::threadRun(IRunnable* runnable, int num_total_tasks,std::mutex* mutex, int* curr_task)
{
    int turn = -1;
    while(turn < num_total_tasks)//taskȫ��������
    {
        mutex->lock();//����
        turn = *curr_task;//��ȡ��ǰ����task��λ��,curr_task�洢�����߳�������task��Ŀ
        *curr_task+=1;
        mutex->unlock();
        if(turn >= num_total_tasks)
        break;
        runnable->runTask(turn, num_total_tasks);//����һ��task��
    }
}

void TaskSystemParallelSpawn::run(IRunnable* runnable, int num_total_tasks) {


    //
    // TODO: CS149 students will modify the implementation of this
    // method in Part A.  The implementation provided below runs all
    // tasks sequentially on the calling thread.
    //
    std::mutex* mutex = new std::mutex();
    int* curr_task = new int;
    *curr_task = 0;
    for(int i=0; i<_num_threads; i++)//�����߳�
    {
        _threads_worker[i] = std::thread(&TaskSystemParallelSpawn::threadRun,this,runnable,num_total_tasks,mutex,curr_task);
    }
    for(int i=0;i<_num_threads;i++)
    {
        _threads_worker[i].join();//�ȴ��߳̽�����runΪͬ������
    }
    delete curr_task;//ɾ���ڴ�ռ��
    delete mutex;
    // for (int i = 0; i < num_total_tasks; i++) {
    //     runnable->runTask(i, num_total_tasks);
    // }
}

TaskID TaskSystemParallelSpawn::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                 const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemParallelSpawn::sync() {
    // You do not need to implement this method.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Spinning Task System Implementation
 * ================================================================
 */



const char* TaskSystemParallelThreadPoolSpinning::name() {
    return "Parallel + Thread Pool + Spin";
}

TaskSystemParallelThreadPoolSpinning::TaskSystemParallelThreadPoolSpinning(int num_threads): ITaskSystem(num_threads) {
    //
    // TODO: CS149 student implementations may decide to perform setup
    // operations (such as thread pool construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
}

TaskSystemParallelThreadPoolSpinning::~TaskSystemParallelThreadPoolSpinning() {}

void TaskSystemParallelThreadPoolSpinning::run(IRunnable* runnable, int num_total_tasks) {


    //
    // TODO: CS149 students will modify the implementation of this
    // method in Part A.  The implementation provided below runs all
    // tasks sequentially on the calling thread.
    //

    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelThreadPoolSpinning::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                              const std::vector<TaskID>& deps) {
    // You do not need to implement this method.
    return 0;
}

void TaskSystemParallelThreadPoolSpinning::sync() {
    // You do not need to implement this method.
    return;
}

/*
 * ================================================================
 * Parallel Thread Pool Sleeping Task System Implementation
 * ================================================================
 */

const char* TaskSystemParallelThreadPoolSleeping::name() {
    return "Parallel + Thread Pool + Sleep";
}

TaskSystemParallelThreadPoolSleeping::TaskSystemParallelThreadPoolSleeping(int num_threads): ITaskSystem(num_threads) {
    //�����̳߳أ���ʼʱȫ��˯��


    // TODO: CS149 student implementations may decide to perform setup
    // operations (such as thread pool construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
    _num_threads = num_threads;//�߳���Ŀ
    cur = 0;
    stop = false;
    _num_total_tasks=-1;
    _runnable = nullptr;
    stop = false;
    for(int i=0; i<_num_threads; i++)
        workers.emplace_back(
        [this](){
            for(;;)
            {
                int turn;
                {
                    std::unique_lock<std::mutex> lock(this->cur_task_mutex);//����
                    this->condition.wait(lock,
                        [this]{return this->stop || this->cur<=this->_num_total_tasks;});//�̳߳�δֹͣ����������ִ���������
                    
                    if(this->cur>=this->_num_total_tasks && this->stop)//ִ�������̳߳�ֹͣ
                    return;
                    turn = this->cur;
                    this->cur++;
                }
                this->_runnable->runTask(turn, this->_num_total_tasks);//����һ������
            }
        }
        );
}

TaskSystemParallelThreadPoolSleeping::~TaskSystemParallelThreadPoolSleeping() {
    //
    // TODO: CS149 student implementations may decide to perform cleanup
    // operations (such as thread pool shutdown construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
    {
        std::unique_lock<std::mutex> lock(cur_task_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread & worker : workers)
        worker.join();
}

void TaskSystemParallelThreadPoolSleeping::run(IRunnable* runnable, int num_total_tasks) {


    //
    // TODO: CS149 students will modify the implementation of this
    // method in Parts A and B.  The implementation provided below runs all
    // tasks sequentially on the calling thread.
    //

    // for (int i = 0; i < num_total_tasks; i++) {
    //     runnable->runTask(i, num_total_tasks);
    // }
    assert(runnable != nullptr && "runnable cannot be null"); 
    {
        std::unique_lock<std::mutex> lock(this->cur_task_mutex);
        this->cur=0;
        this->_num_total_tasks = num_total_tasks;
        this->_runnable = runnable;
    }
    if(num_total_tasks !=0)
    condition.notify_all();//����˯�ߵ��߳�
    

}

TaskID TaskSystemParallelThreadPoolSleeping::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                    const std::vector<TaskID>& deps) {


    //
    // TODO: CS149 students will implement this method in Part B.
    //

    return 0;
}

void TaskSystemParallelThreadPoolSleeping::sync() {

    //
    // TODO: CS149 students will modify the implementation of this method in Part B.
    //

    return;
}
