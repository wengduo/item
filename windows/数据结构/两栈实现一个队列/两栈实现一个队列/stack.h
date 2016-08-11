#include <stdio.h>
#include <stdlib.h>

typedef char ELEM_TYPE;
typedef struct _NODE
{
	ELEM_TYPE data;
	struct _NODE *next;
}NODE;

typedef struct  _LINK_STACK
{
	size_t  length;
	struct _NODE *top;
}LINK_STACK;

bool InitStack(LINK_STACK *phead);

//bool ClearStack(LINK_STACK *s);

bool Push(LINK_STACK *phead, ELEM_TYPE val);

bool Pop(LINK_STACK *phead, ELEM_TYPE *e);

bool GetTop(LINK_STACK *phead, ELEM_TYPE *e);

bool IsEmpty(LINK_STACK *phead);

//bool IsFull(LINK_STACK *s);

size_t GetLength(LINK_STACK *phead);

void Display(LINK_STACK *phead);

bool DestoryStack(LINK_STACK *phead);

int EnQueue(LINK_STACK *phead1, LINK_STACK *phead2, ELEM_TYPE val);

int DeQueue(LINK_STACK *phead1, LINK_STACK *phead2, ELEM_TYPE *e);