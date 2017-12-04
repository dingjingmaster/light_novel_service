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

        ERROR("util_set_zero input error");
        return RET_NULL_POINTER;
    }

    memset(ptr, 0, len);

    return RET_OK;
}

int util_malloc(void** ptr, int len) {
    if(NULL == ptr || len <= 0) {

        ERROR("util_malloc input error");
        return RET_NULL_POINTER;
    }

    void*           ret = NULL;

    ret = malloc(len);
    if(NULL == ret) {

        *ptr = NULL;
        ERROR("malloc error");
        return RET_ERROR;
    } 
    *ptr = ret;
    memset(*ptr, 0, len);

    return RET_OK;
}

int util_set_noblocking(int fd) {

    int             ret = 0;

    ret = fcntl(fd, F_SETFL, O_NONBLOCK);
    if(ret < 0) {
    
        ERROR("fcntl return error");
        return RET_ERROR;
    }

    return RET_OK;
}
