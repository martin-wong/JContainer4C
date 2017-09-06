#include <stdio.h>
#include <stdlib.h>
#include "carraylist.h"
#include "user_define.h"
#include <assert.h>

//#define CRTDBG_MAP_ALLOC //辅助检测内存泄漏的宏

cArrayList * carraylist_help_create_list(int numbersOfElem);
void carraylist_help_iterater(cArrayList * list);
void carraylist_test_add();
void carraylist_test_get();
void carraylist_test_leak();
void carraylist_test_set();
void carraylist_test_remove();
void carraylist_test_indexOf();

//int main(int argc, char** args) {
//    //_CrtSetBreakAlloc(77);
//	carraylist_test_leak();
//	_CrtDumpMemoryLeaks();
//}


cArrayList * carraylist_help_create_list(int numbersOfElem) {
	cArrayList * list = carraylist_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory,0);
	if (list) {
		if (numbersOfElem < 0)
			numbersOfElem = 0;
		for (int i = 1; i < numbersOfElem+1 ; i++)
		{
			myType * elem = (myType *)malloc(sizeof(myType));
			elem->x = i;
			elem->num = (double *)malloc(sizeof(double));
			*elem->num = i*10.0;
			list->addLast(list, elem);
		}	
	}
	return list;
}

void carraylist_test_indexOf() {
	cArrayList * list = carraylist_help_create_list(15);
	/*myType * elem = (myType *)malloc(sizeof(myType));
	elem->x = 4;
	elem->num = (double *)malloc(sizeof(double));
	*elem->num = 30.0;
	assert(list->indexOf(list, elem) == -1 );*/

	myType * elem = (myType *)malloc(sizeof(myType));
	elem->x = 3;
	elem->num = (double *)malloc(sizeof(double));
	*elem->num = 30.0;
	assert(list->indexOf(list, elem) == 2 );

}

void carraylist_test_add() {
	cArrayList * list = carraylist_help_create_list(3);

	/*头部插入
	myType * elem = (myType *)malloc(sizeof(myType));
	elem->x =3 ;
	elem->num = (double *)malloc(sizeof(double));
	*elem->num = 30.0;
	list->add(list, 0, elem);
	*/

	/*插入尾部之前
	myType * elem1 = (myType *)malloc(sizeof(myType));
	elem1->x = 100;
	elem1->num = (double *)malloc(sizeof(double));
	*elem1->num = 1000.0;
	list->add(list, 2, elem1);
	carraylist_help_iterater(list);
	*/

	//测试错误的index
	myType * elem1 = (myType *)malloc(sizeof(myType));
	elem1->x = 100;
	elem1->num = (double *)malloc(sizeof(double));
	*elem1->num = 1000.0;
	list->add(list, 3, elem1);
	carraylist_help_iterater(list);
	

}

void carraylist_test_remove() {
	cArrayList * list = carraylist_help_create_list(11);
	myType * old = list->remove(list,1);//删除第2个元素
	printf("x=%d,num=%.2f\n", old->x, *old->num);
	assert(list->size == 10);
	carraylist_help_iterater(list);
}

void carraylist_test_set() {
	cArrayList * list = carraylist_help_create_list(5);
	myType * elem = (myType *)malloc(sizeof(myType));
	elem->x = 9999;
	elem->num = (double *)malloc(sizeof(double));
	*elem->num = 999.9;
	myType *  old1 = list->set(list, 0, elem);
	printf("x=%d,num=%.2f\n", old1->x, *old1->num);
	carraylist_help_iterater(list);

	myType *  old2 = list->set(list, -1, elem);
	myType *  old3 = list->set(list, 5, elem);
	myType *  old4 = list->set(list, 2, NULL);
	assert(old2 == NULL,old3==NULL,old4==NULL);//断言
}

void carraylist_test_get() {
	cArrayList * list = carraylist_help_create_list(15);
	for (int i = 0 ; i < list->size ; i++){
		myType * elem = (myType *)list->get(list,i);
		printf("elem_%d : x=%d,num=%.2f\n",i+1,elem->x,*elem->num);
	}
}

void carraylist_test_leak() {

	//下面测试内存泄漏情况
	cArrayList * list = carraylist_help_create_list(50000);
	list->destory(list);
	
}

void carraylist_help_iterater(cArrayList * list) {
	for (int i = 0; i < list->size; i++) {
		myType * elem = (myType *)list->get(list, i);
		printf("elem_%d : x=%d,num=%.2f\n", i + 1, elem->x, *elem->num);
	}
}