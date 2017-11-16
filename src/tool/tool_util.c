/*************************************************************************
> FileName: ./tool_util.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 05:21:43 PM DST
 ************************************************************************/

#include "tool_ret.h"
#include "tool_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// get socket
int util_socket(int domain, int type, int protocol, int* servFd) {

    if(NULL == servFd) {

        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = socket(domain, type, protocol);
    if(-1 == ret) {

        return RET_ERROR;
    }

    *servFd = ret;

    return RET_OK;
}

// bind
int util_bind(int servFd, const struct sockaddr* addr, socklen_t addrlen) {

    if(NULL == addr) {

        return RET_NULL_POINTER;
    }

    int ret = 0;

    ret = bind(servFd, addr, addrlen);
    if(-1 == ret) {
    
        return RET_ERROR;
    }

    return RET_OK;
}

// listen
int util_listen(int servFd, int backlog) {

    int ret = 0;

    ret = listen(servFd, backlog);
    if(-1 == ret) {
    
        return RET_ERROR;
    }

    return RET_OK;
}

// close
int socket_close(int* fd) {

    if(NULL == fd) {
        return RET_NULL_POINTER;
    }

    int ret = 0;
    
    ret = close(*fd);
    if(-1 == ret) {
    
        return RET_ERROR;
    }

    return RET_OK;
}

