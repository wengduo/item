#include "seq.h"




bool list_init(NODE **phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	tmp->date = 0;
	tmp->next = NULL;
	tmp->tou = NULL;
	tmp->wei = NULL;
	*phead = tmp;
	return true;
}

bool list_iskong(NODE *phead)
{
	return phead->next == NULL;
}
bool list_push(NODE *phead, ELEM_TYPE val, ELEM_TYPE vip)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *tmp = (DNODE *)malloc(sizeof(DNODE));
	tmp->date = val;
	tmp->vip = vip;
	tmp->next = NULL;
	if (phead->next == NULL)
	{
		phead->next = tmp;
		phead->tou = tmp;
		phead->wei = tmp;
		return true;
	}
	if (phead->next->vip > tmp->vip)
	{
		DNODE *pp = phead->next;
		phead->next = tmp;
		tmp->next = pp;
		phead->tou = tmp;
	}
	DNODE *p = phead->next;
	while (p->next != NULL)
	{
		DNODE *p2 = p;
		p = p->next;
		if (p->vip > tmp->vip)
		{
			p2->next = tmp;
			tmp->next = p;
			return true;
		}
	}
	p->next = tmp;
	phead->wei = tmp;
	return true;
}

bool list_pop(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	//e = &p->date;
	phead->next = p->next;
	phead->tou = p->next;
	free(p);
	return true;
}

bool list_display(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	while (p != NULL)
	{
		printf("%d ", p->date);
		//printf("\033[1;32m%d \033[0m", p->vip);
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
	DNODE *p = phead->next;
	while (p != NULL)
	{
		DNODE *p1 = p;
		p = p->next;
		free(p1);
	}
	free(phead);
	return true;
}

