#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE
{
	int coef;
	int expn;
	struct _NODE *next;
}NODE;


bool InitList(NODE *phead);

void Insert(NODE *phead, int coef, int expn);

bool DestoryList(NODE *phead);