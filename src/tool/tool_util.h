/*************************************************************************
> FileName: tool_util.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 05:08:48 PM DST
 ************************************************************************/

#ifndef _TOOL_UTIL_H
#define _TOOL_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// get socket
int socket_init(int domain, int type, int protocol);

// close socket
int socket_close(int* fd);


#endif
