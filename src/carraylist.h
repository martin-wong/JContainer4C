#ifndef C_ARRAYLIST_H
#define C_ARRAYLIST_H

#include <stdint.h>
#include "user_define.h"

#define DEFAULT_CARRAYLIST_CAPACITY 10

typedef struct carraylist { 
	
	uint32_t size; //������Ԫ�صĸ���
	uint32_t MAX_ARRAY_SIZE ;//�����������
	uint32_t capacity; //�����С
	cMetadata * metaData;
	void ** elementData;//����Ԫ��ָ������� Ҳ���������Ԫ����ָ���û��������ݵ�ָ��
	int32_t(*addLast)(struct carraylist * list, void * elem);
	int32_t (*add)(struct carraylist * list, uint32_t index, void * elem);
	void * (*get)(struct carraylist * list, uint32_t index);
	void * (*set)(struct carraylist * list, uint32_t index, void * newElem);
	void * (*remove)(struct carraylist * list, uint32_t index);
	int64_t (*indexOf)(struct carraylist * list, void * elem);

} cArrayList;

/**
* ����ָ����ʼ������cArrayList.
* @param c_equals       �Զ��������жϺ���ָ��.
* @param c_compareTo    �Զ���ıȽϴ�С����ָ��.
* @param c_hashCode     �Զ��������hashcode�ĺ���ָ��.
* @param c_copy         �Զ���Ŀ�������ָ��.
* @param c_destory      �Զ�������ٺ���ָ��.
* @param initialCapacity��ʼ�����С
* @return               �����ɹ��򷵻�ָ�����ɵ�cArrayList�ṹ���ָ��cArrayList *��ʧ���򷵻�NULL
* @remarks              �Զ����5��������Ҫ����ʵ�֣�Ȼ������Щ������ָ����Ϊ����
*/
cArrayList * carraylist_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem), uint32_t initialCapacity);

/**
* ����cArrayList.
* @param c_equals       �Զ��������жϺ���ָ��.
* @param c_compareTo    �Զ���ıȽϴ�С����ָ��.
* @param c_hashCode     �Զ��������hashcode�ĺ���ָ��.
* @param c_copy         �Զ���Ŀ�������ָ��.
* @param c_destory      �Զ�������ٺ���ָ��.
* @return               �����ɹ��򷵻�ָ�����ɵ�cArrayList�ṹ���ָ��cArrayList *��ʧ���򷵻�NULL
* @remarks              �Զ����5��������Ҫ����ʵ�֣�Ȼ������Щ������ָ����Ϊ����
*/
cArrayList * carraylist_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem));

/**
* ������ĩβ���Ԫ��
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param elem       Ҫ��ӵ�Ԫ�ص�ָ��
* @param index      �����λ��
* @return           ��ӳɹ��򷵻�0��ʧ���򷵻�-1
*/
int32_t carraylist_add(cArrayList * list, uint32_t index, void * elem);

/**
* ������ĩβ���Ԫ��
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param elem       Ҫ��ӵ�Ԫ�ص�ָ��
* @return           ��ӳɹ��򷵻�0��ʧ���򷵻�-1
*/
int32_t carraylist_addLast(cArrayList * list,void * elem);

/**
* �õ�ָ��λ�õ�Ԫ��
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param index      ����
* @return           ��Ӧindex��û��Ԫ�� ����NULL ���򷵻�ָ��Ԫ�ص�ָ��
*/
void * carraylist_get(cArrayList * list, uint32_t index);

/**
* �滻ָ��λ�ô���Ԫ��
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param index      ����
* @param newElem    ��Ԫ�ص�ָ��
* @return           index���Ϸ� ����NULL ��ӳɹ��򷵻�ָ���Ԫ�ص�ָ��
*/
void * carraylist_set(cArrayList * list, uint32_t index,void * newElem);

/**
* �滻ָ��λ�ô���Ԫ��
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param index      ����
* @return           index���Ϸ� ����NULL ɾ���ɹ��򷵻�ָ��ɾ��Ԫ�ص�ָ��
*/
void * carraylist_remove(cArrayList * list, uint32_t index);

/**
* ����ָ��Ԫ�ص�����
* @param list       ָ�����ɵ�cArrayList�ṹ���ָ��
* @param elem       Ҫ���ҵ�Ԫ��
* @return           �Ҳ�������-1 �ҵ�����index
*/
int64_t carraylist_indexOf(struct carraylist * list, void * elem);
#endif 
