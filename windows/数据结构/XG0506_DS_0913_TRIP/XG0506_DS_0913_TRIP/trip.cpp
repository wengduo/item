#include "trip.h"
#include <stdio.h>


bool InitTrip(TRIP *p,ELEM_TYPE v1, ELEM_TYPE v2, ELEM_TYPE v3)
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




//ELEM_TYPE get(TRIP *p, int pos);
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
//                   0 1 2   
bool Get(TRIP *p, int pos, ELEM_TYPE *e)
{
	if (pos>= 0 && pos<=2)
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

bool Put(TRIP *p, int pos, ELEM_TYPE e)
{
	if (p == NULL)
	{
		return false;
	}
	if (pos<0 || pos>2)
	{
		return false;
	}
	if (pos == 0)
	{
		p->e1 = e;
	}
	else if(pos == 1)
	{
		p->e2 = e;
	}
	else
	{
		p->e3 = e;
	}
	return true;
}

bool IsAscending(TRIP *p)
{
	if (p->e1 < p->e2 && p->e2 < p->e3)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool IsDescending(TRIP *p)
{
	return false;
}

void Max(TRIP *p, ELEM_TYPE *e)
{

}
void Min(TRIP *p, ELEM_TYPE *e)
{

}

