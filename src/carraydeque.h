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
	uint32_t head; //第一个有效元素的位置
	uint32_t tail; //尾部第一个空位
	uint32_t size; //数组中元素的个数
	uint32_t MAX_ARRAY_SIZE;//最大数组容量
	uint32_t capacity; //数组大小
	cMetadata * metaData;
	void ** elementData;//保存元素指针的数组 也就是数组的元素是指向用户传入数据的指针
	int32_t (*offerLast)(struct carraydeque * deque, void * elem);
	int32_t(*offerFirst)(struct carraydeque * deque, void * elem);
	void * (*pollFirst)(struct carraydeque * deque);
	void * (*peekFirst)(struct carraydeque * deque);

} cArrayDeque;

/**
* 创建指定初始容量的cArrayDeque.
* @param c_equals       自定义的相等判断函数指针.
* @param c_compareTo    自定义的比较大小函数指针.
* @param c_hashCode     自定义的生成hashcode的函数指针.
* @param c_copy         自定义的拷贝函数指针.
* @param c_destory      自定义的销毁函数指针.
* @param initialCapacity初始队列大小
* @return               创建成功则返回指向生成的cArrayDeque结构体的指针cArrayDeque *，失败则返回NULL
* @remarks              自定义的5个函数需要自行实现，然后传入这些函数的指针作为参数
*/
cArrayDeque * carraydeque_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem), uint32_t initialCapacity);

cArrayDeque * carraydeque_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem));

/**
* 在队尾添加元素
* @param deque      指向生成的cArrayDeque结构体的指针
* @param elem       要插入的元素的指针
* @return           插入成功则返回0，失败则返回-1
*/
int32_t carraydeque_offerLast(cArrayDeque * deque,void * elem);


/**
* 从队列头拿元素 且从队列删除该元素
* @param deque      指向生成的cArrayDeque结构体的指针
* @return           队列为空返回NULL 否则返回头元素
*/
void * carraydeque_pollFirst(cArrayDeque * deque);

/**
* 从队列头拿元素 不删除元素
* @param deque      指向生成的cArrayDeque结构体的指针
* @return           队列为空返回NULL 否则返回头元素
*/
void * carraydeque_peekFirst(cArrayDeque * deque);

/**
* 在队首添加元素
* @param deque      指向生成的cArrayDeque结构体的指针
* @param elem       要插入的元素的指针
* @return           插入成功则返回0，失败则返回-1
*/
int32_t carraydeque_offerFirst(cArrayDeque * deque, void * elem);

#endif