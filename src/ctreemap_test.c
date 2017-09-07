#include <stdio.h>
#include <stdlib.h>
#include "ctreemap.h"
#include "user_define.h"
#include <assert.h>


//#define CRTDBG_MAP_ALLOC //¸¨Öú¼ì²âÄÚ´æÐ¹Â©µÄºê
myType * _new_Key(int num);
valueType * _new_Value(char c);

cTreeMap * ctreemap_help_create();
void ctreemap_test_put();

int main(int argc, char** args) {
	//_CrtSetBreakAlloc(75);
	ctreemap_test_put();
	_CrtDumpMemoryLeaks();
}

cTreeMap * ctreemap_help_create() {
	return ctreemap_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, c_destoryValue);
}

void ctreemap_help_iter(cTreeMapNode * root) {
	if (!root)
		return;
	ctreemap_help_iter(root->left);
	valueType * value = (valueType*)root->value;
	if(!value)
		printf("%c ", '0');
	else
		printf("%c ", value->name);
	ctreemap_help_iter(root->right);
}

void ctreemap_test_put(){
	cTreeMap * map = ctreemap_help_create();
	printf("%d\n", map->size(map));

	for (int i = 0; i < 26; i+=2) 
		map->put(map, _new_Key(i), _new_Value('A' + i));

	for (int i = 1; i < 26; i+=2)
		map->put(map, _new_Key(i), _new_Value('A' + i));

	map->put(map, _new_Key(6), _new_Value('A' + 6)); //ÖØ¸´µÄ¼ü
	map->put(map, _new_Key(0), _new_Value('A' + 0)); //ÖØ¸´µÄ¼ü

	map->put(map, NULL, NULL); 

	ctreemap_help_iter(map->root);
	printf("%d\n", map->size(map));
}

myType * _new_Key(int num) {
	myType * elem = (myType *)malloc(sizeof(myType));
	elem->x = num;
	elem->num = (double *)malloc(sizeof(double));
	*elem->num = num*10.0;
	return elem;
}

valueType * _new_Value(char c) {
	valueType * elem = (valueType *)malloc(sizeof(valueType));
	elem->name = c;
	return elem;
}