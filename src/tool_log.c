/*************************************************************************
> FileName: tool_log.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Wed 22 Nov 2017 06:59:38 PM DST
 ************************************************************************/

#include "tool_log.h"
#include "tool_ret.h"
#include <stdio.h>

void log_init(char* confPath) {
    if(NULL == confPath) {
		 
		 ERROR("log_init error: %s", confPath);
		 return ;
    }

    int                 rc = 0;

    rc = dzlog_init(confPath, "");
    if(rc) {

		 ERROR("dzlog_init error ret: %d", rc);
		 return ;
    }

}

void log_destory(){

    zlog_fini();
}


