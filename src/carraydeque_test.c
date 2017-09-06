#include <stdio.h>
#include "carraydeque.h"
#include "user_define.h"
#include <stdlib.h>
#include <assert.h>

#define CRTDBG_MAP_ALLOC

cArrayDeque * carraydeque_help_create_list(int numbersOfElem);
void carraydeque_test_pollFirst();
void carraydeque_test_peekFirst();
void carraydeque_help_iter(cArrayDeque * deque);
void carraydeque_test_leak();

//int main(int argc, char** args) {
//	carraydeque_test_leak();
//	_CrtDumpMemoryLeaks();
//}

cArrayDeque * carraydeque_help_create_list(int numbersOfElem) {
	cArrayDeque * deque = carraydeque_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, 6);
	if (deque) {
		if (numbersOfElem < 0)
			numbersOfElem = 0;
		for (int i = 1; i < numbersOfElem + 1; i++)
		{
			myType * elem = (myType *)malloc(sizeof(myType));
			elem->x = i;
			elem->num = (double *)malloc(sizeof(double));
			*elem->num = i*10.0;
			deque->offerLast(deque, elem);
		}
	}
	return deque;
}

void carraydeque_test_leak() {
	cArrayDeque * deque = carraydeque_help_create_list(100);
	deque->destory(deque);
}

void carraydeque_test_peekFirst() {
	cArrayDeque * deque = carraydeque_help_create_list(5);
	myType * first = deque->peekFirst(deque);
	printf("x=%d,num=%.2f\n", first->x, *first->num);
	deque->pollFirst(deque);
	first = deque->peekFirst(deque);
	printf("x=%d,num=%.2f\n", first->x, *first->num);
}

void carraydeque_test_pollFirst() {
	cArrayDeque * deque = carraydeque_help_create_list(50);
	carraydeque_help_iter(deque);
}

void carraydeque_help_iter(cArrayDeque * deque) {
	
	myType * first = NULL;
	int i = 0;
	while ((first = deque->pollFirst(deque))) {
		i++;
		printf("elem_%d:x=%d,num=%.2f\n", i, first->x, *first->num);
	}
}