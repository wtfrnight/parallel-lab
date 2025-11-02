#include "tasksys.h"


IRunnable::~IRunnable() {}

ITaskSystem::ITaskSystem(int num_threads) {}
ITaskSystem::~ITaskSystem() {}

Information_table::Information_table(IRunnable* runnable, int num_total_tasks, const std::vector<TaskID>& deps)
:_runnable(runnable),_num_total_tasks(num_total_tasks),_deps(deps),dep_count(deps.size()),over(false),cur_task(0),remain_task(num_total_tasks)
{}

Information_table::~Information_table()//?析构函数
{
    
}

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
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemSerial::sync() {
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

TaskSystemParallelSpawn::TaskSystemParallelSpawn(int num_threads): ITaskSystem(num_threads) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
}

TaskSystemParallelSpawn::~TaskSystemParallelSpawn() {}

void TaskSystemParallelSpawn::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelSpawn::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                 const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelSpawn::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelSpawn in Part B.
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
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
}

TaskSystemParallelThreadPoolSpinning::~TaskSystemParallelThreadPoolSpinning() {}

void TaskSystemParallelThreadPoolSpinning::run(IRunnable* runnable, int num_total_tasks) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }
}

TaskID TaskSystemParallelThreadPoolSpinning::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                              const std::vector<TaskID>& deps) {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
    for (int i = 0; i < num_total_tasks; i++) {
        runnable->runTask(i, num_total_tasks);
    }

    return 0;
}

void TaskSystemParallelThreadPoolSpinning::sync() {
    // NOTE: CS149 students are not expected to implement TaskSystemParallelThreadPoolSpinning in Part B.
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
    //
    // TODO: CS149 student implementations may decide to perform setup
    // operations (such as thread pool construction) here.
    // Implementations are free to add new class member variables
    // (requiring changes to tasksys.h).
    //
    active_batch = 0;
    stop=false;
    for(int i=0; i<num_threads; i++)
        workers.emplace_back(
            [this](){
                for(;;)
                {
                    int turn;
                    TaskID r_Task;
                    IRunnable* _runnable =nullptr;
                    int _num_total_tasks =0;
                    {
                        std::unique_lock<std::mutex> lock(this->_mutex);//任务队列上锁
                        this->condition.wait(lock,
                            [this]{return this->stop || !this->ready_task.empty();});
                        
                        if(this->stop && this->ready_task.empty())//
                            return;

                        r_Task = ready_task.front();//取任务ID
                        turn = map[r_Task]->cur_task.fetch_add(1);
                        _runnable = map[r_Task]->_runnable;
                        _num_total_tasks = map[r_Task]->_num_total_tasks;

                        //condition.notify_one();
                    }
                    if(turn<_num_total_tasks)
                    {
                        _runnable->runTask(turn,_num_total_tasks);
                        if(map[r_Task]->remain_task.fetch_sub(1) == 1)
                        {
                            std::unique_lock<std::mutex> lock(this->_mutex);//任务队列上锁
                            ready_task.pop();//完成任务出队列
                            active_batch.fetch_sub(1);
                            for(auto i:dep_map[r_Task])
                            {
                                map[i]->dep_count--;
                                if(map[i]->dep_count==0)
                                {
                                    ready_task.push(i);//任务就绪
                                }
                            }
                            map[r_Task]->over=true;
                            condition.notify_all();//唤醒工作线程或者asyn


                        }
                    }
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
        std::unique_lock<std::mutex> lock(_mutex);
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
    std::vector<TaskID> no_deps;
    runAsyncWithDeps(runnable, num_total_tasks, no_deps);
    sync();
}

TaskID TaskSystemParallelThreadPoolSleeping::runAsyncWithDeps(IRunnable* runnable, int num_total_tasks,
                                                    const std::vector<TaskID>& deps) {

    int task_ID;
    Information_table* newtable = new Information_table(runnable,num_total_tasks,deps);
    {
        std::unique_lock<std::mutex> lock(_mutex);//元信息表上锁
        task_ID = cur_ID;
        map.insert({task_ID,newtable});
        cur_ID++;
        active_batch.fetch_add(1);
        for(auto i:deps)
        {
            dep_map[i].insert(task_ID);//填写依赖关系表
            if(map[i]->over==true)
            map[task_ID]->dep_count.fetch_sub(1);
        } 
    }
    if(map[task_ID]->dep_count==0)//独立任务
    {
        std::unique_lock<std::mutex> lock(_mutex);//就绪任务队列上锁
        ready_task.push(task_ID);
        condition.notify_all();
    }
    return task_ID;                                                    
    //
    // TODO: CS149 students will implement this method in Part B.
    //

    // for (int i = 0; i < num_total_tasks; i++) {
    //     runnable->runTask(i, num_total_tasks);
    // }
                                              
    return 0;
}

void TaskSystemParallelThreadPoolSleeping::sync() {

    //
    // TODO: CS149 students will modify the implementation of this method in Part B.
    //
    {
        std::unique_lock<std::mutex> lock(_mutex);
    // 阻塞等待，直到所有批量任务完成
        condition.wait(lock, [this](){ return active_batch == 0; });
    }
    return;
}
