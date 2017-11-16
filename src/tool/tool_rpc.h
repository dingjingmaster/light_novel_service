/*************************************************************************
> FileName: tool_rpc.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:00 PM DST
 ************************************************************************/

#ifndef _TOOL_RPC_H
#define _TOOL_RPC_H
#include "tool_util.h"

/*  待修改  */
#define SERV_PORT       10000
#define EPOLL_EVENTS    128

static int gepFd;

int rpc_get_serv_fd();


#endif
