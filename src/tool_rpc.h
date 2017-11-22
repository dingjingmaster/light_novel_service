/*************************************************************************
> FileName: tool_rpc.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:00 PM DST
 ************************************************************************/

#ifndef _TOOL_RPC_H
#define _TOOL_RPC_H
#include "tool_socket.h"

#define     EVENT_NUM       1000
#define     RECV_BUFFER     40960
#define     SEND_BUFFER     10240

int get_rpc_handle(unsigned short port, void** handle/* out */);

int rpc_socket_init(void* handle);

int rpc_socket_loop(void* handle);

int rpc_socket_close(void* handle);

int free_rpc_handle(void** handle);





#endif
