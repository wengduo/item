#include<stdio.h>
#include<iostream>
int k = 0;
int k1 = 0;
int func(int n,int a,int b)
{
	k++;
	if (n < 0)
	{
		return -1;
	}
	if (n == 1 || n == 2)
	{
		return b;
	}
	else
	{
		int c = a + b;
		a = b;
		b = c;
		func(--n, a, b);
	}
}
int fun(int n)
{
	k1++;
	if (n < 0)
	{
		return -1;
	}
	if (n == 1 || n == 2)
	{
		return 1;
	}
	else
	{
		return fun(n-1)+fun(n-2);
	}
}
int main()
{
	int n = 20;
	int a = 1;
	int b = 1;
	int sum = func(n,a,b);
	int sum1 = fun(n);
	printf("%d-%d\n", sum,sum1);
	printf("%d-%d\n", k, k1);
	return 0;
}