/*************************************************************************
> FileName: tool_util.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Wed 22 Nov 2017 03:27:16 PM DST
 ************************************************************************/

#ifndef _TOOL_UTIL_H
#define _TOOL_UTIL_H
#include <string.h>

/**
 *  ptr         内存起始地址
 *  len         内存长度
 */
int util_set_zero(void* ptr, int len);

int util_malloc(void** ptr, int len);

int util_set_noblocking(int fd);


#endif
