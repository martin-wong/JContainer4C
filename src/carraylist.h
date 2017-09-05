#ifndef C_ARRAYLIST_H
#define C_ARRAYLIST_H

#include <stdint.h>
#include "user_define.h"

#define DEFAULT_CARRAYLIST_CAPACITY 10

typedef struct carraylist { 
	
	uint32_t size; //数组中元素的个数
	uint32_t MAX_ARRAY_SIZE ;//最大数组容量
	uint32_t capacity; //数组大小
	cMetadata * metaData;
	void ** elementData;//保存元素指针的数组 也就是数组的元素是指向用户传入数据的指针
	int32_t(*addLast)(struct carraylist * list, void * elem);
	int32_t (*add)(struct carraylist * list, uint32_t index, void * elem);
	void * (*get)(struct carraylist * list, uint32_t index);
	void * (*set)(struct carraylist * list, uint32_t index, void * newElem);
	void * (*remove)(struct carraylist * list, uint32_t index);
	int64_t (*indexOf)(struct carraylist * list, void * elem);

} cArrayList;

/**
* 创建指定初始容量的cArrayList.
* @param c_equals       自定义的相等判断函数指针.
* @param c_compareTo    自定义的比较大小函数指针.
* @param c_hashCode     自定义的生成hashcode的函数指针.
* @param c_copy         自定义的拷贝函数指针.
* @param c_destory      自定义的销毁函数指针.
* @param initialCapacity初始数组大小
* @return               创建成功则返回指向生成的cArrayList结构体的指针cArrayList *，失败则返回NULL
* @remarks              自定义的5个函数需要自行实现，然后传入这些函数的指针作为参数
*/
cArrayList * carraylist_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem), uint32_t initialCapacity);

/**
* 创建cArrayList.
* @param c_equals       自定义的相等判断函数指针.
* @param c_compareTo    自定义的比较大小函数指针.
* @param c_hashCode     自定义的生成hashcode的函数指针.
* @param c_copy         自定义的拷贝函数指针.
* @param c_destory      自定义的销毁函数指针.
* @return               创建成功则返回指向生成的cArrayList结构体的指针cArrayList *，失败则返回NULL
* @remarks              自定义的5个函数需要自行实现，然后传入这些函数的指针作为参数
*/
cArrayList * carraylist_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem));

/**
* 在数组末尾添加元素
* @param list       指向生成的cArrayList结构体的指针
* @param elem       要添加的元素的指针
* @param index      插入的位置
* @return           添加成功则返回0，失败则返回-1
*/
int32_t carraylist_add(cArrayList * list, uint32_t index, void * elem);

/**
* 在数组末尾添加元素
* @param list       指向生成的cArrayList结构体的指针
* @param elem       要添加的元素的指针
* @return           添加成功则返回0，失败则返回-1
*/
int32_t carraylist_addLast(cArrayList * list,void * elem);

/**
* 得到指定位置的元素
* @param list       指向生成的cArrayList结构体的指针
* @param index      索引
* @return           对应index上没有元素 返回NULL 否则返回指向元素的指针
*/
void * carraylist_get(cArrayList * list, uint32_t index);

/**
* 替换指定位置处的元素
* @param list       指向生成的cArrayList结构体的指针
* @param index      索引
* @param newElem    新元素的指针
* @return           index不合法 返回NULL 添加成功则返回指向旧元素的指针
*/
void * carraylist_set(cArrayList * list, uint32_t index,void * newElem);

/**
* 替换指定位置处的元素
* @param list       指向生成的cArrayList结构体的指针
* @param index      索引
* @return           index不合法 返回NULL 删除成功则返回指向删除元素的指针
*/
void * carraylist_remove(cArrayList * list, uint32_t index);

/**
* 查找指定元素的索引
* @param list       指向生成的cArrayList结构体的指针
* @param elem       要查找的元素
* @return           找不到返回-1 找到返回index
*/
int64_t carraylist_indexOf(struct carraylist * list, void * elem);
#endif 
