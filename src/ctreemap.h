#ifndef CTREEMAP_H
#define CTREEMAP_H

#include "user_define.h"

static enum Color { RED, BLACK };
typedef struct ctreemapnode {

	void * key;
	void * value;
	struct ctreemapnode * left;
	struct ctreemapnode * right;
	enum Color color;
	uint32_t n;

}cTreeMapNode;

typedef struct ctreemap {

	cTreeMapNode * root;
	cMetadata * metaData;

	c_boolean (*put)(struct ctreemap * map, void * key, void * value);
	int32_t (*size)(struct ctreemap * * map);

}cTreeMap;


cTreeMap * ctreemap_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem), void * (*c_copy)(void * elem),
	void(*c_destory)(void * elem), void(*c_destoryValue)(valueType * value));

/**
* �����ֵ�� ������Ѿ��й�����ֵ �򸲸�
* @param map       ָ�����ɵ�cTreeMap�ṹ���ָ��
* @param key       �� ����ΪNULL ������ʵ�ֺ����compareTo()
* @param value     ֵ ����ΪNULL
* @return          ����ɹ�����c_TRUE ���򷵻�c_FALSE
*/
c_boolean ctreemap_put(cTreeMap * map, void * key, void * value);

/**
* ����Ԫ�ظ���
* @param map       ָ�����ɵ�cTreeMap�ṹ���ָ��
* @return          Ԫ�ظ���
*/
int32_t ctreemap_size(cTreeMap * map);

#endif // !CTREEMAP_H
