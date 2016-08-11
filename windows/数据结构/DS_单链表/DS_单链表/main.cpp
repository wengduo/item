#include <stdio.h>
#include<string.h>
#include"seq.h"
#include <vld.h>

void zhong_hou(char *p)
{
	NODE *s;
	list_init(&s);
	char buff1[200];
	int i;
	while (*p != NULL)
	{
		if (*p >= '0'&& *p <= '9')
		{
			buff1[i] = *p;
		}
		else
		{

		}
	}
}
int main()
{
	
	char buff[200];
	printf("请输入四则表达式：\n");
	gets(buff);
	printf("%s\n", buff);
	zhong_hou(buff);
	
	//DestoryList(&);
	return 0;
}