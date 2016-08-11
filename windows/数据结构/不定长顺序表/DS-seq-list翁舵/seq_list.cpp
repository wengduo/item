#include "seq_list.h"
#include <stdio.h>
#include<stdlib.h>
////////构造一个空链表////////
bool InitSeqList(SEQ_LIST *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->length = 0;
	p->TotalLength = 5;
	p->n = 10;
	return true;
}
////////销毁线性链表////////////
bool DetorySeqList(SEQ_LIST *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->length = 0;
	return true;
}
////////对链表进行清空///////////
bool ClearSeqList(SEQ_LIST *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->length = 0;
	return true;
}
////////看当前链表是否为空///////
bool IsEmpty(SEQ_LIST *p)
{
	return p->length == 0;
}
////////看链表的存储空间是否存满////////
bool IsFull(SEQ_LIST *p)
{
	return p->length == p->n;
}
/////////看链表现在存储了几个数据//////////
int GetLength(SEQ_LIST *p)
{
	return p->length;
}
//////////往链表中插入数据/////////////////
bool Insert(SEQ_LIST *p, int pos, ELEM_TYPE val)
{
	if (p == NULL || pos<0 || pos>p->length)
	{
		return false;
	}
	if (IsFull(p))
	{
		p->elem = (ELEM_TYPE *)realloc(p->elem, (p->n + p->TotalLength)*sizeof(ELEM_TYPE));
		p->n += p->TotalLength;
	}
	int k = p->length;
	while (k-pos)
	{
		p->elem[k] = p->elem[k-1];
		k--;
	}
	p->elem[pos] = val;
	p->length++;
	return true;
}
/////////展示链表中的内容//////
void DisplaySeqList(SEQ_LIST *p)
{
	for (int i = 0; i<p->length; i++)
	{
		printf("%d ", p->elem[i]);
	}
	printf("\n");
}
//////删除链表中的元素////////
bool Delete(SEQ_LIST *p, int pos)
{
	while (p->length - pos - 1)
	{
		p->elem[pos++] = p->elem[pos + 1];
	}
	p->length--;
	return true;
}
///////查找一个元素在链表中的位置//////////
int my_Search(SEQ_LIST *p, ELEM_TYPE val)
{
	for (int i = 0; i<p->length; i++)
	{
		if (p->elem[i] == val)
		{
			return i;
		}
	}
	return -1;
}
/////////////在链表中找到元素的位置并且删除它///////
bool DeleteVal(SEQ_LIST *p, ELEM_TYPE val)
{
	int pos = my_Search(p, val);
	if (pos != -1)
	{
		Delete(p, pos);
		return true;
	}
	else
	{
		return false;
	}
}