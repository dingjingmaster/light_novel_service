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

// get socket
int socket_init(int domain, int type, int protocol, int* servFd);

// bind
int util_bind(int servFd, const struct sockaddr* addr, socklen_t addrlen);

// listen
int util_listen(int servFd, int backlog);

// close socket
int socket_close(int* fd);


#endif
