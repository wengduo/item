#include<stdio.h>
#include<stdlib.h>

typedef struct _NODE
{
	int date;
	_NODE *next;
	_NODE *prev;
}NODE;

bool list_init(NODE *phead);

bool list_kong(NODE *phead);

bool list_push(NODE *phead, int val);

bool list_pop(NODE *phead, int *e);

int list_length(NODE *phead);

bool list_destory(NODE *phead);

bool list_display(NODE *phead);
