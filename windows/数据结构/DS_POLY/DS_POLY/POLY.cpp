#define  _CRT_SECURE_NO_WARNINGS
#include "POLY.h"

//一元二次方程式的建立
void CreatePloy(NODE *phead)
{
	printf("请输入一元多项式的系数和指数\n");
	int coef;
	int expn;
	InitList(phead);

	while (1)
	{
		scanf("%d %d", &coef, &expn);
		if (coef == 0 && expn == 0)
		{
			break;
		}
		Insert(phead, coef, expn);
	}

	printf("多项式完成\n");
}
//展示一元二次方程式
void DisplayPoly(NODE *phead)
{
	NODE *p = phead->next;

	while (p != NULL)
	{
		printf("%dX^%d ", p->coef, p->expn);
		p = p->next;
		if (p != NULL && p->coef >= 0)
		{
			printf("+ ");
		}
	}
	printf("\n");
}
//一元多项式加法，将pb加到pa
void AddPoly(NODE *pa, NODE *pb)
{
	NODE *p = pb->next;
	while (p != NULL)
	{
		Insert(pa, p->coef, p->expn);
		p = p->next;
	}
}
//一元多项式减法，用pa-pb
void SubPoly(NODE *pa, NODE *pb)
{
	NODE *p = pb->next;
	while (p != NULL)
	{
		Insert(pa, -p->coef, p->expn);
		p = p->next;
	}
}
//一元多项式乘法,并且将结果放到pa里面
bool MulPoly(NODE *pa, NODE *pb)
{
	if (pa == NULL || pa == NULL)
	{
		return false;
	}
	NODE *paa = pa->next;
	NODE *pbb = pb->next;
	NODE headC;
	InitList(&headC);
	while (paa != NULL)
	{
		Insert(&headC, paa->coef, paa->expn);
		paa = paa->next;
	}
	DisplayPoly(&headC);
	DestoryList(pa);
	while (pbb != NULL)
	{
		NODE *pcc = headC.next;
		while (pcc != NULL)
		{
			Insert(pa, pbb->coef * pcc->coef, pcc->expn + pbb->expn);
			pcc = pcc->next;
		}
		pbb = pbb->next;
	}
	DestoryList(&headC);
	return true;
}