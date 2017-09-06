#ifndef C_LINKEDLIST_H
#define C_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "user_define.h"


typedef struct clinkedlistnode {

	void * elem; //ָ���������û��Զ����Ԫ��
	struct clinkedlistnode * next; //��һ���ڵ�
	struct clinkedlistnode * prev; //ǰһ���ڵ�

} cLinkedListNode;

typedef struct clinkedlist { //linkedlist�������ݽṹ

	cMetadata * metaData; //ָ��Ԫ���ݽṹ��
	cLinkedListNode *  head; //ָ��ͷ�ڵ㣨����һ����Ч�ڵ㣩
	cLinkedListNode *  tail; //ָ��β�ڵ�
	uint32_t numberOfElem ; //������Ԫ�ظ���
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
* ����cLinkedList���ݽṹ.
* @param c_equals       �Զ��������жϺ���ָ��.
* @param c_compareTo    �Զ���ıȽϴ�С����ָ��.
* @param c_hashCode     �Զ��������hashcode�ĺ���ָ��.
* @param c_copy         �Զ���Ŀ�������ָ��.
* @param c_destory      �Զ�������ٺ���ָ��.
* @return               �����ɹ��򷵻�ָ�����ɵ�cLinkedList�ṹ���ָ��cLinkedList *��ʧ���򷵻�NULL
* @remarks              �Զ����5��������Ҫ����ʵ�֣�Ȼ������Щ������ָ����Ϊ����
*/
cLinkedList * clinkedlist_create(uint32_t(*c_equals)(void * this, void * another),
	                 int32_t (*c_compareTo)(void * this, void * another), int32_t (*c_hashCode)(void * elem),
	                 void * (*c_copy)(void * elem), void (*c_destory)(void * elem));

/**
* ��������
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @remarks       ���ô˺����󣬲�����ʹ��listָ�룬��Ϊ��ָ����ڴ��ѱ��ͷ�
*/
void clinkedlist_destory(cLinkedList * list);

/**
* ������β������Ԫ��(���ǿ���һ���ٲ��룬����ֱ�Ӳ���)
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @param elem    Ҫ�����Ԫ��ָ��
* @return        ����ɹ��򷵻�0��ʧ�ܷ���-1
*/
int16_t clinkedlist_addLast(cLinkedList * list, void * elem);

/**
* ������ͷ������Ԫ��(���ǿ���һ���ٲ��룬����ֱ�Ӳ���)
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @param elem    Ҫ�����Ԫ��ָ��
* @return        ����ɹ��򷵻�0��ʧ�ܷ���-1
*/
int16_t clinkedlist_addFirst(cLinkedList * list, void * elem);

/**
* �õ��������Ԫ����Ŀ
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @return        ���listΪNULL �򷵻�-1 ���򷵻���Ԫ�ظ���
*/
uint32_t clinkedlist_size(cLinkedList * list);

/**
* �õ������ָ��λ�õ�Ԫ��
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @param index   ָ��λ�� ��0��ʼ��
* @return        ���list��ΪNULL��indexλ�úϷ����򷵻�ָ��λ�ô���Ԫ�صĸ�����ָ�룬��Ҫǿ������ת��Ϊ�Զ��������
*                ���򣬷���NULL
*/
void * clinkedlist_get(cLinkedList * list, uint32_t index);

/**
* ��������ڵ�����Ԫ��
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @remarks       �û��Զ���Ԫ�ص��ͷ����û��Զ�������ٺ���destory����ִ��
*/
void clinkedlist_clear(cLinkedList * list);

/**
* ɾ��ָ��λ�õ�Ԫ��
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @param index   Ҫɾ����Ԫ�ص�����
* @return        �ɹ�����0��ʧ�ܷ���-1
*/
int32_t clinkedlist_remove(cLinkedList * list, uint32_t index);

/**
* ɾ��ָ��Ԫ��
* @param list    ��create���ص�cLinkedList�ṹ��ָ��
* @param Elem    Ҫɾ����Ԫ��
* @return        �ɹ�����0��ʧ�ܷ���-1
*/
int32_t clinkedlist_removeElem(cLinkedList * list, void * Elem);

/**
* ����ָ��λ�ô���Ԫ��
* @param list       ��create���ص�cLinkedList�ṹ��ָ��
* @param index      Ҫ���µ�Ԫ�ص�����
* @param newValue   ָ����Ԫ�ص�ָ��
* @return           ָ���Ԫ�ص�ָ��
*/
void * clinkedlist_set(cLinkedList * list,uint32_t index,void * newElem);

/**
* ����ָ��Ԫ�ص�����
* @param list       ��create���ص�cLinkedList�ṹ��ָ��
* @param Elem       ָ����Ԫ��
* @return           ָ��Ԫ�ص����������Ԫ�ز����ڣ�����-1
*/
int32_t clinkedlist_indexOf(cLinkedList * list, void * Elem);



#endif // !C_LINKEDLIST_H