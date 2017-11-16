/*************************************************************************
> FileName: ./tool_rpc.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 16 Nov 2017 04:53:10 PM DST
 ************************************************************************/

#include "tool_rpc.h"
#include "tool_ret.h"
#include <string.h>
#include <netinet/in.h>

int rpc_get_serv_fd() {

    int ret = 0;
    int servFd = 0;
    struct sockaddr_in sin;

    ret = util_epoll_create(EPOLL_EVENTS, &gepFd);
    if(RET_OK != ret) {
        
        return ret;
    }

    ret = util_socket(AF_INET, SOCK_STREAM, 0, &servFd);
    if(RET_OK != ret) {

        return ret;
    }

    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERV_PORT);
    
    ret = util_bind(servFd, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));
    if(RET_OK != ret) {

        return ret;
    }

    listen(servFd, 128);





    return RET_OK;
}

