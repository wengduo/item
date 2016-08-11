#include "seq.h"




bool list_init(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	
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


bool list_insert(NODE *phead, int pos, void *val)
{
	if (phead == NULL ||pos < 0||pos >list_length(phead))
	{
		return false;
	}
	NODE *tmp = (NODE *)malloc(sizeof(NODE));
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

bool list_delete(NODE *phead,int pos)
{
	if (phead == NULL ||pos < 0 ||pos >= list_length(phead))
	{
		printf("链表已经为空\n");
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

bool list_display(NODE *phead, void (*print)(void *date,char ps),char ps)
{
	if (phead == NULL)
	{
		return false;
	}
	NODE *p = phead->next;
	while (p != NULL)
	{
		print(p->date,ps);
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
	if (p == NULL)
	{
		return true;
	}
	while (p->next != NULL)
	{
		
		p = p->next;
		free(p->prev);
	}
	free(p);
	return true;
}

int list_dizhi(NODE *phead, void *val, bool(*mycompare)(void *date, void *val, char ps), char ps)
{
	if (phead == NULL)
	{
		return -1;
	}
	NODE *p = phead->next;
	int count = 0;
	while (p != NULL)
	{
		count++;
		if (mycompare(p->date, val, ps))
		{
			return count;
		}
		p = p->next;
	}
	printf("无此数\n");
	return -1;
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
			printf("类型错误\n");
			break;
		}
		p = p->next;
	}
	return true;
}

