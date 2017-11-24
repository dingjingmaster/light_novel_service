/*************************************************************************
> FileName: tool_socket.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 05:21:43 PM DST
 ************************************************************************/

#include "tool_ret.h"
#include "tool_log.h"
#include "tool_socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// get socket
int util_socket(int domain, int type, int protocol, int* servFd) {

    if(NULL == servFd) {

        ERROR("util_socket input error");
        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = socket(domain, type, protocol);
    if(-1 == ret) {

        ERROR("socket return error");
        return RET_ERROR;
    }

    *servFd = ret;

    return RET_OK;
}

// bind
int util_bind(int servFd, const struct sockaddr* addr, socklen_t addrlen) {

    if(NULL == addr) {

        ERROR("util_bind input error");
        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = bind(servFd, addr, addrlen);
    if(-1 == ret) {
    
        ERROR("bind return error");
        return RET_ERROR;
    }

    return RET_OK;
}

// listen
int util_listen(int servFd, int backlog) {

    int ret = 0;

    ret = listen(servFd, backlog);
    if(-1 == ret) {
    
        ERROR("listen return error");
        return RET_ERROR;
    }

    return RET_OK;
}

// accept
int util_accept(int sockFd, struct sockaddr* addr, socklen_t* addrlen, int* fdNum) {

    if(NULL == addr || NULL == addrlen || NULL == fdNum) {

        ERROR("util_accept intput error");
        return RET_NULL_POINTER;
    }

    int         ret = 0;

    ret = accept(sockFd, addr, addrlen);
    if(RET_OK != ret) {

        ERROR("accept return error");
        return RET_ERROR;
    }

    *fdNum = ret;

    return RET_OK;
}


// close
int util_fd_close(int* fd) {

    if(NULL == fd) {

        ERROR("util_fd_close intput error");
        return RET_NULL_POINTER;
    }

    int ret = 0;
    
    ret = close(*fd);
    if(-1 == ret) {

        ERROR("close return error");
        return RET_FD_CLOSED;
    }

    *fd = RET_FD_CLOSED;

    return RET_OK;
}

// epoll create
int util_epoll_create(int size, int* epFd) {

    if(NULL == epFd) {

        ERROR("util_epoll_create input error");
        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = epoll_create(size);
    if(-1 == ret) {
    
        ERROR("epoll_create return error");
        return RET_ERROR;
    }

    *epFd = ret;

    return RET_OK;
}

// epoll_ctl
int util_epoll_ctl(int epFd, int op, int fd, struct epoll_event* event) {

    if(NULL == event) {

        ERROR("util_epoll_ctl input error");
        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = epoll_ctl(epFd, op, fd, event);
    if(-1 == ret) {

        ERROR("epoll_ctl return error");
        return RET_ERROR;
    }

    return RET_OK;
}

// epoll wait
int util_epoll_wait(int epFd, struct epoll_event* event, int maxevents, int timeout, int* readyNum) {

    if(NULL == event || NULL == readyNum) {
    
        ERROR("util_epoll_wait input error");
        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = epoll_wait(epFd, event, maxevents, timeout);
    if(-1 == ret) {

        ERROR("epoll_wait return error");
        return RET_ERROR;
    }

    *readyNum = ret;

    return RET_OK;
}

