#include "trip.h"
#include <stdio.h>

//三元组，元素e1,e2,e3分别被赋以v1,v2,v3的值
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
//三元组被销毁
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
//用e返回三元组的第pos元的值
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
//改变三元组第pos元的值为e
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
//如果三元组中的三个元素按升序排列，则返回真，否则返回假
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
//如果三元组中的三个元素按降序排列，则返回真，否则返回假
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
//用e返回三元组中最大值，成功返回真，失败返回假
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
//用e返回三元组中最小值，成功返回真，失败返回假
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

