#include <stdio.h>
#include <stdlib.h>
#include "clinkedlist.h"
#include "user_define.h"

//测试相关声明
void test_Creat_Add_Size();
void test_Get();
void test_Clear();
void test_Remove();
void test_Set();
void test_IndexOf();
void test_Destory();
void test_leak();


//int main(int argc, char** args) {
//	test_leak();
//	_CrtDumpMemoryLeaks();
//}

cLinkedList * help_creat_list() {
	cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);//创建LinkedList 失败则返回NULL
	if (list) {
		myType * elem1 = (myType *)malloc(sizeof(myType));
		myType * elem2 = (myType *)malloc(sizeof(myType));
		myType * elem3 = (myType *)malloc(sizeof(myType));
		elem1->x = 1;
		elem2->x = 2;
		elem3->x = 3;
		elem1->num = (double *)malloc(sizeof(double));
		elem2->num = (double *)malloc(sizeof(double));
		elem3->num = (double *)malloc(sizeof(double));
		*elem1->num = 100.0;
		*elem2->num = 200.0;
		*elem3->num = 300.0;
		//依次添加3个对象 3/300 1/100 2/200
		list->addLast(list, elem1);
		list->addLast(list, elem2);
		list->addFirst(list, elem3);
	}
	return list;
}

void test_leak() {
	cLinkedList * list = help_creat_list();
	for (int i = 1; i < 10000; i++)
	{
		myType * elem = (myType *)malloc(sizeof(myType));
		elem->x = i;
		elem->num = (double *)malloc(sizeof(double));
		*elem->num = i*10.0;
		list->addLast(list, elem);
	}
	list->destory(list);
}

void help_iterater_list(cLinkedList * list) {
	int size = list->size(list);
	for (int i = 0; i <size ; i++)
	{
		myType * elem = (myType*)(list->get(list, i));
		printf("elem_%d  : x=%d , num=%.1f\n", i+1,elem->x,*elem->num);
	}
}


void test_Destory() {
	cLinkedList * list = help_creat_list();
	if (list) 
		clinkedlist_destory(list);
}

void test_IndexOf() {
	cLinkedList * list = help_creat_list();
	if (list) {
		myType * elem1 = (myType *)malloc(sizeof(myType));
		myType * elem2 = (myType *)malloc(sizeof(myType));
		myType * elem3 = (myType *)malloc(sizeof(myType));
		myType * elem4 = (myType *)malloc(sizeof(myType));
		elem1->x = 1;
		elem2->x = 2;
		elem3->x = 3;
		elem4->x = 4;
		elem1->num = (double *)malloc(sizeof(double));
		elem2->num = (double *)malloc(sizeof(double));
		elem3->num = (double *)malloc(sizeof(double));
		elem4->num = (double *)malloc(sizeof(double));
		*elem1->num = 100.0;
		*elem2->num = 200.0;
		*elem3->num = 300.0;
		*elem4->num = 400.0;

		printf("%d\n",list->indexOf(list, elem2));//2
		printf("%d\n",list->indexOf(list, elem3));//0
		printf("%d\n",list->indexOf(list, elem1));//1
		printf("%d\n", list->indexOf(list, elem4));//-1

		elem1->x = 2;
		printf("%d\n", list->indexOf(list, elem1));//-1
		*elem2->num = 300.0;
		printf("%d\n", list->indexOf(list, elem2));//-1

		list->set(list, 1, elem4);
		printf("%d\n", list->indexOf(list, elem4));//1
	}
}

void test_Set() {
	cLinkedList * list = help_creat_list();
	if (list) {
		help_iterater_list(list);

		myType * elem = (myType *)malloc(sizeof(myType));
		elem->x = 4;
		elem->num = (double *)malloc(sizeof(double));
		*elem->num = 400.0;
		myType * old = (myType *)list->set(list,2,elem);
		printf("oldElem : x=%d , num=%.1f\n", old->x, *old->num);

		help_iterater_list(list);
	}
}

void test_Remove() {
	cLinkedList * list = help_creat_list();
	if (list) {
		/*测试删除头元素
		list->remove(list,0);
		help_iterater_list(list);
		*/
		

		/*测试删除尾元素
		list->remove(list, 2);
		help_iterater_list(list); //3/300 1/100
		*/
		
		
		/*测试删除中间元素
		list->remove(list, 1);
	    help_iterater_list(list);
		*/

		/*测试传入错误的index
		list->remove(list, 3);
		help_iterater_list(list);
		*/

		/*测试删除空链表
		cLinkedList * list1 = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
		list->remove(list1, -1);
		list->remove(list1, 1);
		help_iterater_list(list1);
		*/

		//测试删除指定元素
		myType * elem = (myType *)malloc(sizeof(myType));
		elem->x = 3;
		elem->num = (double *)malloc(sizeof(double));
		*elem->num = 300.0;
		list->removeElem(list, elem);
		help_iterater_list(list);

	}

}

void test_Creat_Add_Size() {
	cLinkedList * list = clinkedlist_create(c_equals,c_compareTo,c_hashCode, c_copy, c_destory);//创建LinkedList 失败则返回NULL
	if (list) {
		double num = 9.99999; 
		double num1 = 8.88888;
		myType value1;  //创建3个对象
		value1.x = 100;
		value1.num = &num;
		myType value2;
		value2.x = 99;
		myType value3;
		value3.x = 98;
		value3.num = &num1;
		//依次添加3个对象
		list->addLast(list, &value1);
		list->addLast(list, &value2);
		list->addFirst(list, &value3);
		//拿到链表的第一个节点，看看是否正确添加，因为暂时还没实现get()函数
		printf("%d\n", ((myType*)(list->head->elem))->x); // 98
		printf("%.5f\n", *(((myType*)(list->head->elem))->num)); //8.8888
		printf("%d\n", list->size(list)); //测试size()是否成功  3
	}
}

void test_Clear() {
	cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);//创建LinkedList 失败则返回NULL
	if (list) {
		myType * elem1 = (myType *)malloc(sizeof(myType));
		myType * elem2 = (myType *)malloc(sizeof(myType));
		myType * elem3 = (myType *)malloc(sizeof(myType));
		elem1->x = 1;
		elem2->x = 2;
		elem3->x = 3;
		elem1->num = (double *)malloc(sizeof(double));
		elem2->num = (double *)malloc(sizeof(double));
		elem3->num = (double *)malloc(sizeof(double));
		*elem1->num = 100.0;
		*elem2->num = 200.0;
		*elem3->num = 300.0;
		//依次添加3个对象
		list->addLast(list, elem1);
		list->addLast(list, elem2);
		list->addFirst(list, elem3);

		printf("%d\n", list->size(list)); //3
		myType * elem = (myType *)list->get(list,1);
		printf("%d : %.1f\n", elem->x,*elem->num );//1 100.0
		list->clear(list);
		printf("%d\n", list->size(list)); //0
	
	}
}

void test_Get(){
	cLinkedList * list = help_creat_list();
	if (list) {
		//取出对象
		int index = 0;
		myType * elem = (myType *)list->get(list, index);
		if (!elem) {
			printf("totally %d , get no.%d element failed\n", list->size(list), index + 1);
		}else {
			printf("x = %d\n", elem->x);
		}
		//下面的测试会失败
		index = 3;
		elem = (myType *)list->get(list, index);
		if (!elem) {
			printf("totally %d , get no.%d element failed\n", list->size(list), index + 1);
		}else {
			printf("x = %d\n", elem->x);
		}

		//下面的测试会失败
		index = -1;
		elem = (myType *)list->get(list, index);
		if (!elem) {
			printf("totally %d , get no.%d element failed\n", list->size(list), index + 1);
		}else {
			printf("x = %d\n", elem->x);
		}
	}

}

