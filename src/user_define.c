#include "user_define.h"

int32_t c_equals(myType * this, myType * another) {
	if (this == another)
		return 0;
	if ((this->x == another->x))
		return 0; //相等返回0
	return -1; //不等返回负数
}

myType * c_copy(myType * from) {
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

int32_t c_compareTo(myType * this, myType * another) {

}
int32_t c_hashCode(myType * elem) {
	return	elem->x * (int32_t)(*elem->num) + elem->x * ((int32_t)(*elem->num)/3.14);
}

void c_destory(myType * elem) {
	free(elem->num);
	free(elem);
}

void c_destoryValue(valueType * value){
	free(value);
}
