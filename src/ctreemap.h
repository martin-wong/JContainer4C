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
* 插入键值对 如果键已经有关联的值 则覆盖
* @param map       指向生成的cTreeMap结构体的指针
* @param key       键 可以为NULL 但必须实现合理的compareTo()
* @param value     值 可以为NULL
* @return          插入成功返回c_TRUE 否则返回c_FALSE
*/
c_boolean ctreemap_put(cTreeMap * map, void * key, void * value);

/**
* 返回元素个数
* @param map       指向生成的cTreeMap结构体的指针
* @return          元素个数
*/
int32_t ctreemap_size(cTreeMap * map);

#endif // !CTREEMAP_H
