#include "seq.h"
int count = 1;
bool init_list(NODE **phead,int val)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	assert(tmp != NULL);

	tmp->count = count;
	tmp->start = 1;
	tmp->c = 1;
	tmp->over = val;
	tmp->size = val;
	tmp->next = NULL;
	tmp->prev = NULL;

	(*phead) = tmp;
	return true;
}

bool init_list_a(NODE *phead, int val)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	assert(tmp != NULL);

	tmp->count = count;
	tmp->start = 1;
	tmp->over = val;
	tmp->size = val;
	tmp->next = NULL;
	tmp->prev = NULL;

	phead->next = tmp;
	phead->now = tmp;
	//tmp->next = tmp;
	tmp->prev = phead;

	return true;
}

bool init_list_b(NODE *phead, int val)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	assert(tmp != NULL);

	tmp->count = count;
	tmp->start = 1;
	tmp->over = val;
	tmp->size = val;
	tmp->next = NULL;
	tmp->prev = NULL;

	phead->next = tmp;
	phead->now = tmp;
	tmp->next = tmp;
	tmp->prev = phead;

	return true;
}

NODE* get_tail(NODE *head)
{
	if (head == NULL)
	{
		return NULL;
	}

	NODE *p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}

	return p;
}

bool shen_zuo(NODE *phead, NODE *head, int n)
{
	if (phead->next == NULL)
	{
		return false;
	}

	NODE *p = phead->next;
	while (p != NULL)
	{
		if (p->size >= n)
		{
			NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
			tmp->start = p->start;
			tmp->over = n + p->start - 1;
			tmp->size = n;
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp->count = count++;

			p->start = tmp->over + 1;
			p->size -= tmp->size;

			NODE *tail = get_tail(head);
			tail->next = tmp;
			tmp->prev = tail;

			return true;
		}
		p = p->next;
	}

	printf("申请失败\n");
	return true;
}

void display_head(NODE *head)
{
	if (head->next == NULL)
	{
		printf("wu\n");
		return;
	}

	int k = 0;
	NODE *p = head->next;
	printf("块数 作业号 起始地址 终至地址 作业大小\n");
	while (p != NULL)
	{
		printf("%d %d %d %d %d\n", ++k,p->count, p->start, p->over, p->size);
		p = p->next;
	}

	return;
}

void display_phead(NODE *phead)
{
	if (phead == NULL)
	{
		printf("wu\n");
		return;
	}

	int k = 0;
	NODE *p = phead->next;
	int m = phead->c;
	printf("块号 起始地址 终至地址 作业大小\n");
	while (p != NULL)
	{
		printf("%d %d %d %d\n", ++k, p->start, p->over, p->size);
		p = p->next;
	}

	return;
}

int list_length(NODE *head)
{
	if (head == NULL)
	{
		return NULL;
	}

	int k = 0;
	NODE *p = head;
	while (p->next != NULL)
	{
		k++;
		p = p->next;
	}

	return k;
}

bool list_add(NODE *phead, NODE *tmp)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *pt = phead;
	if (phead->c == 0)
	{
		phead->next = tmp;
		tmp->prev = phead;

		return true;
	}

	int m = phead->c;
	while (m--)
	{
		NODE *pt1 = pt;
		pt = pt->next;

		if (pt->start > tmp->over)
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
			tmp->prev = pt;
			break;
		}
	}
	return true;
}
bool list_add2(NODE *phead, NODE *tmp)
{
	if (phead == NULL)
	{
		return false;
	}

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

		if (pt->start > tmp->over)
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
			tmp->prev = pt;
			break;
		}
	}
	return true;
}

bool list_add1(NODE *phead, NODE *tmp)
{
	if (phead == NULL)
	{
		return false;
	}

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

		if (pt->size > tmp->size)
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
			tmp->prev = pt;
			break;
		}
	}
	return true;
}
bool list_add4(NODE *phead, NODE *tmp)
{
	if (phead == NULL)
	{
		return false;
	}

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

		if (pt->size <= tmp->size)
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
			tmp->prev = pt;
			break;
		}
	}
	return true;
}
void delete_zuo(NODE *phead, NODE *head, int n)
{
	if (head->next == NULL || n <= 0 || n > list_length(head))
	{
		printf("error\n");
	}

	NODE *p = head->next;
	n--;
	while (n)
	{
		p = p->next;
		n--;
	}

	p->prev->next = p->next;
	if (p->next != NULL)
	{
		p->next->prev = p->prev;
	}
	

	list_add2(phead, p);

}

void kong_s(NODE *phead)
{
	if (phead->next == NULL)
	{
		return;
	}

	NODE *p = phead->next;
	int m = phead->c;
	while (m--)
	{
		if ((p->next != NULL) && (p->over == p->next->start - 1))
		{
			p->size += p->next->size;
			p->over = p->next->over;
			NODE *pt = p->next;
			p->next = pt->next;
			pt->next->prev = p;
			free(pt);
		}
		p = p->next;
	}
}

bool first_fit(NODE *phead, NODE *head, NODE *hd)
{
	if (phead == NULL)
	{
		return false;
	}
	while (1)
	{
		printf("申请作业-1 释放作业-2 展示已用空间-3 展示空闲空间-4 退出-5\n");
		int ch; 
		scanf("%d", &ch);
		if (ch == 1)
		{
			int n;
			printf("作业大小\n");
			scanf("%d", &n);
			shen_zuo(phead, head, n);
		}
		else if (ch == 2)
		{
			int n;
			printf("作业号\n");
			scanf("%d", &n);
			delete_zuo(phead, head, n);
			kong_s(phead);
		}
		else if (ch == 3)
		{
			display_head(head);
		}
		else if (ch == 4)
		{
			display_phead(phead);
		}
		else if (ch == 5)
		{
			break;
		}
	}
	return true;
}

bool shen_zuo1(NODE *phead, NODE *head, int n)
{
	if (phead->next == NULL)
	{
		return false;
	}

	NODE *p = phead->now;
	int m = phead->c;
	while (m--)
	{
		if (p->size >= n)
		{
			NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
			tmp->start = p->start;
			tmp->over = n + p->start - 1;
			tmp->size = n;
			tmp->next = NULL;
			tmp->prev = NULL;
			tmp->count = count++;

			p->start = tmp->over + 1;
			p->size -= tmp->size;

			phead->now = p;

			NODE *tail = get_tail(head);
			tail->next = tmp;
			tmp->prev = tail;

			return true;
		}
		p = p->next;
	}

	printf("申请失败\n");
	return true;
}

void delete_zuo1(NODE *phead, NODE *head, int n)
{
	if (head->next == NULL || n <= 0 || n > list_length(head))
	{
		printf("error\n");
	}

	NODE *p = head->next;
	n--;
	while (n)
	{
		p = p->next;
		n--;
	}

	p->prev->next = p->next;
	if (p->next != NULL)
	{
		p->next->prev = p->prev;
	}

	phead->c++; 
	list_add(phead, p);
}

bool next_fit(NODE *phead, NODE *head)
{
	if (phead == NULL)
	{
		return false;
	}
	while (1)
	{
		printf("申请作业-1 释放作业-2 展示已用空间-3 展示空闲空间-4 退出-5\n");
		int ch;
		scanf("%d", &ch);
		if (ch == 1)
		{
			int n;
			printf("作业大小\n");
			scanf("%d", &n);
			shen_zuo1(phead, head, n);
		}
		else if (ch == 2)
		{
			int n;
			printf("作业号\n");
			scanf("%d", &n);
			delete_zuo1(phead, head, n);
			kong_s(phead);
		}
		else if (ch == 3)
		{
			display_head(head);
		}
		else if (ch == 4)
		{
			display_phead(phead);
		}
		else if (ch == 5)
		{
			break;
		}
	}
	return true;
}

void xu_s(NODE *phead)
{
	NODE *tmp = phead->next;
	phead->next = NULL;
	while (tmp != NULL)
	{
		NODE *p2 = tmp;
		tmp = tmp->next;
		p2->next = NULL;
		
		list_add1(phead, p2);
		
	}
}
void xu_s1(NODE *phead)
{
	NODE *tmp = phead->next;
	phead->next = NULL;
	while (tmp != NULL)
	{
		NODE *p2 = tmp;
		tmp = tmp->next;
		p2->next = NULL;

		list_add4(phead, p2);

	}
}
bool best_fit(NODE *phead, NODE *head)
{
	if (phead == NULL)
	{
		return false;
	}
	while (1)
	{
		printf("申请作业-1 释放作业-2 展示已用空间-3 展示空闲空间-4 退出-5\n");
		int ch;
		scanf("%d", &ch);
		if (ch == 1)
		{
			int n;
			printf("作业大小\n");
			scanf("%d", &n);
			shen_zuo(phead, head, n);
		}
		else if (ch == 2)
		{
			int n;
			printf("作业号\n");
			scanf("%d", &n);
			delete_zuo(phead, head, n);
			kong_s(phead);
			xu_s(phead);
		}
		else if (ch == 3)
		{
			display_head(head);
		}
		else if (ch == 4)
		{
			display_phead(phead);
		}
		else if (ch == 5)
		{
			break;
		}
	}
	return true;
}

bool best_fit1(NODE *phead, NODE *head)
{
	if (phead == NULL)
	{
		return false;
	}
	while (1)
	{
		printf("申请作业-1 释放作业-2 展示已用空间-3 展示空闲空间-4 退出-5\n");
		int ch;
		scanf("%d", &ch);
		if (ch == 1)
		{
			int n;
			printf("作业大小\n");
			scanf("%d", &n);
			shen_zuo(phead, head, n);
		}
		else if (ch == 2)
		{
			int n;
			printf("作业号\n");
			scanf("%d", &n);
			delete_zuo(phead, head, n);
			kong_s(phead);
			xu_s1(phead);
		}
		else if (ch == 3)
		{
			display_head(head);
		}
		else if (ch == 4)
		{
			display_phead(phead);
		}
		else if (ch == 5)
		{
			break;
		}
	}
	return true;
}