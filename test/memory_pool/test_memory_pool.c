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
				void*										mem1 = NULL;
				void*										mem2 = NULL;
				void*										mem3 = NULL;
				
				DEBUG("memory_init");
				memory_init(&handle, 1000, 2);
				DEBUG("handle: %p", handle);
				memory_get(handle, &mem1);
				DEBUG("get: %p", mem1);
				memory_get(handle, &mem2);
				DEBUG("get: %p", mem2);

				memory_get(handle, &mem3);
				DEBUG("get: %p", mem3);


				DEBUG("put b: %p", mem1);
				memory_put(handle, &mem1);
				DEBUG("put a: %p", mem1);

				memory_get(handle, &mem1);
				DEBUG("get: %p", mem1);

				memory_get(handle, &mem3);
				DEBUG("get: %p", mem3);

				DEBUG("put: %p", mem1);
				memory_put(handle, &mem1);

				DEBUG("put: %p", mem2);
				memory_put(handle, &mem2);

				DEBUG("put: %p", mem3);
				memory_put(handle, &mem3);

				memory_get(handle, &mem2);
				DEBUG("get: %p", mem2);

				memory_get(handle, &mem3);
				DEBUG("get: %p", mem3);

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
				//INFO("test01 --- 内存池初始化，获取内存，放回内存，销毁内存池");
				test01();
				//INFO("test02 --- 根据值弹出节点");
				//test02();
				//INFO("test03 --- 根据值弹出末尾节点");
				//test03();
				///INFO("test04 --- 根据值弹出头节点");
				//test04();

				return 0;
}

