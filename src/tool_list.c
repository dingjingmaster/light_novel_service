/*************************************************************************
> FileName: tool_list.c
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 27 Nov 2017 04:35:45 PM DST
 ************************************************************************/
#include "tool_list.h"

#include "tool_ret.h"
#include "tool_log.h"
#include "tool_util.h"

struct _LinkNode {
	
	void*           							value;
	struct _LinkNode* 						next;
};

struct _Link{

   LinkNode*   								head; 					// 链表头结点
	LinkNode*   								tail; 					// 链表尾节点
   unsigned long 								length; 					// 链表所含的节点数量
};


int list_init(void** handle){

	if(NULL == handle) {

		ERROR("list_init input error");
		return RET_ERROR;
	}

	int 											ret = 0;
   Link*   										list = NULL;
	
	ret = util_malloc((void**)&list, sizeof(Link));
	if(RET_OK != ret) {
		
		ERROR("malloc error");
		return RET_ERROR;
   }
	
   list ->head = NULL;
   list ->tail = NULL;
   list ->length = 0;
	*handle = list;

   return RET_OK;
}

// 添加头结点
int list_add_head(void* handle, void* value){

	if(NULL == handle || NULL == value) {

		ERROR ("list_add_node_head input error");
		return RET_ERROR;
	}

	int 											ret = 0;
	Link* 										list = (Link*)handle;
	LinkNode* 									node = NULL;
	
	ret = util_malloc((void**)&node, sizeof(LinkNode));
	if(RET_OK != ret) {

		ERROR ("malloc error");
		return RET_ERROR;
   }
	
   node ->value = value;

   if(0 == list ->length) {
		
      list ->head = node;
      list ->tail= node;
      node ->next = NULL;
	} else {
		
      node ->next = list ->head;
		list ->head = node;
   }
	
	++ (list ->length);

	return RET_OK;
}

int list_add_tail(void* handle, void* value){

	if(NULL == handle || NULL == value) {

		ERROR ("list_add_tail input error");
		return RET_ERROR;
	}
	
	int 											ret = 0;
   LinkNode* 									newNode = NULL;
	Link* 										list = (Link*) handle;

	ret = util_malloc((void**)&newNode, sizeof(LinkNode));
   if(RET_OK != ret) {
		
		ERROR ("malloc error");
		return RET_ERROR;
	}

   newNode ->value = value;

   if(0 == list ->length) {
		
      list ->tail = newNode;
      newNode ->next = NULL;
		list ->head = newNode;
	} else {
      
      list ->tail ->next = newNode;
      list ->tail = newNode;
      newNode ->next = NULL;
	}
	
	++(list ->length);

   return RET_OK;
}

int list_pop_head(void* handle, void** node) {

	if(NULL == handle || NULL == node) {

		return RET_ERROR;
	}

	Link* 										link = NULL;
	LinkNode* 									popNode = NULL;

	link = (Link*)handle;

	if(link ->length >= 1) {

		popNode = link ->head;
	}

	link ->head = (link ->head) ->next;

	*node = popNode;
	-- (link ->length);

	return RET_OK;
}

int list_pop_by_value(void* handle, void* value, void** node) {

	if (NULL == value || NULL == handle || NULL == node || NULL == *node) {

		ERROR ("list_pop_by_value input error"); 

		return RET_ERROR;
	}

	int 											length = 0;
	Link* 										link = NULL;
	LinkNode* 									pPre = NULL;
	LinkNode* 									pCur = NULL;

	link = (Link*)handle;
	length = link -> length;

	if(length < 1) {

		ERROR ("list_pop_by_value list is empty"); 
		return RET_EMPTY_LIST;
	}

	pCur = link ->head;
	for (int i = 0; i <= length; ++ i) {

		if (value == pCur ->value) {

			*node = pCur;

			break;
		}

		pPre = pCur;
		pCur = pCur ->next;
	}

	// 去除节点
	pPre ->next = pCur ->next;
	pCur ->next = NULL;
	-- (link ->length);

	return RET_OK;
}

int list_insert_node_tail(void* handle, void* node) {

	if (NULL == handle || NULL == node) {

		ERROR ("list_insert_node_tail input error"); 

		return RET_NULL_POINTER;
	}

	Link* 										link = NULL;
	LinkNode* 									pTail = NULL;

	link = (Link*)handle;
	pTail = link ->tail;

	pTail -> next = node;
	++ (link ->length);

	return RET_OK;
}

/* 链表获取值 */
int list_get_value(void* node, void** value) {
	if(NULL == node || NULL == value) {

		ERROR ("list_get_value input error");
		return RET_NULL_POINTER;
	}

	LinkNode* 									pNode = NULL;

	pNode = (LinkNode*)node;

	*value = pNode ->value;

	return RET_OK;
}


void list_destroy(void** handle) {
	
	if(NULL == *handle) {
		
		ERROR ("list_free already free");
		return;
	}
	
	Link* 		pList = NULL;
	LinkNode* 	pCur = NULL;
	LinkNode* 	pNext = NULL;
	
	//  指向头指针
	pList = (Link*)(*handle);
   pCur = pList ->head;

   for(;pList->length > 0;--(pList ->length)) {
		
      pNext = pCur ->next; 						//  保存下一个节点

      if(NULL != pCur) {
			
			free(pCur); 								// 释放值
		}
      pCur = pNext;
	}

   pList ->head = NULL;
   pList ->tail = NULL;
	free(pList);
	*handle = NULL;
}



