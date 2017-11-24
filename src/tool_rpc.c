/*************************************************************************
> FileName: tool_rpc.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:10 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include "tool_log.h"
#include "tool_util.h"
#include "tool_socket.h"
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

typedef void(*event_call_back)(int fd, int events, void* arg);          // 事件发生的回调函数
void event_read_cb(int fd, int events, void* arg);
void event_write_cb(int fd, int events, void* arg);

typedef struct _MyEvent MyEvent;
typedef struct _ToolRpc ToolRpc;

struct _MyEvent {
    int                 fd;                                             // 文件描述符
    int                 events;
    int                 status;                                         // 0 不在epoll监听队列, 1在epoll监听队列
    int                 len;                                            // 接受数据长度
    int                 offset;                                         // 偏移
    char*               buf;                                            // 接收缓冲区
    void*               arg;
    event_call_back     ev_cb;
    long                lastActivity;                                   // 上次活跃时间
};

struct _ToolRpc {
    int                 servFd;                                         // 服务端文件描述符
    int                 status;                                         // 状态(0正常运行, 1关闭)
    int                 evenLen;                                        // 事件链表的长度
    unsigned short      port;                                           // 端口
};

MyEvent             myEventG[MAX_EVENT + 1];                            // 事件
int                 epollFdG;                                           // epoll文件描述符


// 设置事件操作
int event_set(MyEvent* ev, int fd, event_call_back cb, void* arg){
    if(NULL == ev) {

        ERROR("input error");
        return RET_NULL_POINTER;
    }

    int             ret = 0;

    ev ->fd = fd;
    ev ->ev_cb = cb;
    ev ->arg = arg;
    ev ->status = 0;
    ev ->offset = 0;
    ev ->len = 0;
    ev ->lastActivity = time(NULL);
    ret = util_malloc((void**)&(ev ->buf), RECV_BUF_LEN);
    if(RET_OK != ret) {
        /* 错误 */

        return RET_ERROR;
    }

    return RET_OK;
}

// 添加事件操作
int event_add(int epollFd, int events, MyEvent* ev) {
    if(NULL == ev) {

        return RET_NULL_POINTER;
    }

    int                 op = 0;
    int                 ret = 0;
    struct epoll_event  epv = {0, {0}};

    epv.data.ptr = ev;
    epv.events = ev ->events = events;
    if(1 == ev ->status) {
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        ev ->status = 1;
    }
    ret = util_epoll_ctl(epollFd, op, ev ->fd, &epv);
    if(RET_OK != ret){
        /* 错误 */
        return RET_ERROR;
    }

    return RET_OK;
}

// 删除事件
int event_del(int epollFd, MyEvent* ev){
    if(NULL == ev) {

        return RET_NULL_POINTER;
    }

    int                 ret = 0;
    struct epoll_event  epv = {0, {0}};

    if(1 != ev ->status)
        return RET_OK;

    epv.data.ptr = ev;
    ev ->status = 0;
    ret = util_epoll_ctl(epollFd, EPOLL_CTL_DEL, ev ->fd, &epv);
    if(RET_OK != ret){
        /* 错误 */
        return RET_ERROR;
    }

    return RET_OK;
}

void event_write_cb(int fd, int events, void* arg) {
    
    int                 len = 0;
    MyEvent*            ev = (MyEvent*)arg;

    len = write(fd, ev ->buf + ev ->offset, ev ->len);
    if(len > 0) {
        //
        ev ->offset += len;
        if(ev ->offset == ev ->len) {
            event_del(epollFdG, ev);
            event_set(ev, fd, event_read_cb, ev);
            event_add(epollFdG, EPOLLIN, ev);
        }
    } else {
        close (ev ->fd);
        event_del(epollFdG, ev);
    }
}

void event_read_cb(int fd, int events, void* arg) {

    int                 ret = 0;
    int                 len = 0;
    MyEvent*            ev = (MyEvent*)arg;

    len = read(fd, ev ->buf + ev->len, RECV_BUF_LEN - 1 - ev->len);
    ret = event_del(epollFdG, ev);
    if(RET_OK != ret) {

        ERROR("event del error");
    }
    if (len > 0) {
        ev ->len += len;
        ev ->buf[len] = '\0';
        // 没有接受完整的信息
        event_set(ev, fd, event_write_cb, ev);
        event_add(epollFdG, EPOLLOUT, ev);
    } else if (len == 0) {
        close (ev ->fd);
        // 正常关闭
    } else {
        close (ev->fd);

        ERROR("read info error");
    }
}


// accept 回调实现
void event_accept_cb(int fd, int events, void* arg) {

    int                 i = 0;
    int                 nfd;
    int                 ret;
    socklen_t           len = sizeof(struct sockaddr_in);
    struct sockaddr_in  cliAddr;                                        // 客户端地址

    ret = util_accept(fd, (struct sockaddr*)&cliAddr, &len, &nfd);
    if(RET_OK != ret) {

        ERROR("server accept error");
        return;
    }

    do {
        for(i = 0; i < MAX_EVENT; ++i) {
            if(0 == myEventG[i].status) {                               // 该 event 不在event队列中(这是server socket)

                break;
            }
        }

        if(MAX_EVENT == i) {                                            // 没有找到新连接
            break;
        }

        //
        ret = util_set_noblocking(nfd);
        if(RET_OK != ret) {

            ERROR("server set no blocking error");
        }
    }while(0);
}


/*  各个接口实现    */
int get_rpc_handle(unsigned short port, void** handle){
    if(NULL == handle || port <= 0){

        ERROR("intput value error");
        return RET_NULL_POINTER;
    }

    ToolRpc*            toolRpc = NULL;
    MyEvent*            myEvent = NULL;


    // 分配内存
    toolRpc = (ToolRpc*) malloc (sizeof(ToolRpc));
    if(NULL == toolRpc) {

        ERROR("rpc handll malloc error");
    }

    // 赋值
    toolRpc ->port = port;
    toolRpc ->status = 0;

    *handle = toolRpc;

    return RET_OK;
}

// 初始化
int rpc_socket_init(void* handle) {

    if(NULL == handle) {

        ERROR("input value error");
        return RET_NULL_POINTER;
    }

    int                     ret = 0;
    int                     servFd;
    struct sockaddr_in      servAddr;
    struct epoll_event      event;

    int port = ((ToolRpc*)handle) ->port;

    ret = util_socket(AF_INET, SOCK_STREAM, 0, &servFd);
    if(RET_OK != ret) {

        ERROR("get socket error");
        return ret;
    }

    ret = util_set_zero(&servAddr, sizeof(struct sockaddr_in));
    if(RET_OK != ret) {

        ERROR("memory init error");
        return ret;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    ret = util_bind(servFd, (struct sockaddr*)&servAddr, sizeof(servAddr));
    if(RET_OK != ret) {

        ERROR("bind error");
        return ret;
    }

    ret = util_listen(servFd, 128);
    if(RET_OK != ret) {

        ERROR("listen error");
        return ret;
    }

    ret = util_epoll_create(MAX_EVENT + 1, &epollFdG);
    if(RET_OK != ret) {

        ERROR("epoll create error");
        return ret;
    }

    event.data.fd = servFd;
    event.events = EPOLLIN;
    ret = util_epoll_ctl(epollFdG, EPOLL_CTL_ADD, servFd, &event);
    if(RET_OK != ret) {

        return ret;
    }

    // 保存
    ((ToolRpc*)handle) ->servFd = servFd;

    return RET_OK;
}


// loop
int rpc_socket_loop(void* handle){

    if(NULL == handle) {

        return RET_NULL_POINTER;
    }

    int                     ret = 0;
    int                     checkPos = 0;
    int                     eventNum;
    long                    now = 0;
    long                    dura = 0;
    struct epoll_event      eventOut[MAX_EVENT];                    // 返回的事件

    int                     servFd = ((ToolRpc*)handle) ->servFd;

    ret = util_set_zero(eventOut, MAX_EVENT * sizeof(struct epoll_event));
    if(RET_OK != ret) {

        return RET_ERROR;
    }

    while(1) {
    printf("%s\n", "loop begin");

        eventNum = 0;
        now = time(NULL);

        /*  每隔一段时间检查一下事件是否超出    */
        for(int i = 0; i < 100; ++i, ++ checkPos) {
            if(MAX_EVENT == checkPos) {
                checkPos = 0;
            }
            if(myEventG[checkPos].status != 1) {
                continue;
            }

            dura = now - myEventG[checkPos].lastActivity;
            if(60 <= dura) {
                close(myEventG[checkPos].fd);
                event_del(epollFdG, &myEventG[checkPos]);
            }
        }

        // 等待事件发生
        ret = util_epoll_wait(epollFdG, eventOut, MAX_EVENT - 1, 300, &eventNum);
        if(RET_OK != ret) {

            /* error 但不能退出 */
            ERROR("get wrong event back error");
        }

        for(int i = 0; i < eventNum; ++i) {
            MyEvent* ev = (MyEvent*)eventOut[i].data.ptr;

            if((eventOut[i].events & EPOLLIN) && (ev ->events & EPOLLIN)) {     // 读事件

            }

            if((eventOut[i].events & EPOLLOUT) && (ev ->events & EPOLLOUT)) {   // 写事件

            }
        }
    }

    // 释放资源

    return RET_OK;
}

// 关闭
int rpc_socket_close(void* handle){

    if(NULL == handle) {

        ERROR("handle no pointer error");
        return RET_ERROR;
    }

    ((ToolRpc*)handle) ->status = 1;

    return RET_OK;
}

// 删除handle
int free_rpc_handle(void** handle) {

    if(NULL == handle || NULL == *handle) {

        ERROR("handle no pointer error");
        return RET_NULL_POINTER;
    }

    ToolRpc*        toolRpc = (ToolRpc*)*handle;

    // 释放缓冲区
    /*if(NULL != toolRpc->recvBuf) {

        free(toolRpc ->recvBuf);
        toolRpc ->recvBuf = NULL;
    }
*/
    if(NULL != toolRpc) {

        free(toolRpc);
    }

    *handle = NULL;

    return RET_OK;
}




