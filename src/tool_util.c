/*************************************************************************
> FileName: ./tool_util.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Wed 22 Nov 2017 03:27:25 PM DST
 ************************************************************************/

#include "tool_util.h"
#include "tool_ret.h"
#include "tool_log.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// zero
int util_set_zero(void* ptr, int len){
    if(NULL == ptr) {

        ERROR("传入参数空指针错误 ...");
        return RET_NULL_POINTER;
    }

    memset(ptr, 0, len);

    return RET_OK;
}

int util_malloc(void** ptr, int len) {
    if(NULL == ptr || NULL == *ptr || len <= 0) {

        ERROR("传入参数空指针错误 ...");
        return RET_NULL_POINTER;
    }

    void*           ret = NULL;
    int             retInt = 0;
    ret = malloc(len);
    if(NULL != ret) {

        *ptr = ret;
        retInt = util_set_zero(*ptr, len);
        if(RET_OK != retInt) {

            ERROR("内存格式化失败 ...");
            free(ret);
            *ptr = NULL;

            return RET_ERROR;
        }

        return RET_OK;
    }
    *ptr = NULL;
    ERROR("内存分配失败 ...");

    return RET_ERROR;
}

int util_set_noblocking(int fd) {

    int             ret = 0;

    ret = fcntl(fd, F_SETFL, O_NONBLOCK);
    if(ret < 0) {
    
        ERROR("设置文件描述符非阻塞错误 ...");
        return RET_ERROR;
    }

    return RET_OK;
}
