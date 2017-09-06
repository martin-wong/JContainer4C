#ifndef CHASHMAP_H
#define CHASHMAP_H

#include <stdint.h>
#include "user_define.h"

typedef struct chashmapentry {
	int32_t hash;//�ڵ��hashֵ
	struct chashmapentry * next;//ָ�������е���һ��entry
	void * key;
	void * value;

}cHashMapEntry;

typedef struct chashmap{
	cMetadata * metaData;
	cHashMapEntry ** table;//ɢ�б�
	int32_t numberOfElem; //��ŵ�Ԫ�ظ���
	int32_t capacity; //table�Ĵ�С
	int32_t threshold;//size����threshold�� �ͽ�������
	float loadFactor; //������� 
	int16_t (*put)(struct chashmap * map, void * key, void * value);
	int16_t(*putIfAbcent)(struct chashmap * map, void * key, void * value);
	int32_t (*size)(struct chashmap * map);
	void (*clear)(struct chashmap * map);
	void * (*get)(struct chashmap  * map, void * key);
	void * (*remove)(struct chashmap * map, void * key);
	void (*destory)(struct chashmap * map);

}cHashMap;



cHashMap * chashmap_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem), void * (*c_copy)(void * elem),
	void(*c_destory)(void * elem), void (*c_destoryValue)(valueType * value), int32_t initialCapacity, float loadFactor);


cHashMap * chashmap_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem), void * (*c_copy)(void * elem),
	void(*c_destory)(void * elem), void(*c_destoryValue)(valueType * value));

/**
* �����ֵ�� ������Ѿ��й�����ֵ �򸲸�
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
* @param key       �� ����ΪNULL
* @param value     ֵ ����ΪNULL
* @return          ����ɹ�����0 ���򷵻�-1
* @remarks         JDK��HashMap.put()���ص��Ǿ�ֵ �뱾������ͬ
*/
int16_t chashmap_put(cHashMap * map, void * key, void * value);

/**
* �����ֵ�� ����Ѽ��Ѻ�ĳһֵ���� �����
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
* @param key       �� ����ΪNULL
* @param value     ֵ ����ΪNULL
* @return          ����ɹ�����0 ���򷵻�-1
*/
int16_t chashmap_putIfAbcent(cHashMap * map, void * key, void * value);
/**
* �����ֵ��
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
* @param key       �� ����ΪNULL
* @return          ��ֵ û�о�ֵ����NULL
*/
void * chashmap_get(cHashMap * map, void * key);

/**
* ��ֵ�Ե���Ŀ
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
* @return          ����ɹ�����0 ���򷵻�-1
*/
int32_t chashmap_size(cHashMap * map);

/**
* ɾ����ֵ��
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
* @param key       ָ���ļ�
* @return          ��ֵ ���������򷵻�NULL;
*/
void * chashmap_remove(cHashMap * map , void * key);

/**
* ������м�ֵ��
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
*/
void chashmap_clear( cHashMap * map);

/**
* �������������е��ڴ潫���ͷ�
* @param map       ָ�����ɵ�cHashMap�ṹ���ָ��
*/
void chashmap_destory(cHashMap * map);
#endif