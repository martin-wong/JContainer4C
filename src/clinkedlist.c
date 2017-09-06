#include "clinkedlist.h"

void _clinkedlist_free_node(cLinkedList * list, cLinkedListNode * node);
cLinkedListNode * _clinkedlist_find_element_pointer(cLinkedList * list, uint32_t index);

//��������
cLinkedList * clinkedlist_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem)) {

	cLinkedList * p = (cLinkedList *)malloc(sizeof(cLinkedList));
	if (!p) //�����ڴ�ʧ��
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
	p->metaData = metadate_p; //��ʼ��Ԫ����
	p->head = NULL;
	p->tail = NULL;
	p->numberOfElem = 0;//��ʼ��������ܴ�СΪ0
	p->addLast = clinkedlist_addLast;//��ʼ�����ຯ��ָ��
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
	//�ͷ�ÿ���ڵ���ڴ�
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

//����������Ԫ�ظ���
uint32_t clinkedlist_size(cLinkedList * list){
	return list?list->numberOfElem:-1;
}

//������β������ڵ�
int16_t clinkedlist_addLast(cLinkedList * list, void * elem) {
	if (!list || !elem) //���ָ��Ϊnull
		return -1;
	//����Ϊ�յ����
	if (list->numberOfElem) {
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//����ʧ�� ����-1
			return -1;
		}
		newNode->elem = elem;//��ʼ�����뵽��Node
		newNode->next = NULL;
		newNode->prev = NULL;
	    //����β��
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
		list->numberOfElem++;
	}else { //����Ϊ�յ����
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//����ʧ�� ����-1
			return -1;
		}
		list->head = newNode;//��ͷβָ��ָ�������������ڵ�
		list->tail = newNode;
		newNode->elem = elem;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->numberOfElem = 1;
	}
	return 0;
}

//������ͷ������Ԫ��
int16_t clinkedlist_addFirst(cLinkedList * list, void * elem) {
	if (!list || !elem) //���ָ��Ϊnull
		return -1;
	//����Ϊ�յ����
	if (list->numberOfElem) {
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//����ʧ�� ����-1
			return -1;
		}
		newNode->elem = elem;//��ʼ�����뵽��Node
		newNode->next = NULL;
		newNode->prev = NULL;
		//����ͷ��
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
		list->numberOfElem++;
	}
	else { //����Ϊ�յ����
		cLinkedListNode * newNode = (cLinkedListNode *)malloc(sizeof(cLinkedListNode));
		if (!newNode) {//����ʧ�� ����-1
			return -1;
		}
		list->head = newNode;//��ͷβָ��ָ�������������ڵ�
		list->tail = newNode;
		newNode->elem = elem;
		newNode->next = NULL;
		newNode->prev = NULL;
		list->numberOfElem = 1;
	}
	return 0;
}
//��ָ��λ���õ�Ԫ��
void * clinkedlist_get(cLinkedList * list,uint32_t index) {

	cLinkedListNode * cur = _clinkedlist_find_element_pointer(list,index);
	if (cur)
		return cur->elem;
	else
		return NULL;
}
//�����������Ԫ��
void clinkedlist_clear(cLinkedList * list) {
	if (!list || !list->head) //���ָ��Ϊnull����Ԫ�ظ���Ϊ0
		return;
	cLinkedListNode * cur = list->head->next;
	do{
		list->metaData->destory(list->head->elem);//�����û��Զ�������ٺ������û����ݽ�������
		free(list->head); //�ͷ������cLinkedListNode�ڵ���ڴ�
		list->head = cur;
		cur = cur ? cur->next:NULL ;
	} while (cur);
	list->metaData->destory(list->head->elem);
	free(list->head);
	list->numberOfElem = 0;//����Ԫ������Ϊ0
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
	else if (cur == list->head) {//���Ҫɾ������ͷ�ڵ�
		cur->next->prev = NULL;
		list->head = cur->next;
	}
	else if (cur == list->tail) {//���Ҫɾ������β�ڵ�
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
		int32_t value = list->metaData->equals(cur->elem,Elem);//�Ƚ�
		if (!value) //������
			return index;
		index++;
		cur = cur->next;
	} while (cur);
	return -1;
}

/************************************************************************/
/* ������_��ͷ�Ķ��Ǹ������������Կ��ʹ���߹���������ͷ�ļ��ﲻ������Щ��������                                                                     */
/************************************************************************/

//�ͷ�ָ������ָ���ڵ���ڴ�
void _clinkedlist_free_node(cLinkedList * list , cLinkedListNode * node) {
	list->metaData->destory(node->elem);
	free(node);
}

//����ָ���������Ľڵ��ָ��
cLinkedListNode * _clinkedlist_find_element_pointer(cLinkedList * list, uint32_t index) {
	if (!list || index >= list->numberOfElem || list->numberOfElem == 0)
		return NULL;;
	cLinkedListNode * cur = list->head;//cur���ջ�ָ��Ҫɾ���Ľڵ�
	uint32_t count = 0;
	while (count != index) {
		cur = cur->next;
		count++;
	}
	return cur;
}