#include"seq.h"
//#include<vld.h>

int main()
{
	NODE p;
	list_init(&p);
	list_push(&p, 6);
	list_push(&p, 5);
	list_push(&p, 8);
	list_push(&p, 9);
	list_display(&p);
	ELEM_TYPE e = 0;
	list_pop(&p, &e);
	printf("%d ", e);
	list_destory(&p);
	return 0;
}