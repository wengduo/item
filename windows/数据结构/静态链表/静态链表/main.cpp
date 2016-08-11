#include"static.h"
#include<vld.h>

int main()
{
	STATICLIST s;
	list_init(s);
	list_insert(s, 2, 1);
	list_display(s);
	list_insert(s, 3, 1);
	list_display(s);
	list_insert(s, 4, 1);
	list_insert(s, 5, 2);
	list_insert(s, 7, 5);
	list_display(s);
	list_delete(s, 2);
	list_display(s);
	list_insert(s, 5, 1);
	list_display(s);
	return 0;
}