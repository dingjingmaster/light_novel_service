/*************************************************************************
	> FileName: tool_threadpool.c
	> Author  : DingJing
	> Mail    : dingjing@live.cn
	> Created Time: 2017年06月20日 星期二 10时21分21秒
 ************************************************************************/

#include "tool_thread_pool.h"
#include "tool_ret.h"
#include "tool_log.h"
#include "tool_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* threadpool_routine(void* args); 											//  每个线程都执行

static PthreadPool* 					threadPool = NULL;
int                   				worker = 1000;

struct _PthreadWorker {

	worker_callback             	worker; 										// work 回调函数
	void*                       	argv; 										// 参数
	struct _PthreadWorker*      	next;
};

struct _PthreadPool
{
    int               				maxThreadNum; 								// 最大线程数
    int               				shutDown; 									// 是否关闭
    int               				workerNum; 									// 正在使用的线程数
    pthread_t*        				threadId; 									// 线程池中的所有线程id
    PthreadWorker*    				workerHead; 								// 任务链表的头链表
    pthread_mutex_t   				lock; 										// 互斥锁
    pthread_cond_t    				ready; 										// 条件变量
};

void* threadpool_routine(void *args) {
	
	while(1) {

		DEBUG("thread %lu create successful", pthread_self());
		pthread_mutex_lock(&(threadPool ->lock));
		
		while((threadPool ->shutDown == 0) && (threadPool ->workerNum == 0)) {

			printf("thread %lu is waiting for work\n", pthread_self());
			pthread_cond_wait(&(threadPool ->ready), &(threadPool ->lock));
		}
		
		if((threadPool ->shutDown) == 1) {

			DEBUG("thread %lu exit", pthread_self());
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

int threadpool_init(int num) {
	
	if(num <= 0) {
		
		ERROR ("threadpool_init input error");
		return RET_ERROR;
	}
	
	int               				i = 0;
   int             					ret = 0;

	ret = util_malloc((void**)&threadPool, sizeof(PthreadPool));
   if(RET_OK != ret) {
		
		ERROR("util_malloc error");
		return RET_ERROR;
   }

	ret = util_set_zero(threadPool, sizeof(PthreadPool));
	if(RET_OK != ret) {

		ERROR("util_set_zero error");
		return RET_ERROR;
	}

   //  start
   threadPool ->maxThreadNum = num;
   threadPool ->shutDown = 0;
   threadPool ->workerNum = 0;
   threadPool ->workerHead = NULL;

   pthread_mutex_init(&(threadPool ->lock), NULL);
   pthread_cond_init(&(threadPool ->ready), NULL);

   //  create thread
   //mallocSize = sizeof(pthread_t) * num;
   //ret = threadPool ->threadId = (pthread_t*)malloc(mallocSize);
	ret = util_malloc((void**)&(threadPool ->threadId), sizeof(pthread_t) * num);
	if(RET_OK == ret) {
		
		ERROR ("util_malloc error");
      return RET_ERROR;
   }
	
	//memset(threadPool ->threadId, 0, mallocSize);
	ret = util_set_zero((threadPool ->threadId), num * sizeof(PthreadPool));
	if(RET_OK != ret) {

		ERROR("util_set_zero error");
		return RET_ERROR;
	}

   //  num thread id
   for(i = 0; i < num; ++i) {
		
		ret = pthread_create(&(threadPool ->threadId[i]), NULL, threadpool_routine, NULL);
      if(ret != 0) {
			
			ERROR ("pthread_create error");
         return RET_ERROR;
      }
	}

    return RET_OK;
}

int threadpool_add_work(worker_callback workFunc, void* argv) {
	
	if(NULL == workFunc) {
		
		return RET_NULL_POINTER;
   }

   //  
   PthreadWorker*       workerTmp = NULL;
   PthreadWorker*       pCur = NULL;

   workerTmp = (PthreadWorker*) malloc (sizeof(PthreadWorker));
   if(NULL == workerTmp) {

      ERROR("work malloc error");

      return RET_ERROR;
   }

   memset(workerTmp, 0, sizeof(PthreadWorker));

   workerTmp ->worker = workFunc;
   workerTmp ->argv = argv;
   workerTmp ->next = NULL;

   //  lock
   pthread_mutex_lock(&(threadPool ->lock));

   pCur = threadPool ->workerHead;

   while(1) {
		
		if(NULL == (threadPool ->workerHead)) {
			
			threadPool ->workerHead = workerTmp;
			break;
      } else if (NULL == (pCur ->next)) {
			
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

int threadpool_destroy(void) {
	
	if(1 == (threadPool ->shutDown)) {
		
		return RET_OK;
   }

   int                   i = 0;
   PthreadWorker*        pHead = NULL;
   PthreadWorker*        pNext = NULL;

   threadPool ->shutDown = 1;
    
   pthread_cond_broadcast(&(threadPool ->ready));

   for(i = 0; i < (threadPool ->maxThreadNum); ++i) {
		
		pthread_join((threadPool ->threadId[i]), NULL);
   }

   if(NULL != (threadPool ->threadId)) {
		
		free(threadPool ->threadId);
   }
	
	pHead = (threadPool ->workerHead);

   while(NULL != pHead) {
		
		pNext = pHead ->next;
      free(pHead);
      pHead = pNext ->next;
   }
	
	pthread_mutex_destroy(&(threadPool ->lock));
   pthread_cond_destroy(&(threadPool ->ready));

	if(NULL != threadPool) {
		
      free(threadPool);
	}
    
    return RET_OK;
}


