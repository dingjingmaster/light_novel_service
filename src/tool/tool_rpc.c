/*************************************************************************
> FileName: ./tool_rpc.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:10 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

int rpc_set_event(SocketEvent* ev, int fd, socket_event_call_back ev_cb, void* arg) {

    if(NULL == ev || NULL == arg) {

        return RET_NULL_POINTER;
    }

    ev->fd = fd;
    ev->ev_cb = ev_cb;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 0;
    memset(ev->buf, 0, sizeof(ev->buf));
    ev->s_offset = 0;
    ev->len = 0;
    ev->last_active = time(NULL);

    return RET_OK;
}

// add event
int rpc_add_event(int handle, int events, SocketEvent* ev) {

    if(NULL == ev) {

        return RET_OK;
    }

    int                 ret = 0;
    struct epoll_event  epv = {0, {0}};

    epv.data.ptr = ev;
    epv.events = ev->events = events;

    ret = util_epoll_ctl(handle, EPOLL_CTL_ADD, ev->fd, &epv);
    if(RET_OK != ret) {

        return ret;
    }


    return RET_OK;
}

// rpc delete event
int rpc_del_event(int handle, SocketEvent* ev) {

    if(NULL == ev) {

        return RET_NULL_POINTER;
    }

    int                 ret = 0;
    struct epoll_event  evp = {0, {0}};

    if (1 != ev->status) {

        return RET_WRONG_STATU;
    }

    evp.data.ptr = ev;
    ev->status = 0;

    ret = util_epoll_ctl(handle, EPOLL_CTL_DEL, ev->fd, &evp);
    if(RET_OK != ret){

        return RET_ERROR;
    }

    return RET_OK;
}


// rpc socket init
int rpc_socket_init (int* epHandle) {

    int ret = 0;
    int servFd = 0;
    struct sockaddr_in sin;
    struct epoll_event ev;                                              // 用于处理事件

    ret = util_epoll_create(EPOLL_EVENTS, epHandle);
    if(RET_OK != ret) {
        
        return ret;
    }

    ret = util_socket(AF_INET, SOCK_STREAM, 0, &servFd);
    if(RET_OK != ret) {

        return ret;
    }

    fcntl(servFd, F_SETFL, O_NONBLOCK);

    ev.data.fd = servFd;                                                // add servFd to listen
    ev.events = EPOLLIN;                                                // listen connection

    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERV_PORT);
    
    ret = util_bind(servFd, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
    if(RET_OK != ret) {

        return ret;
    }

    listen(servFd, 128);

    return RET_OK;
}

// accept
int rpc_socket_accept(int fd, int events, void* arg) {

    if(NULL == arg) {

        return RET_NULL_POINTER;
    }

    int                     nfd;
    struct sockaddr_in      cliAddr;



    return RET_OK;
}

