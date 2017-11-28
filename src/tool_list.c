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

// 链表节点
struct _LinkNode {
	
	void*           							value;
	struct _LinkNode* 						next;
};

// 链表结构
struct _Link{

   LinkNode*   								head; 					// 链表头结点
	LinkNode*   								tail; 					// 链表尾节点
   unsigned long 								length; 					// 链表所含的节点数量
};


//  链表创建
int list_init(void** handle){

	if(NULL == handle) {

		ERROR("list_init input error");
		return RET_ERROR;
	}

   Link*   										list = NULL;
	
	if((list = (Link*)malloc(sizeof(Link))) == NULL) {
		
		ERROR("malloc error");
		return RET_ERROR;
   }
	
	//  初始化属性
   list ->head = NULL;
   list ->tail = NULL;
   list ->length = 0;
	*handle = list;

   return RET_OK;
}

int list_add_head(void* handle, void* value){

	if(NULL == handle || NULL == value) {

		ERROR ("list_add_node_head input error");
		return RET_ERROR;
	}

	Link* 					list = (Link*)handle;
	LinkNode* 				node = NULL;
	
	//  分配内存
	if((node = (LinkNode*)malloc(sizeof(LinkNode))) == NULL) {

		ERROR ("malloc error");
		return RET_ERROR;
   }
	
	//  保存值的指针
   node ->value = value;

   //  添加节点到链表头部
   if(0 == list ->length) {
		
		//  链表中无节点
      list ->head = node;
      list ->tail= node;
      node ->next = NULL;
	} else {
		
      node ->next = list ->head;
		list ->head = node;
   }
	
	//  更新链表节点数
	list ->length ++;

	return RET_OK;
}

int list_add_tail(void* handle, void* value){

	if(NULL == handle || NULL == value) {

		ERROR ("list_add_tail input error");
		return RET_ERROR;
	}
	
	//  创建新的节点
   LinkNode* newNode = NULL;
	Link* list = (Link*) handle;

   //  分配内存
   if((newNode = (LinkNode*)malloc(sizeof(LinkNode))) == NULL) {
		
		ERROR ("malloc error");
		return RET_ERROR;
	}

   //  赋值
   newNode ->value = value;

   //  如果链表为空
   if(0 == list ->length) {
		
      list ->tail = newNode;
      newNode ->next = NULL;
		list ->head = newNode;
	} else {
      
      list ->tail ->next = newNode;
      list ->tail = newNode;
      newNode ->next = NULL;
	}
	
	//  更新链表信息
	list ->length ++;

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
   pCur = ((Link*)(*handle)) ->head;
	pList = (Link*)(*handle);

   while(--(pList ->length)) {
		
      pNext = pCur ->next; 						//  保存下一个节点

      if(NULL != (pCur ->value)) {
			
			free(pCur ->value); 						// 释放值
		}
      free(pCur);
      pCur = pNext;
	}

   pList ->head = NULL;
   pList ->tail = NULL;
	*handle = NULL;
}



