#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct _NODE
{
	int count;
	int start;
	int over;
	int size;
	int c;
	_NODE *now;
	_NODE *next;
	_NODE *prev;
}NODE;

bool init_list(NODE **phead,int n);

bool init_list_a(NODE *phead, int n);

bool first_fit(NODE *phead, NODE *head, NODE *hd);

bool next_fit(NODE *phead, NODE *head);

bool init_list_b(NODE *phead, int n);

bool best_fit(NODE *phead, NODE *head);

bool best_fit1(NODE *phead, NODE *head);