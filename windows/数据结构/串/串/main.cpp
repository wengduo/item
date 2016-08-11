#include"seq.h"


int main()
{
	MYString s;
	MYString s1;
	InitString(&s);
	InitString(&s1);
	char buff[100] = "hello worldl";
	char buff1[100];
	//ClearString(&s);
	StringAssign(&s, buff);
	IsEmptyString(&s);
	IsFullString(&s);
	printf("%d\n",GetLengthString(&s));
	
	//StringAssign(&s1, buff1);
	//StringDisplay(&s);
	StringDisplay(&s1);
	//StringCopy(&s,&s1);
	//StringDisplay(&s);
	//printf("%d\n",StringCompare(&s, &s1));
	//StringAppend(MYString &s1, MYString &s2);

	SubString(&s, buff1, 5, 3);
	printf("%s\n", buff1);
	//InsertSub(&s, 3, &s1);
	//DeleteSub(&s, 3, 5);

	DestoryString(&s);
	DestoryString(&s1);
	return 0;
}