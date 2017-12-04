/*************************************************************************
	> File Name: tool_thread_pool.h
	> Author: DingJing
	> Mail: dingjing@live.cn
	> Created Time: 2017年06月20日 星期二 09时59分15秒
 ************************************************************************/

#ifndef _TOOL_THREAD_POOL_H
#define _TOOL_THREAD_POOL_H


typedef   struct _PthreadPool    PthreadPool; 								// 线程池结构体
typedef   struct _PthreadWorker  PthreadWorker; 							// 任务结构体
typedef void* (*worker_callback)(void* argv); 								// 任务回调

/**
 * 线程池初始化操作
 * 输入输出: handle 线程池句柄
 * 输入    : num 线程池中线程的数量
 */
int threadpool_init(int num);

/**
 * 在线程池中添加任务
 * 输入: handle 线程池的句柄
 * 输入: workFunc 自定义的任务执行函数
 * 输入: argv 自定义的任务函数参数
 */
int threadpool_add_work(worker_callback workFunc, void* argv);

/**
 * 线程池的销毁
 * 输入输出: handle 线程池的句柄
 */
int threadpool_destroy(void);











#endif
