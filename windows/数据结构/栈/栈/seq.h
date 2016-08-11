#include<stdio.h>
#include<stdlib.h>

typedef int ELEM_TYPE;
typedef struct _NODE
{
	ELEM_TYPE date;
	_NODE *next;
	_NODE *prev;
}NODE;

bool list_init(NODE *phead);

bool list_kong(NODE *phead);

bool list_push(NODE *phead,ELEM_TYPE val);

bool list_pop(NODE *phead, ELEM_TYPE *e);

int list_length(NODE *phead);

bool list_destory(NODE *phead);

bool list_display(NODE *phead);

