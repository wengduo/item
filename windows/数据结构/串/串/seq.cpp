#include"seq.h"
#include<vld.h>


bool InitString(MYString *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	phead->length = 0;
	phead->size = 10;
	phead->elem = (char *)malloc(sizeof(char)*phead->size);

	return true;
}

bool DestoryString(MYString *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	phead->length = 0;
	free(phead->elem);

	return true;
}

bool ClearString(MYString *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	phead->length = 0;

	return true;
}

bool StringDisplay(MYString *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	for (int i = 0; i < phead->length; i++)
	{
		printf("%c", phead->elem[i]);
	}
	printf("\n");
	return true;
}
bool IsEmptyString(MYString *phead)
{
	return phead->length >= phead->size;
}

bool IsFullString(MYString *phead)
{
	return phead->length == 0;
}

int GetLengthString(MYString *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	return phead->length;
}

bool StringAssign(MYString *phead, char *str)
{
	if (phead == NULL)
	{
		return false;
	}

	while (*str)
	{
		if (IsEmptyString(phead))
		{
			phead->elem = (char *)realloc(phead->elem,sizeof(char)*phead->size * 2);
			phead->size *= 2;
		}
		phead->elem[phead->length++] = *str++;
	}

	return true;
}
bool StringCopy(MYString *phead1, MYString *phead2)
{
	if (phead1 == NULL || phead2 == NULL)
	{
		return false;
	}

	while (phead2->size < phead1->size)
	{
		phead2->elem = (char *)realloc(phead2->elem,sizeof(char)*phead2->size * 2);
		phead2->size *= 2;
	}
	for (int i = 0; i < phead1->length; i++)
	{
		phead2->elem[i] = phead1->elem[i];
	}
	phead2->length = phead1->length;

	return true;
}
int StringCompare(MYString *phead1, MYString *phead2)
{
	int k = 0;
	while (k<phead1->length && k<phead2->length)
	{
		if (phead1->elem[k] > phead2->elem[k])
		{
			return 1;
		}
		else if (phead1->elem[k] < phead2->elem[k])
		{
			return -1;
		}
		k++;
	}
	if (phead1->length == phead2->length)
	{
		return 0;
	}
	else if (phead1->length>phead2->length)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
//StringAppend(MYString &s1, MYString &s2);

bool SubString(MYString *phead, char *s, size_t pos, size_t length)
{
	if (phead == NULL || pos < 0 || pos>phead->length || length>(phead->length-pos+1))
	{
		return false;
	}
	while (length--)
	{
		*s++ = phead->elem[pos++];
	}
	*s = 0;
	return 0;
}

bool InsertSub(MYString *phead1, size_t pos, MYString *phead2)
{
	if (phead1 == NULL || phead2 == NULL || pos < 0 || pos>GetLengthString(phead1))
	{
		return false;
	}
	int i = 0;
	int j = phead1->length;
	int k = phead2->length;
	phead1->length += phead2->length;
	while (IsEmptyString(phead1))
	{
		phead1->elem = (char *)malloc(sizeof(char)*phead1->size * 2);
		phead1->size *= 2;
	}
	while (k--)
	{
		phead1->elem[phead1->length + k] = phead1->elem[--j];
	}
	while (phead2->length--)
	{
		phead1->elem[pos++] = phead2->elem[i++];
	}
	return true;
}

bool DeleteSub(MYString *phead, size_t pos, size_t length)
{
	if (phead == NULL || pos < 0 || pos>GetLengthString(phead)-length+1)
	{
		return false;
	}
	int i = length;
	while (length--)
	{
		if ((pos + i)>phead->length)
		{
			phead->elem[pos++] = phead->elem[pos + i];
		}
		else
		{
			phead->elem[pos++] = 0;
		}
	}
	phead->length -= length;
	return true;
}


