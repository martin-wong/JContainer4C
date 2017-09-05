#include "carraydeque.h"
#include <math.h>


cArrayDeque * carraydeque_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem), uint32_t initialCapacity) {

	cArrayDeque * p = (cArrayDeque *)malloc(sizeof(cArrayDeque));
	if (!p) //分配内存失败
		return NULL;
	cMetadata *  metadate_p = (cMetadata *)malloc(sizeof(cMetadata));
	if (!metadate_p) {
		free(p);
		return NULL;
	}
	metadate_p->equals = c_equals;
	metadate_p->compareTo = c_compareTo;
	metadate_p->hashCode = c_hashCode;
	metadate_p->copy = c_copy;
	metadate_p->destory = c_destory;

	p->capacity = initialCapacity > 0 ? initialCapacity : 1; //初始容量最小为1
	(p->elementData) = (void **)malloc(p->capacity * sizeof(void *));
	if (!p->elementData) {
		free(p);
		return NULL;
	}

	p->metaData = metadate_p; //初始化元数据
	p->MAX_ARRAY_SIZE = pow(2, sizeof(uint32_t) * 8) - 8;
	p->size = 0;
	p->head = 0;
	p->tail = 0;
	
	p->offerLast = carraydeque_offerLast;
	p->peekFirst = carraydeque_peekFirst;
	p->pollFirst = carraydeque_pollFirst;
	p->offerFirst = carraydeque_offerFirst;
	return p;

}

cArrayDeque * carraydeque_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem)) {

	carraydeque_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, DEFAULT_CARRAYDEQUE_CAPACITY);
}

int32_t carraydeque_offerLast(cArrayDeque * deque, void * elem) {
	if (!elem || !deque)  return -1;
	uint32_t oldtail = deque->tail;
	uint32_t head = deque->head;

	deque->elementData[oldtail] = elem;
	deque->tail = (oldtail + 1) == deque->capacity ? 0 : oldtail + 1; //tail抵达了末尾 需要设置到头部 否则加一即可
	//插入之后如果已经没有空间了 就会扩容 这就保证了下次插入一定是有空间的
	if (deque->tail == head)
		if (need_larger_capacity(deque)) {//扩容失败 取消这次的插入
			deque->elementData[oldtail] = NULL;
			deque->tail = oldtail;
			return -1;
		}
	deque->size++; //插入之后仍有空间
	return 0;

}

void * carraydeque_pollFirst(cArrayDeque * deque){
	
	if (!deque || !deque->size)
		return NULL;
	deque->size--;
	void * old = deque->elementData[deque->head];
	deque->head = (deque->head + 1 == deque->capacity )? 0:deque->head + 1;
	return old;
}

void * carraydeque_peekFirst(cArrayDeque * deque){

	if(!deque || !deque->size)
	   return NULL;
	return deque->elementData[deque->head];
}

int32_t carraydeque_offerFirst(cArrayDeque * deque, void * elem){
	if (!elem || !deque)  return -1;

	uint32_t oldhead = deque->head;
	uint32_t newhead = oldhead ? oldhead - 1 : deque->capacity - 1;

	deque->elementData[newhead] = elem;
	deque->head = newhead;
 //插入之后如果已经没有空间了 就会扩容 这就保证了下次插入一定是有空间的
	if (deque->tail == newhead)
		if (need_larger_capacity(deque)) {//扩容失败 取消这次的插入
			deque->elementData[newhead] = NULL;
			deque->head = oldhead;
			return -1;
		}
	deque->size++; //插入之后仍有空间
	return 0;
}

////head往前遇上了tail 或 tail往后遇到了head 才导致扩容,扩容2倍  失败则返回-1 否则返回0
int32_t need_larger_capacity(cArrayDeque * deque) {
	//head往前遇上了tail 或 tail往后遇到了head 才导致扩容
	uint32_t curCapacity = deque->capacity;
	if (curCapacity >= deque->MAX_ARRAY_SIZE)
		return -1;
	uint32_t newCapacity = curCapacity << 1 ;  //扩容2倍
	if (newCapacity < curCapacity)
		newCapacity = deque->MAX_ARRAY_SIZE;//超出了uint32_t的范围(溢出) 就设置为MAX_ARRAY_SIZE
	
	void ** newArray = (void **)malloc(newCapacity * sizeof(void *));
	if (!newArray)
		return -1;

	for (int i = deque->head ,j = 0; i < curCapacity ; i++,j++)
		newArray[j] = deque->elementData[i];
	for (int i = 0, j = curCapacity - deque->head - 1 ; i < deque->head; i++)
		newArray[j] = deque->elementData[i];

	if (deque->elementData)
		free(deque->elementData);

	deque->elementData = newArray;
	deque->capacity = newCapacity;
	deque->head = 0;
	deque->tail = curCapacity ;
	return 0;
}