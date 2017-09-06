#include <stdio.h>
#include <stdlib.h>
#include "chashmap.h"
#include "user_define.h"
#include <assert.h>


#define CRTDBG_MAP_ALLOC //辅助检测内存泄漏的宏

cHashMap * chashmap_help_create(int initialCapacity, float loadFactory);
void chashmap_test_put(cHashMap * map, int numbersOfElem);
void chashmap_test_remove();
void chashmap_test_get();
void chashmap_test_clear();
void chashmap_test_leaks();

void chashmap_showValue(valueType * value);

int main(int argc, char** args) {
   //_CrtSetBreakAlloc(75);
	chashmap_test_leaks();
	//_CrtDumpMemoryLeaks();	
}

cHashMap * chashmap_help_create(int initialCapacity , float loadFactory) {
	return chashmap_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory,c_destoryValue, initialCapacity, loadFactory);
}

void chashmap_test_leaks() {
	cHashMap * map = chashmap_help_create(1000, 0.7);
	chashmap_test_put(map, 1000);
	map->put(map, NULL, NULL);
	map->destory(map);
}

void chashmap_test_clear() {

	cHashMap * map = chashmap_help_create(10, 0.2);
	chashmap_test_put(map, 54);
	map->put(map, NULL, NULL);
	assert(map->size(map) == 55);

	map->clear(map);
	assert(map->size(map) == 0);

	chashmap_test_put(map, 10);
	assert(map->size(map) == 10);

}

void chashmap_test_remove() {

	cHashMap * map = chashmap_help_create(100,0.2);
	chashmap_test_put(map,13);

	myType * key = (myType *)malloc(sizeof(myType));
	key->x = 2;
	key->num = (double *)malloc(sizeof(double));
	*key->num = 20.0;

	assert(map->get(map, key) != NULL);
	valueType * value = map->remove(map, key);
	assert(value->name == 50 , map->size(map) == 1);
	assert(map->size(map) == 12);
	assert(map->get(map,key)==NULL);

}

void chashmap_test_put(cHashMap * map,int numbersOfElem) {
	for (int i = 1; i < numbersOfElem + 1; i++)
	{
		myType * key = (myType *)malloc(sizeof(myType));
		key->x = i;
		key->num = (double *)malloc(sizeof(double));
		*key->num = i*10.0;

		valueType * value = (valueType *)malloc(sizeof(valueType));
		value->name = i+48;
		map->put(map, key,value);
	}
}

void chashmap_test_get() {
	cHashMap * map = chashmap_help_create(100,0.75);
	map->put(map, NULL, NULL);
	chashmap_test_put(map,200);
	map->put(map, NULL, NULL);

	myType * key = (myType *)malloc(sizeof(myType));
	key->x = 8;
	key->num = (double *)malloc(sizeof(double));
	*key->num = 80.0;

	valueType * value = map->get(map, key);
	assert(value->name == 56);

	value = (valueType *)malloc(sizeof(valueType));
	value->name = 57;
	map->put(map, key, value);
	value = map->get(map, key);
	assert(value->name == 57);

	assert(map->putIfAbcent(map, key, value) == -1);

	assert(map->get(map, NULL) == NULL);
	assert(map->size(map) == 201);

}

void chashmap_showValue(valueType * value) {
	printf("%c\n",value->name);
}