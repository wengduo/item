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
	printf("�������кź��к�(����Ϊ12)\n");
	scanf("%d,%d", &m, &n);
	if (m == 0 || n == 0)
	{
		printf("�кŻ��кŲ���Ϊ0\n");
		printf("�����������кź��к�");
		my_scanf();
	}
	else
	{
		my_printf(m, n, p);
		my_scanf();
	}
}