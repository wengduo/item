#include "trip.h"
#include <stdio.h>

//��Ԫ�飬Ԫ��e1,e2,e3�ֱ𱻸���v1,v2,v3��ֵ
bool InitTrip(TRIP *p, ELEM_TYPE v1, ELEM_TYPE v2, ELEM_TYPE v3)
{

	if (p == NULL)
	{
		return false;
	}
	p->e1 = v1;
	p->e2 = v2;
	p->e3 = v3;
	return true;
}
//��Ԫ�鱻����
bool DestoryTrip(TRIP *p)
{
	if (p == NULL)
	{
		return false;
	}
	p->e1 = 0;
	p->e2 = 0;
	p->e3 = 0;
	return true;
}  
//��e������Ԫ��ĵ�posԪ��ֵ
bool Get(TRIP *p, int pos, ELEM_TYPE *e)
{
	if (pos >= 0 && pos <= 2 && p != NULL)
	{
		if (pos == 0)
		{
			*e = p->e1;
		}
		else if (pos == 1)
		{
			*e = p->e2;
		}
		else
		{
			*e = p->e3;
		}
		return true;
	}
	return false;
}
//�ı���Ԫ���posԪ��ֵΪe
bool Put(TRIP *p, int pos, ELEM_TYPE e)
{
	if (pos<0 || pos>2 || p == NULL)
	{
		return false;
	}
	if (pos == 0)
	{
		p->e1 = e;
	}
	else if (pos == 1)
	{
		p->e2 = e;
	}
	else
	{
		p->e3 = e;
	}
	return true;
}
//�����Ԫ���е�����Ԫ�ذ��������У��򷵻��棬���򷵻ؼ�
bool IsAscending(TRIP *p)
{
	if (p->e1 < p->e2 && p->e2 < p->e3 && p != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//�����Ԫ���е�����Ԫ�ذ��������У��򷵻��棬���򷵻ؼ�
bool IsDescending(TRIP *p)
{
	if (p->e1 > p->e2 && p->e2 < p->e3 && p != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//��e������Ԫ�������ֵ���ɹ������棬ʧ�ܷ��ؼ�
void Max(TRIP *p, ELEM_TYPE *e)
{
	if (p->e1 > p->e2)
	{
		if (p->e1 > p->e3)
		{
			*e = p->e1;
		}
		else
		{
			*e = p->e3;
		}
	}
	else
	{
		if (p->e2 > p->e3)
		{
			*e = p->e2;
		}
		else
		{
			*e = p->e3;
		}
	}
}
//��e������Ԫ������Сֵ���ɹ������棬ʧ�ܷ��ؼ�
void Min(TRIP *p, ELEM_TYPE *e)
{
	if (p->e1 < p->e2)
	{
		if (p->e1 < p->e3)
		{
			*e = p->e1;
		}
		else
		{
			*e = p->e3;
		}
	}
	else
	{
		if (p->e2 < p->e3)
		{
			*e = p->e2;
		}
		else
		{
			*e = p->e3;
		}
	}
}

