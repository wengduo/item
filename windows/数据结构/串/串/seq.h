#include<stdio.h>
#include<stdlib.h>

typedef struct _MYString
{
	char *elem;
	size_t length;
	size_t size;
}MYString;

bool InitString(MYString *phead);

bool DestoryString(MYString *phead);

bool ClearString(MYString *phead);

bool IsEmptyString(MYString *phead);

bool IsFullString(MYString *phead);

int GetLengthString(MYString *phead);

bool StringAssign(MYString *phead, char *str);

bool StringCopy(MYString *phead1, MYString *phead2);

int StringCompare(MYString *phead1, MYString *phead2);

bool StringDisplay(MYString *phead);

//StringAppend(MYString &s1, MYString &s2);

bool SubString(MYString *phead, char *s, size_t pos, size_t length);

bool InsertSub(MYString *phead1, size_t pos, MYString *phead2);

bool DeleteSub(MYString *phead, size_t pos, size_t length);

//Replace(MYString &s, MYString &t, MYString &v);

//ReplaceAll(MYString &s, MYString &t, MYString &v);
