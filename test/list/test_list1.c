/*************************************************************************
> FileName: test_list.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 04 Dec 2017 06:06:43 PM DST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "../../src/tool_list.h"
#include "../../src/tool_log.h"

void test01(void) {

	void* 						listHandle = NULL;

   // 初始化日志
   log_init("./log_conf/log.conf");
	INFO("LOG 初始化");


	// 初始化链表
	list_init(&listHandle);

	// 链表头插
	list_add_head(listHandle, "aa");
	INFO("插入aa");
	list_add_head(listHandle, "bb");
	INFO("插入bb");

	// 链表尾插
	list_add_tail(listHandle, "cc");
	INFO("插入cc");
	list_add_tail(listHandle, "dd");
	INFO("插入dd");

	// 此时链表为 bb -> aa -> cc -> dd
	for (int i = 0; i < 4; ++i) {

		void* 					node = NULL;
		void* 					value = NULL;
		// 获取头部元素
		list_pop_head(listHandle, &node);

		// 获取头部值
		list_get_value(node, &value);
		INFO("打印头部元素值: %s", (char*)value);
	}

	list_destroy(&listHandle);
}

void test02(void) {

	void* 						listHandle = NULL;
	void* 						node = NULL;
	void* 						value = NULL;

   // 初始化日志
   log_init("./log_conf/log.conf");
	INFO("LOG 初始化");


	// 初始化链表
	list_init(&listHandle);

	// 链表头插
	list_add_head(listHandle, "aa");
	INFO("插入aa");
	list_add_head(listHandle, "bb");
	INFO("插入bb");

	// 链表尾插
	list_add_tail(listHandle, "cc");
	INFO("插入cc");
	list_add_tail(listHandle, "dd");
	INFO("插入dd");

	INFO("弹出cc前");
	// 此时链表为 bb -> aa -> cc -> dd
	list_pop_by_value(listHandle,"cc", &node);
	INFO("弹出cc后");

	for (int i = 0; i < 3; ++i) {

		// 获取头部元素
		list_pop_head(listHandle, &node);

		// 获取头部值
		list_get_value(node, &value);
		INFO("打印头部元素值: %s", (char*)value);
	}

	list_destroy(&listHandle);
}

int main(void) {

	INFO("test01 --- 头插、尾插、弹出头部元素、获取节点值");
	test01();
	INFO("test02 --- 根据值弹出节点");
	test02();
	return 0;
}

