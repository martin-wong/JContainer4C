#ifndef CHASHMAP_H
#define CHASHMAP_H

#include <stdint.h>
#include "user_define.h"

typedef struct chashmapentry {
	int32_t hash;//节点的hash值
	struct chashmapentry * next;//指向链表中的下一个entry
	void * key;
	void * value;

}cHashMapEntry;

typedef struct chashmap{
	cMetadata * metaData;
	cHashMapEntry ** table;//散列表
	int32_t numberOfElem; //存放的元素个数
	int32_t capacity; //table的大小
	int32_t threshold;//size超过threshold后 就进行扩容
	float loadFactor; //填充因子 
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
* 插入键值对 如果键已经有关联的值 则覆盖
* @param map       指向生成的cHashMap结构体的指针
* @param key       键 可以为NULL
* @param value     值 可以为NULL
* @return          插入成功返回0 否则返回-1
* @remarks         JDK的HashMap.put()返回的是旧值 与本方法不同
*/
int16_t chashmap_put(cHashMap * map, void * key, void * value);

/**
* 插入键值对 如果已键已和某一值关联 则不添加
* @param map       指向生成的cHashMap结构体的指针
* @param key       键 可以为NULL
* @param value     值 可以为NULL
* @return          插入成功返回0 否则返回-1
*/
int16_t chashmap_putIfAbcent(cHashMap * map, void * key, void * value);
/**
* 插入键值对
* @param map       指向生成的cHashMap结构体的指针
* @param key       键 可以为NULL
* @return          旧值 没有旧值返回NULL
*/
void * chashmap_get(cHashMap * map, void * key);

/**
* 键值对的数目
* @param map       指向生成的cHashMap结构体的指针
* @return          插入成功返回0 否则返回-1
*/
int32_t chashmap_size(cHashMap * map);

/**
* 删除键值对
* @param map       指向生成的cHashMap结构体的指针
* @param key       指定的键
* @return          旧值 若不存在则返回NULL;
*/
void * chashmap_remove(cHashMap * map , void * key);

/**
* 清空所有键值对
* @param map       指向生成的cHashMap结构体的指针
*/
void chashmap_clear( cHashMap * map);

/**
* 销毁容器，所有的内存将被释放
* @param map       指向生成的cHashMap结构体的指针
*/
void chashmap_destory(cHashMap * map);
#endif