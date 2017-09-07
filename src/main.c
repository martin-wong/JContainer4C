#include <stdio.h>
#include <stdlib.h>
#include "chashmap.h"
#include "user_define.h"
#include <assert.h>
#include "clinkedlist.h"


#define CRTDBG_MAP_ALLOC //¸¨Öú¼ì²âÄÚ´æÐ¹Â©µÄºê

myType * _new_Key(int num);
valueType * _new_Value(char c);

//int main(int argc, char** args) {
//	//_CrtSetBreakAlloc(75);
//	
//	//´´½¨ÈÝÆ÷
//	int initialCapacity = 100; float loadFactory = 0.6;
//	cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
//	cHashMap * map = chashmap_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, c_destoryValue, initialCapacity, loadFactory);
//	
//	//Ê¹ÓÃÈÝÆ÷
//	list->addLast(list, _new_Key(1));
//	list->addFirst(list, _new_Key(2));
//	myType * elem = list->get(list, 0);
//
//	myType * key = _new_Key(10);
//	map->put(map, key,_new_Value('A'));
//	map->put(map, NULL, _new_Value('B'));
//	valueType * value = map->get(map, key);
//
//	//Ïú»ÙÈÝÆ÷
//	list->destory(list);
//	map->destory(map);
//	
//	//_CrtDumpMemoryLeaks();
//}

//myType * _new_Key(int num) {
//	myType * elem = (myType *)malloc(sizeof(myType));
//	elem->x = num;
//	elem->num = (double *)malloc(sizeof(double));
//	*elem->num = num*10.0;
//	return elem;
//}
//
//valueType * _new_Value(char c) {
//	valueType * elem = (valueType *)malloc(sizeof(valueType));
//	elem->name = c;
//	return elem;
//}