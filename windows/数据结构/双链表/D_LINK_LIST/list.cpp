
#include "list.h"
//初始化双链表头
bool InitDHead(HEAD *phead)
{
	phead->next = NULL;
	phead->prev = NULL;
	phead->data = 0;
	phead->size = 4;//初始申请空间
	phead->arr = (int **)malloc(sizeof(int *)* phead->size*2);
	return true;
}
//初始化双链表
bool InitDList(DNODE *phead)
{
	phead->next = NULL;
	phead->prev = NULL;
	return true;
}
//销毁双链表
bool DestoryDList(HEAD *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	while (--phead->data)
	{
		p = p->next;
		free(p->prev);
	}
	free(p);
	phead->next = NULL;
	free(phead->arr);
	return true;
}
static bool IsDEmpty(HEAD *phead)
{
	return phead->next == NULL;
}
//展示双链表
bool DisplayList(HEAD *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	printf("%d ", phead->data);
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	return true;
}
//双链表的头部插入
bool InsertDHead(HEAD *phead, int val)
{
	if (phead->data > phead->size)
	{
		phead->arr = (int **)realloc(phead->arr, sizeof(int *)* phead->size * 2);
		phead->size = phead->size * 2;
		printf("再次申请\n");
	}
	DNODE *tmp = (DNODE *)malloc(sizeof(DNODE));
	//printf("0x%p ", tmp);
	int k = phead->data;
	while (k)
	{
		phead->arr[k] = phead->arr[k - 1];
		k--;
	}
	phead->arr[0] = (int *)tmp;
	printf("10x%p ", phead->arr[0]);
	phead->data++;
	InitDList(tmp);
	tmp->data = val;
	tmp->next = phead->next;
	if (!IsDEmpty(phead))
	{
		phead->next->prev = tmp;
	}
	tmp->prev = (DNODE *)phead;
	phead->next = tmp;
	return true;
}
//双链表的尾部插入
bool InsertDTail(HEAD *phead, int val)
{
	if (phead == NULL)
	{
		return false;
	}
	if (phead->data > phead->size)
	{
		phead->arr = (int **)realloc(phead->arr, sizeof(int *)* phead->size * 2);
		phead->size = phead->size * 2;
		printf("再次申请\n");
	}
	DNODE *tmp = (DNODE *)malloc(sizeof(DNODE));
	phead->arr[phead->data++] = (int *)tmp;
	InitDList(tmp);
	DNODE *p = (DNODE *)phead;
	tmp->data = val;
	while (p->next != NULL)
	{
		p = p->next;
	}
	tmp->prev = p;
	p->next = tmp;
	return true;
}
//双链表的中部插入
bool InsertDByPos(HEAD *phead, int pos, int val)
{
	if (phead == NULL || pos<1 || pos>phead->data)
	{
		return false;
	}
	if (phead->data > phead->size)
	{
		phead->arr = (int **)realloc(phead->arr, sizeof(int *)* phead->size * 2);
		phead->size = phead->size * 2;
		printf("再次申请\n");
	}
	DNODE *tmp = (DNODE *)malloc(sizeof(DNODE)); 
	printf("0x%p ", tmp);
	int k = phead->data;
	while (k >= pos)
	{
		phead->arr[k] = phead->arr[k - 1];
		k--;
	}
	phead->arr[k] = (int *)tmp;
	InitDList(tmp);
	DNODE *p = (DNODE *)phead;
	tmp->data = val;
	while (pos--)
	{
		p = p->next;
	}
	tmp->prev = p->prev;
	tmp->next = p;
	p->prev->next = tmp;
	p->prev = tmp;
	return true;
}
//双链表的值删
bool DeleteWhat(HEAD *phead, int val)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	int k = 0;
	while (p != NULL)
	{
		if (p->data == val)
		{
			while (k<phead->data)
			{
				phead->arr[k] = phead->arr[k + 1];
				k++;
			}
			if (p->next == NULL)
			{
				p->prev->next = NULL;
			}
			else
			{
				p->prev->next = p->next;
				p->next->prev = p->prev;
			}
			free(p);
			phead->data--;
			return true;
		}
		p = p->next;
		k++;
	}
	return false;
}
//双链表的位置删
bool DeleteWhere(HEAD *phead, int pos)
{
	if (phead == NULL||pos<0||pos>phead->data)
	{
		return false;
	}
	int k = pos-1;
	while (k<phead->data)
	{
		phead->arr[k] = phead->arr[k+1];
		k++;
	}
	DNODE *p = phead->next;
	while (--pos)
	{
		p = p->next;
	}
	if (p->next == NULL)
	{
		p->prev->next = NULL;
	}
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p);
	phead->data--;
	return true;
}
//逆序双链表
bool fanDList(HEAD *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	phead->next->prev = NULL;
	while (p->next != NULL)
	{
		DNODE *tmp = p;
		p = p->next;
		DNODE *tmp1 = tmp->next;
		tmp->next = tmp->prev;
		tmp->prev = tmp1;
	}
	p->next = p->prev;
	p->prev = (DNODE *)phead;
	phead->next = p;
	return true;
}
//检查双链表是否有环
bool huanDList(HEAD *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	//////////////////////////////
	DNODE *s1 = (DNODE *)phead;
	DNODE *p1 = (DNODE *)phead;
	int i = 1;
	while (s1->next != NULL)            //构造有环双链表
	{
		i++;
		s1 = s1->next;
		if (i = 4)
		{
			DNODE *p1 = s1;
		}                              
	}
	s1->next = p1;
	/////////////////////////
	DNODE *p = (DNODE *)phead;
	DNODE *s = (DNODE *)phead;
	while (p != NULL||s != NULL)
	{
		if (p == s)
		{
			printf("此双链表有环\n");
			return true;
		}
		p = p->next;
		s = s->next->next;
	}
	printf("此双链表无环");
	return true;
}
//得到双链表的长度
int GetlengDList(HEAD *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	DNODE *p = phead->next;
	int count = 0;
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count;
}