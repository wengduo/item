#include<stdio.h>
#include<stdlib.h>

typedef int ELEM_TYPE;

typedef struct _DNODE
{
	ELEM_TYPE date;
	ELEM_TYPE vip;
	struct _DNODE *next;
}DNODE;

typedef struct _NODE
{
	ELEM_TYPE date;
	DNODE *tou;
	DNODE *next;
	DNODE *wei;
}NODE;

bool list_init(NODE **phead);

bool list_iskong(NODE *phead);

bool list_push(NODE *phead,ELEM_TYPE val,ELEM_TYPE vip);

bool list_pop(NODE *phead);

bool list_display(NODE *phead);

bool list_destory(NODE *phead);
