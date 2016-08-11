#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _NODE
{
	void *date;
	_NODE *next;
	_NODE *prev;
}NODE;

bool list_init(NODE *phead);

int list_length(NODE *phead);

bool list_display(NODE *phead, void (*print)(void *date,char ps),char ps);

bool list_iskong(NODE *phead);

bool list_insert(NODE *phead, int pos, void *val);

bool list_delete(NODE *phead, int pos);

int list_dizhi(NODE *phead, void *val, bool (*mycompare)(void *date, void *val, char ps), char ps);

bool list_display(NODE *phead,char s);

bool list_destory(NODE *phead);
