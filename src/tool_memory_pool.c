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

typedef struct _MemoryPool MemoryPool;
typedef struct _MemoryBlock MemoryBlock;

struct _MemoryBlock {

	void* 						memPtr; 											// 首地址
	int 							status; 											// status 0 表示未使用 1 表示正在使用

	struct _MemoryBlock* 	next;
};

struct _MemoryPool{

	int 							total; 											// 内存池总大小
	int 							remain; 											// 剩余大小

	Link* 						usedBlock; 										// 已使用内存
	Link* 						remainBlock; 									// 未使用内存
};

int memory_init(void** handle, int size, int num) {

	if(size <= 0 || num <= 0 || NULL == handle) {

		ERROR("memory_init input error -- [size: %d, num: %d]", size, num);
		return RET_ERROR;
	}

	int 							ret = 0;
	MemoryPool* 				memPool = NULL;

	ret = util_malloc((void**)&memPool, sizeof(MemoryPool));
	if(RET_OK != ret) {

		ERROR("util_malloc error");
		return RET_ERROR;
	}






	return RET_OK;
}
