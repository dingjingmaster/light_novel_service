/*************************************************************************
> FileName: tool_memory_pool.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 27 Nov 2017 02:42:59 PM DST
 ************************************************************************/
#include "tool_memory_pool.h"
#include "tool_ret.h"
#include "tool_log.h"
#include "tool_list.h"
#include "tool_util.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _MemoryPool 	MemoryPool;

struct _MemoryPool{
				
				int																					total;																		// 内存池总大小
				int																					remain;																	// 剩余大小
				Link*																			usedBlock;														// 已使用内存
				Link*																			remainBlock;												// 未使用内存
};

int memory_init(void** handle, int size, int num) {

				if(size <= 0 || num <= 0 || NULL == handle) {

								ERROR("memory_init input error -- [size: %d, num: %d]", size, num);
								return RET_ERROR;
				}

				int																					ret = 0;
				Link*																			usedBlock= NULL;
				Link*																			remainBlock = NULL;
				void*																			memBlock = NULL;
				MemoryPool*													memPool = NULL;

				ret = util_malloc((void**)&memPool, sizeof(MemoryPool)); 			// 创建线程池
				if(RET_OK != ret) {

								ERROR("util_malloc error");
								return RET_ERROR;
				}

				ret = list_init((void**)&remainBlock); 									// 创建链表
				if(RET_OK != ret) {

								ERROR ("list_init error");
								return RET_ERROR;
				}

				ret = list_init((void**)&usedBlock);												// 创建链表
				if(RET_OK != ret) {

								ERROR ("list_init error");
								return RET_ERROR;
				}

				for (int i = 0; i < num; ++ i) {																// 申请内存

								ret = util_malloc(&memBlock, size);
								if(RET_OK != ret) {

								ERROR("util_malloc error");
								return RET_ERROR;																											// 不能退出
								}

								ret = list_add_head((void*)remainBlock, (void*)memBlock);
								if(RET_OK != ret) {

								ERROR("list_add_handle error");
								return RET_ERROR;
								}
				}

				memPool ->remainBlock = remainBlock;
				memPool ->usedBlock = usedBlock;
				memPool ->total = num;
				memPool ->remain = num;

				*handle = memPool;

				return RET_OK;
}

int memory_get(void*handle, void** mem) {

				if(NULL == handle || NULL == mem) {

								ERROR("memory_get input error");

								return RET_ERROR;
				}

				int																									ret = 0;
				int																									remain = 0;
				Link*																							usedBlock= NULL;
				Link*																							remainBlock = NULL;
				LinkNode*																			memTmp = NULL;
				MemoryPool*																	memPool = NULL;

				memPool = (MemoryPool*)handle;

				usedBlock = memPool ->usedBlock;
				remainBlock = memPool ->remainBlock;
				remain = memPool ->remain;

				if (remain <=  0) {

								*mem = NULL;
								return RET_EMPTY_MEMPOOL;
				}

				// 获取内存节点
				ret = list_pop_head(remainBlock, (void**)&memTmp);
				if(RET_OK != ret) {

								ERROR("list_pop_head error");
								return RET_ERROR;
				}

				// 添加到正在使用的队列
				ret = list_insert_node_tail(usedBlock, (void*)memTmp);
				if(RET_OK != ret) {

								ERROR("list_insert_node_tail error");
								return RET_ERROR;
				}

				ret = list_get_value(memTmp, mem);
				if (RET_OK != ret) {

								ERROR("list_get_value error");
								return RET_ERROR;
				}

				-- (memPool ->remain);

				return RET_OK;
}

// 放回内存池
int memory_put(void* handle, void** mem) {
	
				if(NULL == handle || NULL == mem) {

								ERROR("memory_put input error");
								return RET_NULL_POINTER;
				}

				int																					ret = 0;
				Link*																			usedBlock= NULL;
				Link*																			remainBlock = NULL;
				LinkNode*															memTmp = NULL;
				MemoryPool*													memPool = NULL;

				memPool = (MemoryPool*)handle;

				usedBlock = memPool ->usedBlock;
				remainBlock = memPool ->remainBlock;

				// 不需要放回
				if (NULL == *mem) {

								return RET_OK;
				}

				// 获取内存节点
				ret = list_pop_by_value(usedBlock, *mem, (void**)&memTmp);
				if(RET_OK != ret) {

								ERROR("list_pop_head error");
								return RET_ERROR;
				}

				// 添加到正在使用的队列
				ret = list_insert_node_tail(remainBlock, (void*)memTmp);
				if(RET_OK != ret) {

								ERROR("list_insert_node_tail error");
								return RET_ERROR;
				}

				++ (memPool ->remain);

				*mem = NULL;

				return RET_OK;
}

int memory_destory(void** handle) {
	
				if(NULL == *handle) {

								ERROR("memory_destory error");
								return RET_ERROR;
				}

				Link*																			usedBlock= NULL;
				Link*																			remainBlock = NULL;
				MemoryPool*													memPool = NULL;

				memPool = (MemoryPool*)(*handle);

				usedBlock = memPool ->usedBlock;
				remainBlock = memPool ->remainBlock;

				list_destroy((void**)&usedBlock);
				list_destroy((void**)&remainBlock);

				free(memPool);

				*handle = NULL;

				return RET_OK;
}
