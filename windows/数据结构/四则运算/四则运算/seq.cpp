#include "seq.h"




bool list_init(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	phead->size = 0;
	phead->date = NULL;
	phead->next = NULL;
	phead->prev = NULL;
	return true;
}

bool list_iskong(NODE *phead)
{
	return phead->next == NULL;
}

int list_length(NODE *phead)
{
	if (phead == NULL)
	{
		return -1;
	}
	NODE *p = phead;
	int count = 0;
	while (p->next != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}
bool list_insert(NODE *phead, int pos, void *val,float size)
{
	if (phead == NULL || pos < 0 || pos >list_length(phead))
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->size = size;
	tmp->date = val;
	tmp->next = NULL;
	tmp->prev = NULL;
	NODE *p = phead;
	if (pos == 0)
	{
		p = phead->next;
		phead->next = tmp;
		tmp->prev = phead;
		tmp->next = p;
		if (p != NULL)
		{
			p->prev = tmp;
		}
	}
	else if (pos == list_length(phead))
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = tmp;
		tmp->prev = p;
	}
	else
	{
		while (pos--)
		{
			p = p->next;
		}
		p->next->prev = tmp;
		tmp->next = p->next;
		tmp->prev = p;
		p->next = tmp;
	}
	return true;
}

bool list_delete(NODE *phead, int pos)
{
	if (phead == NULL || pos < 0 || pos >= list_length(phead))
	{
		return false;
	}
	NODE *p = phead;
	if (pos == 0)
	{
		p = p->next;
		if (p->next == NULL)
		{
			phead->next = NULL;
		}
		else
		{
			phead->next = p->next;
			p->next->prev = phead;
		}
	}
	else if (pos == list_length(phead)-1)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->prev->next = NULL;
	}
	else
	{
		while (pos--)
		{
			p = p->next;
		}
		p = p->next;
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p);
	return true;
}

void *list_gettop(NODE *phead)
{
	if (phead->next == NULL)
	{
		return NULL;
	}
	return phead->next->date;
}
bool list_display(NODE *phead, char s)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	while (p != NULL)
	{
		switch (s)
		{
		case 'i':
			printf("%d ", *(int *)p->date);
			break;
		case 'c':
			printf("%s ", *(char *)p->date);
			break;
		case 'd':
			printf("%lf ", *(double *)p->date);
			break;
		case 'f':
			printf("%f ", *(float *)p->date);
			break;
		default:
			printf("ÀàÐÍ´íÎó\n");
			break;
		}
		p = p->next;
	}
	return true;
}

bool list_destory(NODE *phead)
{
	if (phead == NULL)
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
	return true;
}

