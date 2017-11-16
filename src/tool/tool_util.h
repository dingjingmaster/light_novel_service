/*************************************************************************
> FileName: tool_util.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 05:08:48 PM DST
 ************************************************************************/

#ifndef _TOOL_UTIL_H
#define _TOOL_UTIL_H
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

// get socket
int util_socket(int domain, int type, int protocol, int* servFd);

// bind
int util_bind(int servFd, const struct sockaddr* addr, socklen_t addrlen);

// listen
int util_listen(int servFd, int backlog);

// close socket
int util_fd_close(int* fd);

// epoll create
int util_epoll_create(int size, int* epFd);

// epoll_ctl
int util_epoll_ctl(int epFd, int op, int fd, struct epoll_event* event);

// epoll wait
int util_epoll_wait(int epFd, struct epoll_event* event, int maxevents, int timeout, int* readyNum);

#endif
