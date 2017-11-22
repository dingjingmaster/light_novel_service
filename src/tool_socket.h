/*************************************************************************
> FileName: tool_socket.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 05:08:48 PM DST
 ************************************************************************/

#ifndef _TOOL_SOCKET_H
#define _TOOL_SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>

/**
 *  domain      连接格式
 *  type        协议
 *  protocol    配置默认0
 *  servFd      返回的服务端socket文件描述符
 */
int util_socket(int domain, int type, int protocol, int* servFd);

/**
 *  servFd      要注册ip地址的文件描述符
 *  addr        地址结构体
 *  addrlen     地址长度
 */
int util_bind(int servFd, const struct sockaddr* addr, socklen_t addrlen);

/**
 *  servFd      标记该文件描述符监听客户端请求
 *  backlog     同一时间允许连接的客户端请求个数(队列长度)
 */
int util_listen(int servFd, int backlog);

/**
 *  sockFd      服务端被监听文件描述符
 *  addr        客户端地址信息
 *  addrlen     地址信息长度
 *  fdNum       客户端请求数量
 */
int util_accept(int sockFd, struct sockaddr* addr, socklen_t* addrlen, int* fdNum);

/**
 *  fd          要关闭的文件描述符
 */
int util_fd_close(int* fd);

/**
 *  size        代理文件描述符数量
 *  epFd        代理文件描述符
 */
int util_epoll_create(int size, int* epFd);

/**
 *  epFd        代理文件描述符
 *  op          对代理文件描述符的操作
 *  fd          要操作的文件描述符
 *  event       代理文件描述符要监听的fd事件
 */
int util_epoll_ctl(int epFd, int op, int fd, struct epoll_event* event);

/**
 *  epFd        代理文件描述符
 *  event       被监听文件描述符的事件
 *  maxevents   达到该值返回
 *  timeout     等待事件, 时间到返回, -1永久等待
 *  readyNum    请求IO的文件描述符数量
 */
int util_epoll_wait(int epFd, struct epoll_event* event, int maxevents, int timeout, int* readyNum);

/**
 *  ptr         内存起始地址
 *  len         内存长度
 */
int util_set_zero(void* ptr, int len);

#endif
