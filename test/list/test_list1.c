/*************************************************************************
> FileName: test_list.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 04 Dec 2017 06:06:43 PM DST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "tool_list.h"
#include "tool_log.h"

void test01(void) {

	void* 						listHandle = NULL;

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

void test03(void) {

	void* 						listHandle = NULL;
	void* 						node = NULL;
	void* 						value = NULL;


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

	INFO("弹出dd前");
	// 此时链表为 bb -> aa -> cc -> dd
	list_pop_by_value(listHandle,"dd", &node);
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


void test04(void) {

	void* 						listHandle = NULL;
	void* 						node = NULL;
	void* 						value = NULL;


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

	INFO("弹出bb前");
	// 此时链表为 bb -> aa -> cc -> dd
	list_pop_by_value(listHandle,"bb", &node);
	INFO("弹出bb后");

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
				
				// 初始化日志
				log_init("./log_conf/log.conf");
				INFO("test01 --- 头插、尾插、弹出头部元素、获取节点值");
				test01();
				INFO("test02 --- 根据值弹出节点");
				test02();
				INFO("test03 --- 根据值弹出末尾节点");
				test03();
				INFO("test04 --- 根据值弹出头节点");
				test04();

				return 0;
}

