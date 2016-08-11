#include "LINK_LIST.h"

bool InitList(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	phead->data = 0;
	phead->next = NULL;
	return true;
}

static NODE *AllocNode()
{
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
	if (tmp == NULL)
	{
		printf("½áµãÉêÇëÊ§°Ü\n");
		return NULL;
	}
	return tmp;
}

bool InsertHead(NODE *phead, ELEM_TYPE val)
{
	NODE *tmp = AllocNode();
	phead->data++;
	tmp->data = val;

	tmp->next = phead->next;
	phead->next = tmp;

	return true;
}

bool InsertZhong(NODE *phead, ELEM_TYPE val, int k)
{
	NODE *tmp = AllocNode();
	if (k < 1 || k >= phead->data)
	{
		return false;
	}
	phead->data++;
	tmp->data = val;
	NODE *p = phead;
	k--;
	while (k--)
	{
		p = p->next;
	}
	tmp->next = p->next;
	p->next = tmp;
	return true;
}
bool InsertTail(NODE *phead, ELEM_TYPE val)
{
	NODE *tmp = AllocNode();
	phead->data++;
	tmp->data = val;

	NODE *p = phead;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = tmp;
	tmp->next = NULL;

	return true;
}

void DisplayList(NODE *phead)
{
	printf("%d ", phead->data);
	NODE *p = phead->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

bool DestoryList(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *tmp = phead->next;

	while (tmp != NULL)
	{
		phead->next = tmp->next;
		free(tmp);
		tmp = phead->next;
	}
	phead->data = 0;
	return true;
}
int GetLength(NODE *phead,int n)
{
	NODE *p = phead;
	n = 0;
	while (p->next != NULL)
	{
		p = p->next;
		n++;
	}
	return n;
}
bool DeleteListWhere(NODE *phead, int k)
{
	if (phead == NULL || k <= 0 || k>GetLength(phead, k))
	{
		return false;
	}
	NODE *p = phead;
	phead->data--;
	k--;
	while (k--)
	{
		p = p->next;
	}
	NODE *tmp = p->next;
	p->next = tmp->next;
	free(tmp);
	return true;
}
bool DeleteListWhat(NODE *phead, ELEM_TYPE val)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead;
	while (p->next != NULL)
	{
		if (p->data == val)
		{
			NODE *tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			phead->data--;
			return true;
		}
		p = p->next;
	}
	return false;
}
bool FanList(NODE *phead)
{
	int k = (phead->data+1)/2;
	int n = phead->data;
	int f = phead->data;
	NODE *tmp = phead;
	NODE *tmp2 = phead;
	while (k--)
	{
		NODE *p = tmp;
		NODE *tmp1 = p->next;
		while ((--f) && (p = p->next));
		if (p->next->next == NULL)
		{
			p->next->next = tmp->next->next;
			tmp->next = p->next;
			p->next = tmp1;
			tmp1->next = NULL;
		}
		else
		{
			if (tmp->next==p)
			{
				NODE *tmp5 = p->next;
				p->next = tmp5->next;
				tmp5->next = p;
				tmp->next = tmp5;
			}
			else
			{
				NODE *tmp3 = p->next;
				NODE *tmp4 = tmp3->next;
				tmp3 = p->next;
				tmp2->next = p->next;
				tmp3->next = tmp1->next;
				p->next = tmp1;
				tmp1->next = tmp4;
			}
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
		n -= 2;
		f = n;
	}
	return true;
}