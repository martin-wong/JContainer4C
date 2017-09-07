#ifndef USER_DEFINE_H
#define USER_DEFINE_H
#include <stdint.h>

//用户自定义函数的相关声明
typedef struct MyType { int x; double * num; } myType; //自定义的元素类型
typedef struct MyMapValueType { char name; } valueType; //自定义的元素类型
int32_t c_equals(myType * this, myType * another);//自定义的相等规则
int32_t c_compareTo(myType * this, myType * another);//大小比较规则 若this<another 返回-1 this>another 返回1 相等返回0
int32_t c_hashCode(myType * key);//hashcode值生成规则
myType * c_copy(myType * from);//拷贝函数
void c_destory(myType * elem);//销毁函数(用于Map时，则会被用来销毁key)
void c_destoryValue(valueType * value);//用于销毁map的value的销毁函数

typedef int c_boolean ;
#define c_TRUE 1;
#define c_FALSE 0;


typedef struct cmetadata {
	int32_t(*equals)(void * this, void * another);//自定义的相等规则
	int32_t(*compareTo)(void * this, void * another);//大小规则
	int32_t(*hashCode)(void * elem);//hashcode值生成规则
	void * (*copy)(void * from);//拷贝函数
	void(*destory)(void * from);//销毁函数
	void (*destoryValue)(valueType * value);//用于销毁map的value的销毁函数
}cMetadata;

#endif