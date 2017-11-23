/*************************************************************************
> FileName: main.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Thu 23 Nov 2017 04:37:45 PM DST
 ************************************************************************/

#include "main_run.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

    server_main(argc, argv);

    puts("服务关闭成功...");

    return 0;
}

