/*************************************************************************
> FileName: tool_rpc.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:10 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include "tool_rpc_util.h"
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

int rpc_socket_init(unsigned short port, int* servFd, int* epollFd) {

    if(NULL == servFd || NULL == epollFd) {

        return RET_NULL_POINTER;
    }

    int                     ret = 0;
    struct sockaddr_in      servAddr;
    struct epoll_event      event;

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

    return RET_OK;
}

// loop
int rpc_socket_loop(int servFd, int epollFd) {

    int                     ret = 0;
    struct epoll_event      events[EVENT_NUM];

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
