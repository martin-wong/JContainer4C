#include "user_define.h"

int32_t c_equals(myType * this, myType * another) {
	if ((this->x == another->x) && ((*this->num) == (*another->num)))
		return 0; //��ȷ���0
	return -1; //���ȷ��ظ���
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


}

void c_destory(myType * elem) {
	free(elem->num);
	free(elem);
}