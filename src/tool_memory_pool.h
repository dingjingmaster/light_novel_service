/*************************************************************************
> FileName: tool_memory_pool.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 27 Nov 2017 02:42:55 PM DST
 ************************************************************************/

#ifndef _TOOL_MEMORY_POOL_H
#define _TOOL_MEMORY_POOL_H
#ifdef __cplusplus
extern "C" {
#endif


int memory_init(void** handle, int size, int num);
int memory_get(void*handle, void** mem);
int memory_destory(void** handle);

#ifdef __cplusplus
}
#endif
#endif
