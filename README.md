# JContainer4C
### 一个C语言版的"Collection & Map",致力于为C语言使用者提供方便易用的类Java集合框架。
#### 使用方式
1.包含想使用的容器类型的头文件，例如要使用cLinkedList(类似Java的LinkedList) 
```c
#include "clinkedlist.h"  
```
2.自定义元素数据结构，例如 
```c 
typedef struct MyType { int x; double * num; } myType;
```
3.实现5个自定义的函数
```c
uint32_t c_equals(myType * this , myType * another);//自定义的相等规则 相等返回0 不等返回-1
int32_t c_compareTo(myType * this, myType * another);//大小规则 0表示相等 -1表示 this<another 1反之
int32_t c_hashCode(myType * elem);//hashcode值生成规则
myType * c_copy(myType * from);//拷贝函数 返回生成的副本的指针
void c_destory();//销毁函数
```
4.调用对应容器的XXX_create方法创建容器
```c
cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
 ```
5.使用得到的容器指针进行各项操作(方法调用的第一个参数必须是指针本身(类似与Java中隐式的this指针))
```c
list->addLast(list, elem1);
list->clear(list);
list->destory(list);
......
```
6.下面是一个小例子
```c
#include <stdio.h>
#include <stdlib.h>
#include "clinkedlist.h"

typedef struct MyType { int x; double * num; } myType; //自定义的元素类型
uint32_t c_equals(myType * this , myType * another);//自定义的相等规则
int32_t c_compareTo(myType * this, myType * another);//大小规则
int32_t c_hashCode(myType * elem);//hashcode值生成规则
myType * c_copy(myType * from);//拷贝函数
void c_destory();//销毁函数

int main(int argc, char** args) {
    //创建LinkedList 失败则返回NULL
   cLinkedList * list = clinkedlist_create(c_equals, c_compareTo, c_hashCode, c_copy, c_destory);
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
      list->destory(list);
   }
}
//其他4个自定义方法的实现省略
void c_destory(myType * elem) {
	free(elem->num);
	free(elem);
}

```
