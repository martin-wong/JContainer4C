#ifndef CARRAYDEQUE_H
#define CARRAYDEQUE_H

#include "user_define.h"

#define DEFAULT_CARRAYDEQUE_CAPACITY 10
typedef struct carraydeque {
	/*
	 [ 10 ,3 ,null ,null ,1 ,3 ,44 ]  ->  elementData
		   ^              ^
          tail           head
	*/
	uint32_t head; //��һ����ЧԪ�ص�λ��
	uint32_t tail; //β����һ����λ
	uint32_t size; //������Ԫ�صĸ���
	uint32_t MAX_ARRAY_SIZE;//�����������
	uint32_t capacity; //�����С
	cMetadata * metaData;
	void ** elementData;//����Ԫ��ָ������� Ҳ���������Ԫ����ָ���û��������ݵ�ָ��
	int32_t (*offerLast)(struct carraydeque * deque, void * elem);
	int32_t(*offerFirst)(struct carraydeque * deque, void * elem);
	void * (*pollFirst)(struct carraydeque * deque);
	void * (*peekFirst)(struct carraydeque * deque);

} cArrayDeque;

/**
* ����ָ����ʼ������cArrayDeque.
* @param c_equals       �Զ��������жϺ���ָ��.
* @param c_compareTo    �Զ���ıȽϴ�С����ָ��.
* @param c_hashCode     �Զ��������hashcode�ĺ���ָ��.
* @param c_copy         �Զ���Ŀ�������ָ��.
* @param c_destory      �Զ�������ٺ���ָ��.
* @param initialCapacity��ʼ���д�С
* @return               �����ɹ��򷵻�ָ�����ɵ�cArrayDeque�ṹ���ָ��cArrayDeque *��ʧ���򷵻�NULL
* @remarks              �Զ����5��������Ҫ����ʵ�֣�Ȼ������Щ������ָ����Ϊ����
*/
cArrayDeque * carraydeque_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem), uint32_t initialCapacity);

cArrayDeque * carraydeque_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem));

/**
* �ڶ�β���Ԫ��
* @param deque      ָ�����ɵ�cArrayDeque�ṹ���ָ��
* @param elem       Ҫ�����Ԫ�ص�ָ��
* @return           ����ɹ��򷵻�0��ʧ���򷵻�-1
*/
int32_t carraydeque_offerLast(cArrayDeque * deque,void * elem);


/**
* �Ӷ���ͷ��Ԫ�� �ҴӶ���ɾ����Ԫ��
* @param deque      ָ�����ɵ�cArrayDeque�ṹ���ָ��
* @return           ����Ϊ�շ���NULL ���򷵻�ͷԪ��
*/
void * carraydeque_pollFirst(cArrayDeque * deque);

/**
* �Ӷ���ͷ��Ԫ�� ��ɾ��Ԫ��
* @param deque      ָ�����ɵ�cArrayDeque�ṹ���ָ��
* @return           ����Ϊ�շ���NULL ���򷵻�ͷԪ��
*/
void * carraydeque_peekFirst(cArrayDeque * deque);

/**
* �ڶ������Ԫ��
* @param deque      ָ�����ɵ�cArrayDeque�ṹ���ָ��
* @param elem       Ҫ�����Ԫ�ص�ָ��
* @return           ����ɹ��򷵻�0��ʧ���򷵻�-1
*/
int32_t carraydeque_offerFirst(cArrayDeque * deque, void * elem);

#endif