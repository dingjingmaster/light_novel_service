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

typedef struct _SocketEvent SocketEvent;
typedef void(*socket_event_call_back)(int fd, int events, void* arg);

struct _SocketEvent {

    int                     fd;
    int                     events;
    int                     status;             // 1 代表在 epoll 等待列表中, 0 不在
    int                     len;
    int                     s_offset;
    void*                   arg;
    socket_event_call_back  ev_cb;
    long                    last_active;        // 上次活跃时间戳
    char                    buf[128];           // 待修改
};


// set event
int rpc_set_event(SocketEvent* ev, int fd, socket_event_call_back ev_cb, void* arg);

// add event
int rpc_add_event(int handle, int events, SocketEvent* ev);

// del event
int rpc_del_event(int handle, SocketEvent* ev);

// init socket handle
int rpc_socket_init(int* epHandle);


#endif
