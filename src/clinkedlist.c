#include "clinkedlist.h"

void _clinkedlist_free_node(cLinkedList * list, cLinkedListNode * node);
cLinkedListNode * _clinkedlist_find_element_pointer(cLinkedList * list, uint32_t index);

//创建链表
cLinkedList * clinkedlist_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem)) {

	cLinkedList * p = (cLinkedList *)malloc(sizeof(cLinkedList));
	if (!p) //分配内存失败
		return NULL;
	cMetadata *  metadate_p = (cMetadata * )malloc(sizeof(cMetadata));
	if (!metadate_p) {
		free(p);
		return NULL;
	}
	metadate_p->equals = c_equals;
	metadate_p->compareTo = c_compareTo;
	metadate_p->hashCode = c_hashCode;
	metadate_p->copy = c_copy;
	metadate_p->destory = c_destory;
	p->metaData = metadate_p; //初始化元数据
	p->head = NULL;
	p->tail = NULL;
	p->numberOfElem = 0;//初始化链表的总大小为0
	p->addLast = clinkedlist_addLast;//初始化各类函数指针
	p->addFirst = clinkedlist_addFirst;
	p->size = clinkedlist_size;
	p->clear = clinkedlist_clear;
	p->get = clinkedlist_get;
	p->remove = clinkedlist_remove;
	p->removeElem = clinkedlist_removeElem;
	p->set = clinkedlist_set;
	p->indexOf = clinkedlist_indexOf;
	p->destory = clinkedlist_destory;
	return p;

}

void clinkedlist_destory(cLinkedList * list) {
	if (!list)
		return -1;
	//释放每个节点的内存
	cLinkedListNode * cur = list->head;
	cLinkedListNode * next;
	while (cur) {
		next = cur->next;
		_clinkedlist_free_node(list, cur);
		cur = next;
	}

	free(list->metaData);
	free(list);

}

//返回链表总元素个数
uint32_t clinkedlist_size(cLinkedList * list){
	return list?list->numberOfElem:-1;
}

//从链表尾部插入节点
int16_t clinkedlist_addLast(cLinkedList * list, void * elem) {
	if (!list || !elem) //如果指针为null
		return -1;
	//链表不为空的情况
	if (list->numberOfElem) {
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//分配失败 返回-1
			return -1;
		}
		newNode->elem = elem;//初始化申请到的Node
		newNode->next = NULL;
		newNode->prev = NULL;
	    //插入尾部
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
		list->numberOfElem++;
	}else { //链表为空的情况
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//分配失败 返回-1
			return -1;
		}
		list->head = newNode;//将头尾指针指向新申请的这个节点
		list->tail = newNode;
		newNode->elem = elem;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->numberOfElem = 1;
	}
	return 0;
}

//从链表头部插入元素
int16_t clinkedlist_addFirst(cLinkedList * list, void * elem) {
	if (!list || !elem) //如果指针为null
		return -1;
	//链表不为空的情况
	if (list->numberOfElem) {
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//分配失败 返回-1
			return -1;
		}
		newNode->elem = elem;//初始化申请到的Node
		newNode->next = NULL;
		newNode->prev = NULL;
		//插入头部
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
		list->numberOfElem++;
	}
	else { //链表为空的情况
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//分配失败 返回-1
			return -1;
		}
		list->head = newNode;//将头尾指针指向新申请的这个节点
		list->tail = newNode;
		newNode->elem = elem;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->numberOfElem = 1;
	}
	return 0;
}
//从指定位置拿到元素
void * clinkedlist_get(cLinkedList * list,uint32_t index) {

	cLinkedListNode * cur = _clinkedlist_find_element_pointer(list,index);
	if (cur)
		return cur->elem;
	else
		return NULL;
}
//清空链表所有元素
void clinkedlist_clear(cLinkedList * list) {
	if (!list || !list->head) //如果指针为null或者元素个数为0
		return;
	cLinkedListNode * cur = list->head->next;
	do{
		list->metaData->destory(list->head->elem);//调用用户自定义的销毁函数对用户数据进行销毁
		free(list->head); //释放申请的cLinkedListNode节点的内存
		list->head = cur;
		cur = cur ? cur->next:NULL ;
	} while (cur);
	list->metaData->destory(list->head->elem);
	free(list->head);
	list->numberOfElem = 0;//重置元素数量为0
	list->head = NULL;
	list->tail = NULL;
}

int32_t clinkedlist_remove(cLinkedList * list, uint32_t index){
	cLinkedListNode * cur = _clinkedlist_find_element_pointer(list, index);
	if (!cur)
		return -1;
	if (cur == list->head && cur == list->tail) {
		list->head = list->tail = NULL;
	}
	else if (cur == list->head) {//如果要删除的是头节点
		cur->next->prev = NULL;
		list->head = cur->next;
	}
	else if (cur == list->tail) {//如果要删除的是尾节点
		cur->prev->next = NULL;
		list->tail = cur->prev;
	}
	else {
		cLinkedListNode * PREV = cur->prev;
		cLinkedListNode * NEXT = cur->next;
		PREV->next = NEXT;
		if (NEXT)
			NEXT->prev = PREV;
	}
	_clinkedlist_free_node(list, cur);
	list->numberOfElem--;
	return 0;
}

int32_t clinkedlist_removeElem(cLinkedList * list, void * elem) {
	if (!list || !elem)
		return -1;
	int32_t index = clinkedlist_indexOf(list,elem);
	if (index == -1)
		return -1;
	if (clinkedlist_remove(list, index) == -1)
		return -1;
	return 0;

}

void * clinkedlist_set(cLinkedList * list, uint32_t index, void * newElem) {
	if (!newElem)
		return NULL;
	cLinkedListNode * oldNode = _clinkedlist_find_element_pointer(list, index);
	if (!oldNode)
		return NULL;
	void * oldElem = oldNode->elem;
	oldNode->elem = newElem;
	return oldElem;
}

int32_t clinkedlist_indexOf(cLinkedList * list, void * Elem){
	if (!list || !list->numberOfElem || !Elem)
		return -1;
	cLinkedListNode * cur = list->head;
	int32_t index = 0;
	do {
		int32_t value = list->metaData->equals(cur->elem,Elem);//比较
		if (!value) //如果相等
			return index;
		index++;
		cur = cur->next;
	} while (cur);
	return -1;
}

/************************************************************************/
/* 以下以_打头的都是辅助函数，不对库的使用者公开，所以头文件里不包含这些辅助函数                                                                     */
/************************************************************************/

//释放指定链表指定节点的内存
void _clinkedlist_free_node(cLinkedList * list , cLinkedListNode * node) {
	list->metaData->destory(node->elem);
	free(node);
}

//返回指定索引处的节点的指针
cLinkedListNode * _clinkedlist_find_element_pointer(cLinkedList * list, uint32_t index) {
	if (!list || index >= list->numberOfElem || list->numberOfElem == 0)
		return NULL;;
	cLinkedListNode * cur = list->head;//cur最终会指向要删除的节点
	uint32_t count = 0;
	while (count != index) {
		cur = cur->next;
		count++;
	}
	return cur;
}