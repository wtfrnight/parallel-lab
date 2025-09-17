#include <stdio.h>
#include <thread>
#include "CycleTimer.h"

typedef struct {
    float x0, x1;
    float y0, y1;
    unsigned int width;
    unsigned int height;
    int maxIterations;
    int* output;
    int threadId;
    int numThreads;
} WorkerArgs;


extern void mandelbrotSerial(
    float x0, float y0, float x1, float y1,
    int width, int height,
    int startRow, int numRows,
    int maxIterations,
    int output[]);



// workerThreadStart --

// Thread entrypoint.
// void workerThreadStart(WorkerArgs * const args) {

//     // TODO FOR CS149 STUDENTS: Implement the body of the worker
//     // thread here. Each thread should make a call to mandelbrotSerial()
//     // to compute a part of the output image.  For example, in a
//     // program that uses two threads, thread 0 could compute the top
//     // half of the image and thread 1 could compute the bottom half.
    
//     // CS149学生任务：在此处实现工作线程的函数体。
//     // 每个线程都应调用mandelbrotSerial()来计算输出图像的一部分。
//     // 例如，在使用两个线程的程序中，线程0可计算图像的上半部分，
//     // 线程1可计算图像的下半部分
//     int rowtask = (args->height) / args->numThreads;
//     int rowbegin = args->threadId * rowtask; 
//     int rowend = rowbegin + rowtask;
//     if(args->threadId == args->numThreads - 1) 
//     rowend = args->height;
//     double t_startTime = CycleTimer::currentSeconds();
//     mandelbrotSerial(
//         args->x0,args->y0,args->x1,args->y1,
//         args->width,args->height,
//         rowbegin,rowend-rowbegin,
//         args->maxIterations,
//         args->output
//     );
//     double t_endTime = CycleTimer::currentSeconds();
//     printf("Thread %d from %d to %d : [%.3f] ms \n", args->threadId , rowbegin, rowend,  (t_endTime-t_startTime)*1000);
// }

void workerThreadStart(WorkerArgs * const args) {

    // TODO FOR CS149 STUDENTS: Implement the body of the worker
    // thread here. Each thread should make a call to mandelbrotSerial()
    // to compute a part of the output image.  For example, in a
    // program that uses two threads, thread 0 could compute the top
    // half of the image and thread 1 could compute the bottom half.
    
    // CS149学生任务：在此处实现工作线程的函数体。
    // 每个线程都应调用mandelbrotSerial()来计算输出图像的一部分。
    // 例如，在使用两个线程的程序中，线程0可计算图像的上半部分，
    // 线程1可计算图像的下半部分

    int Chunk_size =16;
    int step = args->numThreads * Chunk_size;

    double t_startTime = CycleTimer::currentSeconds();

    for(int cur_row = args->threadId * Chunk_size;
        cur_row < args->height;
        cur_row += step)
    {
        int numrows = std::min(Chunk_size,(int)args->height-cur_row);
        
        mandelbrotSerial(
        args->x0,args->y0,args->x1,args->y1,
        args->width,args->height,
        cur_row,numrows,
        args->maxIterations,
        args->output
        );
//        printf("Thread %d form %d to %d\n", args->threadId ,cur_row, cur_row+numrows);
    }
    double t_endTime = CycleTimer::currentSeconds();
    printf("Thread %d  : [%.3f] ms \n", args->threadId ,(t_endTime-t_startTime)*1000);
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning std::threads.
void mandelbrotThread(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    static constexpr int MAX_THREADS = 32;

    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    // Creates thread objects that do not yet represent a thread.
    std::thread workers[MAX_THREADS];
    WorkerArgs args[MAX_THREADS];

    for (int i=0; i<numThreads; i++) {
      
        // TODO FOR CS149 STUDENTS: You may or may not wish to modify
        // the per-thread arguments here.  The code below copies the
        // same arguments for each thread
        
        // CS149学生任务：你可能需要（也可能不需要）在此处修改
        // 每个线程的参数。下面的代码为所有线程复制了
        // 相同的基础参数（需根据任务划分逻辑调整）
        args[i].x0 = x0;
        args[i].y0 = y0;
        args[i].x1 = x1;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].numThreads = numThreads;
        args[i].output = output;
        args[i].threadId = i;
    }

    // Spawn the worker threads.  Note that only numThreads-1 std::threads
    // are created and the main application thread is used as a worker
    // as well.
    for (int i=1; i<numThreads; i++) {
        workers[i] = std::thread(workerThreadStart, &args[i]);
    }
    
    workerThreadStart(&args[0]);

    // join worker threads
    for (int i=1; i<numThreads; i++) {
        workers[i].join();
    }
}

