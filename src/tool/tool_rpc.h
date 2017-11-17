/*************************************************************************
> FileName: tool_rpc.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:00 PM DST
 ************************************************************************/

#ifndef _TOOL_RPC_H
#define _TOOL_RPC_H
#include "tool_rpc_util.h"

#define     EVENT_NUM   1000


int rpc_socket_init(unsigned short port, int* servFd, int* epollFd);

int rpc_socket_loop(int servFd, int epollFd);





#endif
