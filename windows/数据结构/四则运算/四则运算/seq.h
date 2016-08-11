#include<stdio.h>
#include<stdlib.h>


typedef struct _NODE
{
	void *date;
	float size;
	_NODE *next;
	_NODE *prev;
}NODE;

bool list_init(NODE *phead);

int list_length(NODE *phead);

bool list_iskong(NODE *phead);

void *list_gettop(NODE *phead);

bool list_insert(NODE *phead, int pos, void *val,float size);

bool list_delete(NODE *phead, int pos);

bool list_display(NODE *phead, char s);

bool list_destory(NODE *phead);
