#include "LINK_LIST.h"

//初始化单链表
bool InitList(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}
	phead->coef = 0;
	phead->expn = 0;

	phead->next = NULL;

	return true;
}
//销毁单链表
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
	return true;
}
//内部函数申请新的成员
static NODE *AllocNode(int coef, int expn)
{
	NODE *tmp = (NODE*)malloc(sizeof(NODE));
	tmp->coef = coef;
	tmp->expn = expn;
	tmp->next = NULL;

	return tmp;
}
//内部函数查找单链表是否存在此指数
static NODE *Search(NODE *phead, int key)
{
	NODE *tmp = phead->next;

	while (tmp != NULL)
	{
		if (tmp->expn == key)
		{
			return tmp;
		}
		tmp = tmp->next;
	}

	return NULL;
}
//单链表做顺序式的插入
void Insert(NODE *phead, int coef, int expn)
{
	NODE *p;
	phead->coef++;
	if ((p = Search(phead, expn)) != NULL)
	{
		p->coef += coef;
		return;
	}

	NODE *tmp = AllocNode(coef, expn);
	NODE *s = phead;
	p = phead->next;
	while (p != NULL)
	{
		if (p->expn > expn)
		{
			break;
		}
		s = p;
		p = p->next;
	}

	tmp->next = s->next;
	s->next = tmp;
}