/*************************************************************************
	> File Name: tool_threadpool.h
	> Author: DingJing
	> Mail: dingjing_ding@staff.easou.com
	> Created Time: 2017年06月20日 星期二 09时59分15秒
 ************************************************************************/

#ifndef _TOOL_THREADPOOL_H
#define _TOOL_THREADPOOL_H

#include <pthread.h>

typedef   struct _PthreadPool    PthreadPool;
typedef   struct _PthreadWorker  PthreadWorker;

typedef void* (*worker_callback)(void* argv);

struct _PthreadWorker
{
    worker_callback             worker;
    void*                       argv;

    struct _PthreadWorker*      next;
};

struct _PthreadPool
{
    int               maxThreadNum;
    int               shutDown;
    int               workerNum;

    pthread_t*        threadId;

    PthreadWorker*    workerHead;

    pthread_mutex_t   lock;
    pthread_cond_t    ready;
};

//  thread pool init
int threadpool_init(int num);

//  add work
int threadpool_add_work(worker_callback workFunc, void* argv);

//  thread pool destroy
int threadpool_destroy();











#endif
