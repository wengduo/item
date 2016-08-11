#include"seq.h"


bool list_init(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	phead->next = NULL;
	phead->prev = NULL;
	phead->date = 0;
	return true;
}

bool list_kong(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	return phead->next == NULL;
}

bool list_push(NODE *phead, ELEM_TYPE val)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->date = val;
	if (phead->next == NULL)
	{
		phead->next = tmp;
		tmp->prev = phead;
		return true;
	}
	tmp->next = phead->next;
	phead->next->prev = tmp;
	tmp->prev = phead;
	phead->next = tmp;
	return true;
}

bool list_pop(NODE *phead, ELEM_TYPE *e)
{
	if (phead == NULL||phead->next == NULL)
	{
		return false;
	}
	*e = phead->next->date;
	NODE *p = phead->next;
	phead->next = phead->next->next;
	free(p);
	if (phead->next != NULL)
	{
		phead->next->prev = phead;
	}
	return true;
}

int list_length(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

bool list_destory(NODE *phead)
{
	if (phead->next == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	while (p->next != NULL)
	{
		p = p->next;
		free(p->prev);
	}
	free(p);
	phead->next = NULL;
	return true;
}

bool list_display(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	while (p != NULL)
	{
		printf("%d ", p->date);
		p = p->next;
	}
	return true;
}