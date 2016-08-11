#include"static.h"


bool list_init(STATICLIST phead)
{
	if (phead == NULL)
	{
		return false;
	}
	int i = 0;
	for (; i < MAXSIZE - 1;)
	{
		phead[i++].cur = i + 1;
	}
	phead[MAXSIZE - 1].cur = 0;
	return true;
}

int list_length(STATICLIST phead)
{
	if (phead == NULL)
	{
		return false;
	}
	return phead[0].cur-1;
}

bool list_insert(STATICLIST phead, int val, int i)
{
	if (phead == NULL || list_length(phead)+1 < i||i < 1)
	{
		return false;
	}
	if (list_length(phead) == 0)
	{
		phead[1].date = val;
		phead[1].cur = 0;
		phead[0].cur = 2;
		phead[MAXSIZE - 1].cur = 1;
		return true;
	}
	if (i == list_length(phead)+1)
	{
		int j = 1;
		int size = phead[0].cur;
		while (j < phead[0].cur)
		{
			if (phead[j].cur == -1)
			{
				phead[0].cur = j;
				break;
			}
			j++;
		}
		int k = MAXSIZE - 1;
		while (phead[k].cur)
		{
			k = phead[k].cur;
		}
		phead[phead[0].cur].cur = 0;
		phead[phead[0].cur].date = val;
		phead[k].cur = phead[0].cur;
		if (phead[0].cur < size)
		{
			phead[0].cur = size;
			return true;
		}
		phead[0].cur += 1;
		return true;
	}
	if (i >= 1 && i <= list_length(phead))
	{
		int j = 1;
		int size = phead[0].cur;
		while (j < phead[0].cur)
		{
			if (phead[j].cur == -1)
			{
				phead[0].cur = j;
				break;
			}
			j++;
		}
		int k = MAXSIZE - 1;
		int tmp = k;
		while (i--)
		{
			tmp = k;
			k = phead[k].cur;
		}
		phead[phead[0].cur].date = val;
		phead[phead[0].cur].cur = phead[tmp].cur;
		phead[tmp].cur = phead[0].cur;
		if (phead[0].cur < size)
		{
			phead[0].cur = size;
			return true;
		}
		phead[0].cur += 1;
		return true;
	}
	return true;
}

bool list_display(STATICLIST phead)
{
	if (phead == NULL || phead[MAXSIZE - 1].cur == 0)
	{
		return false;
	}
	int k = MAXSIZE - 1;
	k = phead[k].cur;
	while (phead[k].cur)
	{
		printf("%d ", phead[k].date);
		k = phead[k].cur;
	}
	printf("%d ", phead[k].date);
	printf("\n");
	return true;
}

bool list_delete(STATICLIST phead, int i)
{
	if (phead == NULL || list_length(phead) + 1 < i || i < 1)
	{
		return false;
	}
	int k = MAXSIZE - 1;
	int tmp = k;
	while (i--)
	{
		tmp = k;
		k = phead[k].cur;
	}
	int m = phead[tmp].cur;//].cur = -1;
	phead[tmp].cur = phead[k].cur;
	phead[m].cur = -1;
	return true;
}
