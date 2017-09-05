#ifndef USER_DEFINE_H
#define USER_DEFINE_H
#include <stdint.h>

//�û��Զ��庯�����������
typedef struct MyType { int x; double * num; } myType; //�Զ����Ԫ������
int32_t c_equals(myType * this, myType * another);//�Զ������ȹ���
int32_t c_compareTo(myType * this, myType * another);//��С����
int32_t c_hashCode(myType * elem);//hashcodeֵ���ɹ���
myType * c_copy(myType * from);//��������
void c_destory(myType * elem);//���ٺ���

typedef struct cmetadata {
	int32_t(*equals)(void * this, void * another);//�Զ������ȹ���
	int32_t(*compareTo)(void * this, void * another);//��С����
	int32_t(*hashCode)(void * elem);//hashcodeֵ���ɹ���
	void * (*copy)(void * from);//��������
	void(*destory)(void * from);//���ٺ���
}cMetadata;

#endif