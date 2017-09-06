# JContainer4C
### 一个C语言版的"Collection & Map",致力于为C语言使用者提供方便易用的类Java集合框架。
#### 使用方式
1.包含想使用的容器类型的头文件，例如要使用cLinkedList(类似Java的LinkedList) 
```c
#include "clinkedlist.h"  
```
2.自定义元素数据类型，例如：
```c 
//使用list及queue类型的容器，自定义一个元素类型即可
typedef struct MyType { int x; double * num; } myType; //自定义的元素类型(也用于Map的键的类型)
//如果使用Map则还需要自定义一个"Value"的类型，例如： 
typedef struct MyMapValueType { char name; } valueType; //自定义的Map值的元素类型
```
3.实现5个自定义的函数(要使用Map则是6个)
```c
int32_t c_equals(myType * this, myType * another);//自定义的相等规则
int32_t c_compareTo(myType * this, myType * another);//大小规则
int32_t c_hashCode(myType * key);//hashcode值生成规则
myType * c_copy(myType * from);//拷贝函数
void c_destory(myType * elem);//销毁函数(用于Map时，则会被用来销毁key)
void c_destoryValue(valueType * value);//用于销毁map的value的销毁函数
```
4.调用对应容器的XXX_create方法注册自定义函数，并创建容器
```c
cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
 ```
5.使用得到的容器指针进行各项操作，方法调用的第一个参数必须是指针本身(类似与Java中隐式的this指针)
```c
list->addLast(list, elem1);
list->clear(list);
list->destory(list); //完全销毁容器 释放所有申请的内存
......
```
6.下面是一个小例子
```c
#include <stdio.h>
#include <stdlib.h>
#include "chashmap.h"
#include "clinkedlist.h"

typedef struct MyType { int x; double * num; } myType; //自定义的元素类型
typedef struct MyMapValueType { char name; } valueType; //自定义的元素类型

uint32_t c_equals(myType * this , myType * another);//自定义的相等规则
int32_t c_compareTo(myType * this, myType * another);//大小规则
int32_t c_hashCode(myType * elem);//hashcode值生成规则
myType * c_copy(myType * from);//拷贝函数
void c_destory();//销毁函数
void c_destoryValue(valueType * value);


myType * _new_Key(int num);
valueType * _new_Value(char c);

int main(int argc, char** args) {
	
	//创建容器
	int initialCapacity = 100; float loadFactory = 0.6;
	cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
	cHashMap * map = chashmap_createBySize(c_equals, c_compareTo, c_hashCode, c_copy, c_destory, c_destoryValue, initialCapacity, loadFactory);
	
	//使用容器
	list->addLast(list, _new_Key(1));
	list->addFirst(list, _new_Key(2));
	myType * elem = list->get(list, 0);

	myType * key = _new_Key(10);
	map->put(map, key,_new_Value('A'));
	map->put(map, NULL, _new_Value('B'));
	valueType * value = map->get(map, key);

	//销毁容器
	list->destory(list);
	map->destory(map);
	
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

//下面是自定义方法的例子
int32_t c_equals(myType * this, myType * another) {
	if (this == another)
		return 0;
	if ((this->x == another->x))
		return 0; //相等返回0
	return -1; //不等返回负数
}

myType * c_copy(myType * from) { //深拷贝
	myType * to = (myType *)malloc(sizeof(myType));
	if (!to)
		return NULL;
	to->x = from->x;
	to->num = (double *)malloc(sizeof(double));
	if (!to->num) {
		free(to);
		return NULL;
	}
	*to->num = *from->num;
	return to;
}

int32_t c_hashCode(myType * elem) { //随便写的....
	return	elem->x * (int32_t)(*elem->num) + elem->x * ((int32_t)(*elem->num)/3.14);
}

void c_destory(myType * elem) { //因为保证加入容器的对象是malloc出来的 所以这里的销毁逻辑就是free
	free(elem->num);       //销毁逻辑因你产生对象方式的不同而决定
	free(elem);
}

void c_destoryValue(valueType * value){
	free(value);
}

```
