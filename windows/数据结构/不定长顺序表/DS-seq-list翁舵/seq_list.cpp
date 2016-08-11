#include "seq_list.h"
#include <stdio.h>
#include<stdlib.h>
////////����һ��������////////
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
////////������������////////////
bool DetorySeqList(SEQ_LIST *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->length = 0;
	return true;
}
////////������������///////////
bool ClearSeqList(SEQ_LIST *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->length = 0;
	return true;
}
////////����ǰ�����Ƿ�Ϊ��///////
bool IsEmpty(SEQ_LIST *p)
{
	return p->length == 0;
}
////////������Ĵ洢�ռ��Ƿ����////////
bool IsFull(SEQ_LIST *p)
{
	return p->length == p->n;
}
/////////���������ڴ洢�˼�������//////////
int GetLength(SEQ_LIST *p)
{
	return p->length;
}
//////////�������в�������/////////////////
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
/////////չʾ�����е�����//////
void DisplaySeqList(SEQ_LIST *p)
{
	for (int i = 0; i<p->length; i++)
	{
		printf("%d ", p->elem[i]);
	}
	printf("\n");
}
//////ɾ�������е�Ԫ��////////
bool Delete(SEQ_LIST *p, int pos)
{
	while (p->length - pos - 1)
	{
		p->elem[pos++] = p->elem[pos + 1];
	}
	p->length--;
	return true;
}
///////����һ��Ԫ���������е�λ��//////////
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
/////////////���������ҵ�Ԫ�ص�λ�ò���ɾ����///////
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