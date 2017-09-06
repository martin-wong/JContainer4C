#ifndef C_LINKEDLIST_H
#define C_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "user_define.h"


typedef struct clinkedlistnode {

	void * elem; //指向真正的用户自定义的元素
	struct clinkedlistnode * next; //下一个节点
	struct clinkedlistnode * prev; //前一个节点

} cLinkedListNode;

typedef struct clinkedlist { //linkedlist抽象数据结构

	cMetadata * metaData; //指向元数据结构体
	cLinkedListNode *  head; //指向头节点（即第一个有效节点）
	cLinkedListNode *  tail; //指向尾节点
	uint32_t numberOfElem ; //链表总元素个数
	int16_t(*addLast)(struct clinkedlist * list, void * elem);
	int16_t(*addFirst)(struct clinkedlist * list, void * elem);
 	uint32_t(*size)(struct clinkedlist * list); 
	int32_t(*indexOf)(struct clinkedlist * list, void * Elem);
	int32_t(*remove)(struct clinkedlist * list, uint32_t index);
	int32_t(*removeElem)(struct clinkedlist * list, void * Elem);
	void (*clear)(struct clinkedlist * list);
	void * (*get)(struct clinkedlist * list, uint32_t index);
	void * (*set)(struct clinkedlist * list, uint32_t index, void * newElem);
	void (*destory)(struct clinkedlist * list);
	

} cLinkedList;


/**
* 创建cLinkedList数据结构.
* @param c_equals       自定义的相等判断函数指针.
* @param c_compareTo    自定义的比较大小函数指针.
* @param c_hashCode     自定义的生成hashcode的函数指针.
* @param c_copy         自定义的拷贝函数指针.
* @param c_destory      自定义的销毁函数指针.
* @return               创建成功则返回指向生成的cLinkedList结构体的指针cLinkedList *，失败则返回NULL
* @remarks              自定义的5个函数需要自行实现，然后传入这些函数的指针作为参数
*/
cLinkedList * clinkedlist_create(uint32_t(*c_equals)(void * this, void * another),
	                 int32_t (*c_compareTo)(void * this, void * another), int32_t (*c_hashCode)(void * elem),
	                 void * (*c_copy)(void * elem), void (*c_destory)(void * elem));

/**
* 销毁链表
* @param list    由create返回的cLinkedList结构体指针
* @remarks       调用此函数后，不得再使用list指针，因为其指向的内存已被释放
*/
void clinkedlist_destory(cLinkedList * list);

/**
* 在链表尾部插入元素(不是拷贝一份再插入，而是直接插入)
* @param list    由create返回的cLinkedList结构体指针
* @param elem    要插入的元素指针
* @return        插入成功则返回0，失败返回-1
*/
int16_t clinkedlist_addLast(cLinkedList * list, void * elem);

/**
* 在链表头部插入元素(不是拷贝一份再插入，而是直接插入)
* @param list    由create返回的cLinkedList结构体指针
* @param elem    要插入的元素指针
* @return        插入成功则返回0，失败返回-1
*/
int16_t clinkedlist_addFirst(cLinkedList * list, void * elem);

/**
* 得到链表的总元素数目
* @param list    由create返回的cLinkedList结构体指针
* @return        如果list为NULL 则返回-1 否则返回总元素个数
*/
uint32_t clinkedlist_size(cLinkedList * list);

/**
* 得到链表的指定位置的元素
* @param list    由create返回的cLinkedList结构体指针
* @param index   指定位置 从0开始计
* @return        如果list不为NULL且index位置合法，则返回指定位置处的元素的副本的指针，需要强制类型转换为自定义的类型
*                否则，返回NULL
*/
void * clinkedlist_get(cLinkedList * list, uint32_t index);

/**
* 清除容器内的所有元素
* @param list    由create返回的cLinkedList结构体指针
* @remarks       用户自定义元素的释放由用户自定义的销毁函数destory函数执行
*/
void clinkedlist_clear(cLinkedList * list);

/**
* 删除指定位置的元素
* @param list    由create返回的cLinkedList结构体指针
* @param index   要删除的元素的索引
* @return        成功返回0，失败返回-1
*/
int32_t clinkedlist_remove(cLinkedList * list, uint32_t index);

/**
* 删除指定元素
* @param list    由create返回的cLinkedList结构体指针
* @param Elem    要删除的元素
* @return        成功返回0，失败返回-1
*/
int32_t clinkedlist_removeElem(cLinkedList * list, void * Elem);

/**
* 更新指定位置处的元素
* @param list       由create返回的cLinkedList结构体指针
* @param index      要更新的元素的索引
* @param newValue   指向新元素的指针
* @return           指向旧元素的指针
*/
void * clinkedlist_set(cLinkedList * list,uint32_t index,void * newElem);

/**
* 返回指定元素的索引
* @param list       由create返回的cLinkedList结构体指针
* @param Elem       指定的元素
* @return           指定元素的索引，如果元素不存在，返回-1
*/
int32_t clinkedlist_indexOf(cLinkedList * list, void * Elem);



#endif // !C_LINKEDLIST_H