#include "chashmap.h"
#include "user_define.h"
#include <stdlib.h>

static float DEFAULT_LOAD_FACTOR = 0.75f; //默认0.75f
static uint32_t MAXIMUM_CAPACITY = 1 << 30;//最大的table大小
static uint32_t DEFAULT_INITIAL_CAPACITY = 16; //默认的table大小

int16_t _chashmap_addEntry(cHashMap * map, int32_t hash, void * key, void * value, int32_t bucketIndex);
void _chashmap_resize(cHashMap * map);
int32_t _tableSizeFor(int32_t cap);
int32_t _chashmap_indexFor(int32_t hash, int32_t length);
int32_t _chashmap_hash(cHashMap * map, void * key);
cHashMapEntry * _chashmap_newEntry(int32_t hash, void * key, void * value, cHashMapEntry * next);
int16_t chashmap_putVal(cHashMap * map, void * key, void * value, int16_t putIfAbcent);

cHashMap * chashmap_createBySize(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem), void * (*c_copy)(void * elem),
	void(*c_destory)(void * elem), void(*c_destoryValue)(valueType * value), int32_t initialCapacity, float loadFactor) {

	cHashMap * p = (cHashMap *)malloc(sizeof(cHashMap));
	if (!p) //分配内存失败
		return NULL;
	cMetadata *  metadata_p = (cMetadata *)malloc(sizeof(cMetadata));
	if (!metadata_p) {
		free(p);
		return NULL;
	}
	p->metaData = metadata_p;
	metadata_p->equals = c_equals;
	metadata_p->compareTo = c_compareTo;
	metadata_p->hashCode = c_hashCode;
	metadata_p->copy = c_copy;
	metadata_p->destory = c_destory;
	metadata_p->destoryValue = c_destoryValue;

	if (initialCapacity > MAXIMUM_CAPACITY)
		initialCapacity = MAXIMUM_CAPACITY;
	if (initialCapacity < 1)
		initialCapacity = DEFAULT_INITIAL_CAPACITY;
	if (loadFactor <= 0 || loadFactor >= 0.99)
		p->loadFactor = DEFAULT_LOAD_FACTOR;
	else
		p->loadFactor = loadFactor;
	p->capacity = _tableSizeFor(initialCapacity);//返回大于initialCapacity的最小2次幂
	p->threshold = (int32_t)p->capacity * p->loadFactor;
	p->numberOfElem = 0;
	if (!(p->table = (cHashMapEntry **)malloc(sizeof(cHashMapEntry *) * p->capacity))) {//初始化数组
		free(metadata_p);
		free(p);
		return NULL;
	}
	memset(p->table, '\0', sizeof(cHashMapEntry *)*p->capacity);
	p->put = chashmap_put;
	p->size = chashmap_size;
	p->get = chashmap_get;
	p->putIfAbcent = chashmap_putIfAbcent;
	p->remove = chashmap_remove;
	p->clear = chashmap_clear;
	p->destory = chashmap_destory;
	return p;
}

cHashMap * chashmap_create(uint32_t(*c_equals)(void * this, void * another),
	int32_t(*c_compareTo)(void * this, void * another), int32_t(*c_hashCode)(void * elem), void * (*c_copy)(void * elem),
	void(*c_destory)(void * elem), void(*c_destoryValue)(valueType * value)) {
	chashmap_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, c_destoryValue, DEFAULT_LOAD_FACTOR, DEFAULT_INITIAL_CAPACITY);
}

int16_t chashmap_put(cHashMap * map, void * key, void * value) {
	return chashmap_putVal(map,key,value,0);
}
int16_t chashmap_putIfAbcent(cHashMap * map, void * key, void * value) {
	return chashmap_putVal(map, key, value, 1);
}


int16_t chashmap_putVal(cHashMap * map, void * key, void * value,int16_t putIfAbcent) {
	if (!map)
		return -1;
	int32_t hash = _chashmap_hash(map, key);//键的hash值
	int32_t i = _chashmap_indexFor(hash, map->capacity);//对应的数组中的位置
	for (cHashMapEntry * e = map->table[i]; e != NULL; e = e->next){
		void * oldKey;
		if (e->hash == hash && ((oldKey = e->key) == key || !map->metaData->equals(oldKey, key))){ 
			void * oldValue = e->value;
			if (!putIfAbcent) {//覆盖旧值
				e->value = value;
				map->metaData->destoryValue(oldValue);//释放旧value的内存
				return 0;
			}
			return -1;//有冲突 不覆盖 返回失败
		}
	}
    return _chashmap_addEntry(map, hash, key, value, i);
}

void * chashmap_get(cHashMap * map, void * key) {
	if (!map)
		return NULL;
	int32_t hash = _chashmap_hash(map, key);//键的hash值
	int32_t i = _chashmap_indexFor(hash, map->capacity);//对应的数组中的位置
	for (cHashMapEntry * e = map->table[i]; e != NULL; e = e->next)
	{
		void * oldKey;
		if (e->hash == hash && ((oldKey = e->key) == key || !map->metaData->equals(oldKey, key)))
			return e->value;
	}
	return NULL;
}

int32_t chashmap_size(cHashMap * map) {
	return map->numberOfElem;
}

void * chashmap_remove(cHashMap * map, void * key){
	if (!map)
		return NULL;
	int32_t hash = _chashmap_hash(map, key);//键的hash值
	int32_t i = _chashmap_indexFor(hash, map->capacity);//对应的数组中的位置
	for (cHashMapEntry * e = map->table[i],*next,*prev = e; e != NULL; e = next)
	{
		next = e->next;
		void * oldKey;
		if (e->hash == hash && ((oldKey = e->key) == key || !map->metaData->equals(oldKey, key))) {
			prev->next = next;//将前节点的指针指向下一个节点
			if (prev == e)//本节点是链表的头结点 把数组的桶位设置为NULL
				map->table[i] == NULL;
			map->numberOfElem--;
			map->metaData->destory(e->key);//销毁key
			void * value =  e->value;//拿到要返回的value
			free(e);//清理cHashMapEntry节点
			return value;
		}
		prev = e;	
	}
	return NULL;
}

void chashmap_clear(cHashMap * map){
	if (!map)
		return;
	for (int i = 0 ; i < map->capacity; i++){
		for (cHashMapEntry * e = map->table[i], *next; e != NULL; e = next){
			next = e->next;
			map->numberOfElem--;
			if(e->key)
		    	map->metaData->destory(e->key);//销毁key
			if (e->value)
			    map->metaData->destoryValue(e->value);
			free(e);//清理cHashMapEntry节点
		}
		map->table[i] = NULL;
	}
}

void chashmap_destory(cHashMap * map){
	if (!map)
		return;
	map->clear(map);
	free(map->metaData);
	free(map->table);
	free(map);
}

//扩容 rehash
void _chashmap_resize(cHashMap * map) {
	//todo
}

int16_t _chashmap_addEntry(cHashMap * map, int32_t hash, void * key, void * value, int32_t bucketIndex) {
	cHashMapEntry * e = map->table[bucketIndex];
	cHashMapEntry * new = _chashmap_newEntry(hash, key, value, e);
	if (new)
		map->table[bucketIndex] = new;
	else
		return -1;
	if (++map->numberOfElem > map->threshold)
		_chashmap_resize(map);
	return 0;
}

cHashMapEntry * _chashmap_newEntry(int32_t hash, void * key, void * value, cHashMapEntry * next) {
	cHashMapEntry * entry = (cHashMapEntry *)malloc(sizeof(cHashMapEntry));
	if (!entry)
		return NULL;
	entry->hash = hash;
	entry->key = key;
	entry->value = value;
	entry->next = next;
	return entry;
}

int32_t _tableSizeFor(int32_t cap) {
	int n = cap - 1;
	n |= n >> 1;  //11XXXXXX..
	n |= n >> 2;  //1111XXXX..
	n |= n >> 4;  //11111111..
	n |= n >> 8;
	n |= n >> 16;
	return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

int32_t _chashmap_hash(cHashMap * map, void * key) {
	int32_t h;
	return (key == NULL) ? 0 : ((h = map->metaData->hashCode(key)) ^ (((uint32_t)h) >> 16));
}

int32_t _chashmap_indexFor(int32_t hash, int32_t length) {
	return (length - 1) & hash;
}