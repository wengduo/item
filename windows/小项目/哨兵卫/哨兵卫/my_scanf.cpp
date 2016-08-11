#define _CRT_SECURE_NO_WARNINGS

#define MLEN 20
#include<stdio.h>
#include<string.h>
#include"my_printf.h"

void my_scanf()
{
	int p = 0;
	int m;
	int n;
	printf("请输入列号和行号(极限为12)\n");
	scanf("%d,%d", &m, &n);
	if (m == 0 || n == 0)
	{
		printf("行号或列号不能为0\n");
		printf("请重新输入列号和行号");
		my_scanf();
	}
	else
	{
		my_printf(m, n, p);
		my_scanf();
	}
}