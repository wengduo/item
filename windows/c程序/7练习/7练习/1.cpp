#include<stdio.h>
/*int func_s(int x, int y)
{
	int rs;
	int r;
	int p;
	if (x < y)
	{
		int tmp;
		tmp = x;
		x = y;
		y = tmp;
	}
	if (x%y == 0)
	{
		rs = y;
	}
	else
	{
		p = x*y;
		while (y != 0)
		{
			r = x%y;
			x = y;
			y = r;
		}
		rs = x;
	}
	return rs;
}
int func_b(int x, int y)
{
	int rb;
	int r;
	int p;
	if (x < y)
	{
		int tmp;
		tmp = x;
		x = y;
		y = tmp;
	}
	if (x%y == 0)
	{
		
		rb = x;
	}
	else
	{
		p = x*y;
		while (y != 0)
		{
			r = x%y;
			x = y;
			y = r;
		}
		
		rb = p / x;
	}
	
	return  rb;
}
int main()
{
	int a = 6;
	int b = 9;
	
	printf("%d-%d\n",func_s(a,b),func_b(a,b));
	return 0;
}*/
int func(int x)
{
	int i;
	int rs;
	for (i = 2; i < x; i++)
	{
		if (x%i == 0)
		{
			rs = 0;
			break;
			
		}
		else
		{
			continue;
		}
	}
	if (i > x - 1)
	{
		rs = 1;
		
	}
	return rs;
}
int main()
{
	int a=15;

	if (func(a) == 1)
	{
		printf("%d是一个素数\n", a);
	}
	else
	{
		printf("%d不是一个素数\n", a);
	}

	return 0;
}
