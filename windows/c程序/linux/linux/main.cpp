#include"seq.h"
#include<vld.h>

	//pwd rm file1.c clear mkdir date.c file1.h.ls cat ..su su.c
	//	//mkdir.c touch.c rm.c date cat.c touch ll clear.c pwd.c ls.c
int main()
{
	NODE *phead;
	list_init(&phead);

	list_add_a(phead, "1", 0);
	list_add_a(phead, "file1.c", 0);
	list_add_a(phead, "clear", 0);
	list_add_a(phead, "mkdir", 0);
	list_add_a(phead, "date.c", 0);
	list_add_a(phead, "file.h", 0);
	list_add_a(phead, "ls",0);
	list_add_a(phead, "ls.c", 0);
	list_add_a(phead, ".", 0);
	list_add_a(phead, "..", 0);
	list_add_a(phead, "2", 0);
	list_add_a(phead, "su", 0);
	list_add_a(phead, "7", 0);
	list_add_a(phead, "pwd.c", 0);
	list_add_a(phead, "6", 0);
	list_add_a(phead, "rm.c", 0);
	list_add_a(phead, "clear.c", 0);
	list_add_a(phead, "3", 0);
	list_add_a(phead, "mkdir", 0);
	list_add_a(phead, "4", 0);
	list_add_a(phead, "5", 0);
	list_add_a(phead, "clear", 0);
	list_add_a(phead, "10", 0);
	list_add_a(phead, "mkdir", 0);
	list_add_a(phead, "20", 0);
	list_add_a(phead, "file.h", 0);
	list_add_a(phead, "mkdir", 0);
	list_add_a(phead, "9", 0);
	list_add_a(phead, "file.h", 0);
	list_display(phead);
	list_destory(phead);
	return 0;
}