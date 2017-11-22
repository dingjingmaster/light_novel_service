/*************************************************************************
> FileName: tool_rpc.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:10 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include "tool_socket.h"
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

typedef struct _ToolRpc ToolRpc;

struct _ToolRpc {
    int                 servFd;                         // 服务端文件描述符
    int                 epollFd;                        // epoll文件描述符
    int                 status;                         // 状态(0正常运行, 1关闭)
    char*               sendBuf;                        // 发送缓冲区
    char*               recvBuf;                        // 接收缓冲区
    unsigned short      port;                           // 端口
};

int get_rpc_handle(unsigned short port, void** handle){
    if(NULL == handle || 0 > port){

        return RET_NULL_POINTER;
    }

    ToolRpc* toolRpc = NULL;


    // 分配内存
    toolRpc = (ToolRpc*) malloc (sizeof(ToolRpc));
    toolRpc ->sendBuf = (char*)malloc(sizeof(char) * SEND_BUFFER);
    toolRpc ->recvBuf = (char*)malloc(sizeof(char) * RECV_BUFFER);

    // 赋值
    toolRpc ->port = port;
    toolRpc ->status = 0;

    *handle = toolRpc;

    return RET_OK;
}

// 初始化
int rpc_socket_init(void* handle) {

    int                     ret = 0;
    int*                    servFd;
    int*                    epollFd;
    struct sockaddr_in      servAddr;
    struct epoll_event      event;

    int port = ((ToolRpc*)handle) ->port;

    ret = util_socket(AF_INET, SOCK_STREAM, 0, servFd);
    if(RET_OK != ret) {

        return ret;
    }

    ret = util_set_zero(&servAddr, sizeof(struct sockaddr_in));
    if(RET_OK != ret) {

        return ret;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    ret = util_bind(*servFd, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if(RET_OK != ret) {

        return ret;
    }

    ret = util_listen(*servFd, 128);
    if(RET_OK != ret) {

        return ret;
    }

    ret = util_epoll_create(EVENT_NUM, epollFd);
    if(RET_OK != ret) {

        return ret;
    }

    event.data.fd = *servFd;
    event.events = EPOLLIN;
    ret = util_epoll_ctl(*epollFd, EPOLL_CTL_ADD, *servFd, &event);
    if(RET_OK != ret) {

        return ret;
    }

    // 保存
    ((ToolRpc*)handle) ->servFd = *servFd;
    ((ToolRpc*)handle) ->epollFd= *epollFd;

    return RET_OK;
}

// loop
int rpc_socket_loop(void* handle){

    int                     ret = 0;
    struct epoll_event      events[EVENT_NUM];

    int                     servFd = ((ToolRpc*)handle) ->servFd;
    int                     epollFd = ((ToolRpc*)handle) ->epollFd;

    ret = util_set_zero(events, EVENT_NUM * sizeof(struct epoll_event));
    if(RET_OK != ret) {

        return RET_ERROR;
    }

    while(1) {

        int                 eventNum;

        ret = util_epoll_wait(epollFd, events, EVENT_NUM - 1, 300, &eventNum);
        if(RET_OK != ret) {

            return ret;
        }

        for(int i; i < eventNum; ++i) {
            /*  关闭    */

            if(servFd == events[i].data.fd) {

                /*  新连接  */
            }
            /*  ..  */
        }
    }

    return RET_OK;
}

// 关闭
int rpc_socket_close(void* handle){

    if(NULL == handle) {

        return RET_ERROR;
    }

    ((ToolRpc*)handle) ->status = 1;

    return RET_OK;
}

// 删除handle
int free_rpc_handle(void** handle) {

    if(NULL == handle || NULL == *handle) {

        return RET_NULL_POINTER;
    }

    ToolRpc*        toolRpc = (ToolRpc*)*handle;

    // 释放缓冲区
    if(NULL != toolRpc->sendBuf) {

        free(toolRpc ->sendBuf);
        toolRpc ->sendBuf = NULL;
    }

    if(NULL != toolRpc->recvBuf) {

        free(toolRpc ->recvBuf);
        toolRpc ->recvBuf = NULL;
    }

    if(NULL != toolRpc) {

        free(toolRpc);
    }

    *handle = NULL;

    return RET_OK;
}
