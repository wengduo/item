#include"seq.h"

bool list_init(NODE **phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	*phead = tmp;
	tmp->next = NULL;
	tmp->prev = NULL;
	return true;
}

bool list_add(NODE *phead, char *p)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->date = p;
	tmp->next = NULL;
	tmp->prev = NULL;
	NODE *pt = phead;
	while (pt->next != NULL)
	{
		pt = pt->next;
	}
	pt->next = tmp;
	tmp->prev = pt;
	return true;
}

int list_length(NODE *phead)
{
	NODE *p = phead;
	int count = 0;
	while (p->next != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}

char *list_getstr(NODE *phead, int pos)
{
	if (phead == NULL || pos < 0 || pos >list_length(phead))
	{
		return NULL;
	}
	NODE *p = phead;
	while (pos >= 0)
	{
		p = p->next;
		pos--;
	}
	return p->date;
}

bool list_clear(NODE *phead)
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

bool list_destory(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	while (p->next != NULL)
	{
		NODE *p1 = p->next;
		free(p);
		p = p1;
	}
	free(p);
	free(phead);
	return true;
}

bool list_add_a(NODE *phead, char *p, int val)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->size = val;
	tmp->next = NULL;
	tmp->prev = NULL;
	strncpy_s(tmp->buff, p,strlen(p)+1);
	NODE *pt = phead;
	if (pt->next == NULL)
	{
		phead->next = tmp;
		tmp->prev = phead;
		return true;
	}
	while (pt->next != NULL)
	{
		NODE *pt1 = pt;
		pt = pt->next;
		if (strcmp(pt->buff, p) > 0)
		{
			pt1->next = tmp;
			tmp->prev = pt1;
			tmp->next = pt;
			pt->prev = tmp;
			break;
		}
		if (pt->next == NULL)
		{
			pt->next = tmp;
			tmp->prev = pt1;
			break;
		}
	}
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
		printf("%s\n", p->buff);
		p = p->next;
	}
	return true;
}
