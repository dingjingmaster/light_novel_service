/*************************************************************************
> FileName: tool_list.h
> Author  : DingJing
> Mail    : dingjing@live.cn
> Created Time: Mon 27 Nov 2017 04:34:42 PM DST
 ************************************************************************/

#ifndef _TOOL_LIST_H
#define _TOOL_LIST_H

#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _LinkNode LinkNode;
typedef struct _Link Link;


/*  创建新的链表  */
int list_init(void** handle);

/*  链表头插    */
int list_add_head(void* handle, void* value);

/*  链表尾插    */
int list_add_tail(void* handle, void* value);

/*  弹出链表头部元素 */
int list_pop_head(void* handle, void** node);

/*  根据值弹出链元素 */
int list_pop_by_value(void* handle, void* value, void** node);

/*  链表在尾部插入节点 */
int list_insert_node_tail(void* handle, void* node);

/*  链表获取值 	*/
int list_get_value(void* node, void** value);

/*  释放链表内存  */
void list_destroy(void** handle);

#ifdef __cplusplus
}
#endif
#endif // CLIB_LIST_H


