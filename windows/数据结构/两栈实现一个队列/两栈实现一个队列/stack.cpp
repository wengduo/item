#include "stack.h"
bool InitStack(LINK_STACK *phead)
{
	phead->length = 0;
	phead->top = NULL;

	return true;
}

NODE *AllocNode(ELEM_TYPE val)
{
	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	if (tmp == NULL)
	{
		printf("½áµãÉêÇëÊ§°Ü\n");
		return false;
	}
	tmp->data = val;
	tmp->next = NULL;

	return tmp;
}

bool Push(LINK_STACK *phead, ELEM_TYPE val)
{
	NODE *tmp = AllocNode(val);

	tmp->next = phead->top;
	phead->top = tmp;
	phead->length++;

	return true;
}

bool IsEmpty(LINK_STACK *phead)
{
	//return phead->length == 0;
	return phead->top == NULL;
}

bool Pop(LINK_STACK *phead, ELEM_TYPE *e)
{
	if (IsEmpty(phead))
	{
		return false;
	}

	NODE *tmp = phead->top;

	*e = tmp->data;

	phead->top = tmp->next;
	free(tmp);

	phead->length--;
	return true;
}

bool GetTop(LINK_STACK *phead, ELEM_TYPE *e)
{
	if (phead == NULL)
	{
		return false;
	}
	if (IsEmpty(phead))
	{
		return false;
	}
	*e = phead->top->data;

	return true;
}

size_t GetLength(LINK_STACK *phead)
{
	return phead->length;
}

void Display(LINK_STACK *phead)
{
	NODE *tmp = phead->top;

	for (size_t i = 0; i<phead->length; i++)
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}


bool DestoryStack(LINK_STACK *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	size_t n = phead->length;
	ELEM_TYPE e;

	for (size_t i = 0; i<n; i++)
	{
		Pop(phead, &e);
	}

	return true;
}
int EnQueue(LINK_STACK *phead1, LINK_STACK *phead2, ELEM_TYPE val)
{
	Push(phead1, val);
	return  val;
}
int DeQueue(LINK_STACK *phead1, LINK_STACK *phead2, ELEM_TYPE *e)
{
	if (IsEmpty(phead2) == 1)
	{
		while (IsEmpty(phead1) == 0)
		{
			Pop(phead1, e);
			Push(phead2, *e);
		}
	}
	if (IsEmpty(phead2) == 0)
	{

	}
	Pop(phead2, e);
	return  *e;
}