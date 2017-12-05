/*************************************************************************
> FileName: test_list.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 04 Dec 2017 06:06:43 PM DST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "tool_memory_pool.h"
#include "tool_log.h"

void test01(void) {

	void*										handle = NULL;
	void*										mem = NULL;

	DEBUG("memory_init");
	memory_init(&handle, 1000, 20);
	DEBUG("%p", handle);
	memory_get(handle, &mem);
	DEBUG("%p", mem);
	memory_destory(&handle);

}

void test02(void) {

}

void test03(void) {

}


void test04(void) {
}



int main(void) {
				
				// 初始化日志
				log_init("./log_conf/log.conf");
				//INFO("test01 --- 头插、尾插、弹出头部元素、获取节点值");
				test01();
				//INFO("test02 --- 根据值弹出节点");
				//test02();
				//INFO("test03 --- 根据值弹出末尾节点");
				//test03();
				///INFO("test04 --- 根据值弹出头节点");
				//test04();

				return 0;
}

