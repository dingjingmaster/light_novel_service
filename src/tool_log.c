/*************************************************************************
> FileName: tool_log.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Wed 22 Nov 2017 06:59:38 PM DST
 ************************************************************************/

#include "tool_log.h"
#include "tool_ret.h"
#include <stdio.h>

int log_init(char* confPath) {
    if(NULL == confPath) {

        return RET_NULL_POINTER;
    }

    int                 rc = 0;

    rc = dzlog_init(confPath, "");
    if(rc) {

        return RET_ERROR;
    }

    return RET_OK;
}

int log_destory(){

    zlog_fini();

    return RET_OK;
}


