#ifndef USER_DEFINE_H
#define USER_DEFINE_H
#include <stdint.h>

//�û��Զ��庯�����������
typedef struct MyType { int x; double * num; } myType; //�Զ����Ԫ������
typedef struct MyMapValueType { char name; } valueType; //�Զ����Ԫ������
int32_t c_equals(myType * this, myType * another);//�Զ������ȹ���
int32_t c_compareTo(myType * this, myType * another);//��С�ȽϹ��� ��this<another ����-1 this>another ����1 ��ȷ���0
int32_t c_hashCode(myType * key);//hashcodeֵ���ɹ���
myType * c_copy(myType * from);//��������
void c_destory(myType * elem);//���ٺ���(����Mapʱ����ᱻ��������key)
void c_destoryValue(valueType * value);//��������map��value�����ٺ���

typedef int c_boolean ;
#define c_TRUE 1;
#define c_FALSE 0;


typedef struct cmetadata {
	int32_t(*equals)(void * this, void * another);//�Զ������ȹ���
	int32_t(*compareTo)(void * this, void * another);//��С����
	int32_t(*hashCode)(void * elem);//hashcodeֵ���ɹ���
	void * (*copy)(void * from);//��������
	void(*destory)(void * from);//���ٺ���
	void (*destoryValue)(valueType * value);//��������map��value�����ٺ���
}cMetadata;

#endif