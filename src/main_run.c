/*************************************************************************
> FileName: main_run.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 23 Nov 2017 03:53:33 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include "tool_log.h"
#include "main_run.h"
#include <stdio.h>

int server_main(int argc, char* argv[]) {

    unsigned short                  port = 3000;
    int                             ret = 0;
    void*                           handle = NULL;

    // 初始化日志
    ret = log_init("./conf/log.conf");
    if(RET_OK != ret) {

        return RET_ERROR;
    }


    // 获得handle
    ret = get_rpc_handle(port, &handle);
    if(RET_OK != ret) {

        ERROR("获取 rpc handle 错误 ...");
        return RET_ERROR;
    }


    DEBUG("获取 rpc handle 成功 ...");
    // 初始化 handle
    ret = rpc_socket_init(handle);
    if(RET_OK != ret) {

        ERROR("服务端 socket 初始化失败 ...");
        return RET_ERROR;
    }

    DEBUG("服务端 socket 初始化成功 ...");

    // 关闭socket
    ret = rpc_socket_close(handle);
    if(RET_OK != ret) {

        puts("socket 关闭失败...");
    }
    puts("获取socket close成功");

    // 服务关闭
    ret = free_rpc_handle(&handle);
    if(RET_OK != ret) {

        puts("服务资源释放失败...");

        return RET_ERROR;
    }

    return RET_OK;
}

