#include<stdlib.h>
#include<stdio.h>
#include<vld.h>
#include "seq_list.h"


int main()
{
	int k = 0;
	bool f;
	SEQ_LIST *s = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
    s->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));
	InitSeqList(s);

	for (int i = 1; i<12; i++)
	{
		Insert(s, 0, i * 10);
		printf("%d\n",s->elem[0]);
	}

	DisplaySeqList(s);
	Delete(s, 0);
	DisplaySeqList(s);
	Delete(s, 3);
	DisplaySeqList(s);
	Delete(s, 1);
	DisplaySeqList(s);
	IsEmpty(s);
	k=GetLength(s);
	printf("%d\n", k);
	Insert(s, 2, 20);
	f=IsFull(s);
	printf("%d\n", f);
	DisplaySeqList(s);
	Delete(s, 1);
	int h=my_Search(s,  20);
	printf("%d\n", h);
	DeleteVal(s,  20);
	free(s->elem);
	free(s);
	return 0;
}

///利用顺序表的基本运算，实现如果在顺序表A 中出现的元素，在顺序表B 中也出现，则将A
///中该元素删除。
/*int main()
{
	SEQ_LIST *s = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
	s->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));///A链表
	SEQ_LIST *p = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
	p->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));///B链表
	InitSeqList(s);
	InitSeqList(p);
	for (int i = 1; i<6; i++)//初始化A链表
	{
		Insert(s, 0, i * 2);
	}
	DisplaySeqList(s);
	for (int i = 1; i<7; i++)//初始化B链表
	{
		Insert(p, 0, i);
	}
	DisplaySeqList(p);
	for (int i = 0; i < p->length; i++)
	{
		for (int j = 0; j < s->length; j++)
		{
			if (p->elem[i] == s->elem[j])
			{
				Delete(s, j);
			}
		}
	}
	DisplaySeqList(s);
	DisplaySeqList(p);
	free(s->elem);
	free(p->elem);
	free(s);
	free(p);
	return 0;
}

//2.顺序表A 和顺序表B 的元素都是非递减排列，利用线性表的基本运算，将它们合并成一个顺
//序表C，要求C 也是非递减排列。例如，A = （6，11，11，23），B = （2，10，12，12，21），
//则C = （2，6，10，11，11，12，12，21，23）。

int main()
{
	SEQ_LIST *s = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
	s->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));///A链表
	SEQ_LIST *p = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
	p->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));///B链表
	SEQ_LIST *f = (SEQ_LIST*)malloc(sizeof(SEQ_LIST)* 1);
	f->elem = (ELEM_TYPE *)malloc(sizeof(ELEM_TYPE)* (10));///C链表
	InitSeqList(s);
	InitSeqList(p);
	InitSeqList(f);
	for (int i = 20; i > 0;i--)//初始化A链表
	{
		Insert(s, 0, i * 2);
	}
	DisplaySeqList(s);
	for (int i = 7; i>0; i--)//初始化B链表
	{
		Insert(p, 0, i*10);
	}
	DisplaySeqList(p);
	int k = p->length + s->length;
	for (int j = 0; j < k; j++)
	{
		if (GetLength(p)==0)
		{
			Insert(f, j, s->elem[0]);
			Delete(s, 0);
		}
		else if(GetLength(s)==0)
		{
			Insert(f, j, p->elem[0]);
			Delete(p, 0);
		}
		else
		{
			if (p->elem[0] >= s->elem[0])
			{
				Insert(f, j, s->elem[0]);
				Delete(s, 0);
			}
			else
			{
				Insert(f, j, p->elem[0]);
				Delete(p, 0);
			}
		}
	}
	DisplaySeqList(f);
	free(s->elem);
	free(p->elem);
	free(f->elem);
	free(s);
	free(p);
	free(f);
	return 0;
}*/