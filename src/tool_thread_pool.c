/*************************************************************************
	> FileName: tool_threadpool.c
	> Author  : DingJing
	> Mail    : dingjing@live.cn
	> Created Time: 2017年06月20日 星期二 10时21分21秒
 ************************************************************************/

#include "tool_ret.h"
#include "tool_thread_pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//  每个线程都执行
void* threadpool_routine(void *args);

static PthreadPool*   threadPool = NULL;
int                   worker = 50;

int cthread_pool_home_init(int num)
{
    if(num <= 0)
    {
        return RET_ERROR;
    }

    int               i = 0;
    void*             ret = NULL;
    int               retInt = 0;
    unsigned int      mallocSize = 0;
    pthread_t         threadTmp = 0;


    mallocSize = sizeof(PthreadPool);

    ret = threadPool = (PthreadPool*)malloc(mallocSize);
    if(NULL == ret)
    {
        return RET_ERROR;
    }

    memset(threadPool, 0, mallocSize);

    //  start
    threadPool ->maxThreadNum = num;
    threadPool ->shutDown = 0;
    threadPool ->workerNum = 0;
    threadPool ->workerHead = NULL;

    pthread_mutex_init(&(threadPool ->lock), NULL);
    pthread_cond_init(&(threadPool ->ready), NULL);

    //  create thread
    mallocSize = sizeof(pthread_t) * num;
    ret = threadPool ->threadId = (pthread_t*)malloc(mallocSize);
    if(NULL == ret)
    {
        puts("线程池内存分配错误");
        return RET_ERROR;
    }

    memset(threadPool ->threadId, 0, mallocSize);

    //  num thread id
    for(i = 0; i < num; ++i)
    {
        retInt = pthread_create(&(threadPool ->threadId[i]), NULL, threadpool_routine, NULL);
        if(retInt != 0)
        {
            puts("创建线程错误!!!");
            return RET_ERROR;
        }

    }

    return RET_OK;
}


void* threadpool_routine(void *args)
{
    while(1)
    {
        printf("thread %lu Created successful\n", pthread_self());

        pthread_mutex_lock(&(threadPool ->lock));

        while((threadPool ->shutDown == 0) && (threadPool ->workerNum == 0))
        {
            printf("thread %lu is waiting for work\n", pthread_self());

            pthread_cond_wait(&(threadPool ->ready), &(threadPool ->lock));
        }

        if((threadPool ->shutDown) == 1)
        {
            puts("退出了");
            pthread_mutex_unlock(&(threadPool ->lock));

            pthread_exit(NULL);
        }

        //  do work
        -- (threadPool ->workerNum);

        PthreadWorker*  worker = (threadPool ->workerHead);
        threadPool ->workerHead = (threadPool ->workerHead) ->next;

        pthread_mutex_unlock(&(threadPool ->lock));
    
        (*(worker ->worker))(worker ->argv);

        free (worker);

        worker = NULL;
    }
}

int threadpool_add_work(worker_callback workFunc, void* argv)
{
    if(NULL == workFunc)
    {
        return RET_NULL_POINTER;
    }

    //  
    PthreadWorker*       workerTmp = NULL;
    PthreadWorker*       pCur = NULL;

    workerTmp = (PthreadWorker*) malloc (sizeof(PthreadWorker));
    if(NULL == workerTmp)
    {
        puts("work 分配内存失败!!!");

        return RET_ERROR;
    }

    memset(workerTmp, 0, sizeof(PthreadWorker));

    workerTmp ->worker = workFunc;
    workerTmp ->argv = argv;
    workerTmp ->next = NULL;

    //  lock
    pthread_mutex_lock(&(threadPool ->lock));

    pCur = threadPool ->workerHead;

    while(1)
    {
        if(NULL == (threadPool ->workerHead))
        {
            threadPool ->workerHead = workerTmp;

            break;
        }
        else if (NULL == (pCur ->next))
        {
            pCur ->next = workerTmp;

            break;
        }
        
        pCur = pCur ->next;
    }

    ++ (threadPool ->workerNum);

    pthread_mutex_unlock(&(threadPool ->lock));
    pthread_cond_signal(&(threadPool ->ready));

    return RET_OK;
}

int cthread_pool_home_destroy()
{
    if(1 == (threadPool ->shutDown))
    {
        return RET_OK;
    }

    int                   i = 0;
    PthreadWorker*        pHead = NULL;
    PthreadWorker*        pNext = NULL;

    threadPool ->shutDown = 1;
    
    pthread_cond_broadcast(&(threadPool ->ready));

    for(i = 0; i < (threadPool ->maxThreadNum); ++i)
    {
        pthread_join((threadPool ->threadId[i]), NULL);
    }

    if(NULL != (threadPool ->threadId))
    {
        free(threadPool ->threadId);
    }

    pHead = (threadPool ->workerHead);

    while(NULL != pHead)
    {
        pNext = pHead ->next;
        free(pHead);
        pHead = pNext ->next;
    }

    pthread_mutex_destroy(&(threadPool ->lock));
    pthread_cond_destroy(&(threadPool ->ready));

    if(NULL != threadPool)
    {
        free(threadPool);
    }
    

    return RET_OK;
}


