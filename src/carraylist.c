#include <math.h>
#include "carraylist.h"

int32_t _arraylist_ensure_capacity(cArrayList * list, uint32_t expected);
void _arraylist_copy(cArrayList * list, uint32_t from, uint32_t to, uint32_t numMoved);
int32_t _arraylist_range_check(cArrayList * list, uint32_t index);

cArrayList * carraylist_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	void * (*c_copy)(void * elem), void(*c_destory)(void * elem),uint32_t initialCapacity) {

	cArrayList * p = (cArrayList *)malloc(sizeof(cArrayList));
	if (!p) //分配内存失败
		return NULL;
	cMetadata *  metadate_p = (cMetadata *)malloc(sizeof(cMetadata));
	if (!metadate_p) {
		free(p);
		return NULL;
	}
	//初始化相关数据
	metadate_p->equals = c_equals;
	metadate_p->compareTo = c_compareTo;
	metadate_p->hashCode = c_hashCode;
	metadate_p->copy = c_copy;
	metadate_p->destory = c_destory;

	p->elementData = NULL;
	p->metaData = metadate_p; //初始化元数据
    p->MAX_ARRAY_SIZE = pow(2,sizeof(uint32_t)*8)-8;
	p->size = 0;
	p->capacity = 0;
	if (initialCapacity > 0) { //如果指定了初始容量 
		(p->elementData) = (void **)malloc(initialCapacity * sizeof(void *));
		if (!p->elementData) {
			free(p);
			return NULL;
		}
		p->capacity = initialCapacity;
	}
	p->addLast = carraylist_addLast;
	p->add = carraylist_add;
	p->get = carraylist_get;
	p->set = carraylist_set;
	p->remove = carraylist_remove;
	p->indexOf = carraylist_indexOf;
	p->destory = carraylist_destory;
	p->clear = carraylist_clear;

	return p;
}

cArrayList * carraylist_create(uint32_t(*c_equals)(void * this, void * another),
	    int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem),
	     void * (*c_copy)(void * elem), void(*c_destory)(void * elem)) {
	carraylist_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory,DEFAULT_CARRAYLIST_CAPACITY);
}

void carraylist_destory(cArrayList * list){
	if (!list)
		return;
	list->clear(list);
	free(list->metaData);
	free(list->elementData);
	free(list);
}

int32_t carraylist_addLast(cArrayList * list, void * elem) {
	if (!list || !elem || _arraylist_ensure_capacity(list, list->size + 1))
		return -1;
	list->elementData[list->size++] = elem;
	return 0;
}

int32_t carraylist_add(cArrayList * list, uint32_t index, void * elem) {
	if (!list || !elem || _arraylist_range_check(list, index) || _arraylist_ensure_capacity(list, list->size + 1))
		return -1;
	_arraylist_copy(list, index, index + 1, list->size - index );
	list->elementData[index] = elem;
	list->size++;
	return 0;
}

void * carraylist_get(cArrayList * list, uint32_t index) {
	if (!list || index < 0 || index > list->size - 1)
		return NULL;
	return list->elementData[index];
}

void * carraylist_set(cArrayList * list, uint32_t index, void * newElem) {
	if (!list || !newElem || _arraylist_range_check(list, index))
		return NULL;
	void * oldElem = list->elementData[index];
	list->elementData[index] = newElem;
	return oldElem;
}

int64_t carraylist_indexOf(struct carraylist * list, void * elem) {
	if (!list || !elem)
		return -1;
	for (int i = 0; i < list->size; i++) {
		if (!list->metaData->equals(elem, list->elementData[i]))
			return i;
	}
	return -1;
}

void carraylist_clear(cArrayList * list){
	if (!list)
		return;
	for (int i = 0 ; i < list->size ; i++){
		void * elem = list->elementData[i];
		if(elem)
		   list->metaData->destory(list->elementData[i]);
		list->elementData[i] = NULL;
	}
	list->size = 0;
}

void * carraylist_remove(cArrayList * list, uint32_t index) {
	if (!list || _arraylist_range_check(list, index))
		return NULL;
	void * oldElem = list->elementData[index];
	uint32_t numMoved = list->size - index - 1; //需要移动的元素个数
	if (numMoved > 0)
		_arraylist_copy(list,index+1,index,numMoved);
	list->size--;
	return oldElem;
}

void _arraylist_copy(cArrayList * list, uint32_t from, uint32_t to, uint32_t numMoved) {//将索引index开始的numMoved个元素拷贝到索引to处
	void ** array = list->elementData;
	if (from > to) 
		for (int i = 0; i < numMoved; i++)
			array[to+i] = array[from+i];
	else
		for (int i = numMoved-1; i >= 0; i--)
			array[to + i] = array[from + i];
}

//确保索引合法，不合法则返回-1 合法返回0
int32_t _arraylist_range_check(cArrayList * list, uint32_t index) {
	if (index < 0 || ((index+1) > list->size ))
		return -1;
    return 0;
}
//容量足够返回0 不够则申请容量然后返回0 申请失败返回-1
int32_t _arraylist_ensure_capacity(cArrayList * list,uint32_t expected) {
	uint32_t curCapacity = list->capacity;
	uint32_t curSize = list->size;
	uint32_t newCapacity = 0;
	if (expected <= curCapacity)
		return 0;
	if (curCapacity < DEFAULT_CARRAYLIST_CAPACITY) { //小于默认容量 每次加 4
		 newCapacity =  4 + curCapacity;
	}else {
		//已没有内存可以分配 返回-1
		if (curCapacity >= list->MAX_ARRAY_SIZE)
			return -1;
		newCapacity = curCapacity + (curCapacity >> 1);  //扩容1.5倍
		if ( newCapacity < curCapacity || newCapacity < (curCapacity >> 1))
			newCapacity = list->MAX_ARRAY_SIZE ;//超出了uint32_t的范围(溢出) 就设置为MAX_ARRAY_SIZE
	}
	void ** newArray = (void **)malloc(newCapacity * sizeof(void *));
	if (!newArray)
		return -1;
	for (int i = 0; i < curSize; i++) 
		newArray[i] = list->elementData[i];
	if(list->elementData)
	    free(list->elementData);
	list->elementData = newArray;
	list->capacity = newCapacity;
	return 0;;
}

