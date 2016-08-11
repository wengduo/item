#define MLEN 20
#include<stdio.h>

extern void swap(int *p1, int *p2);
extern int best;
extern int bestx[MLEN + 1][MLEN + 1];;
extern void compute(int m, int n);
void my_printf(int m, int n, int p)
{
	if (m == 1)
	{
		int best = 0;
		if (n % 3 == 0)
		{
			for (int i = 1; i <= n; i++)
			{
				if (i == 2 + p * 3)
				{
					printf("1 ");
					p++;
					best++;
				}
				else
				{
					printf("0 ");
				}
			}
			printf("\n%d\n ", best);
		}
		else if (n%3==1)
		{
			for (int i = 1; i < n; i++)
			{
				if (i == 2 + p * 3)
				{
					printf("1 ");
					p++;
					best++;
				}
				else
				{
					printf("0 ");
				}
			}
			printf("1");
			printf("\n%d\n ", ++best);
		}
		else
		{
			if (n % 3 == 2)
			{
				for (int i = 1; i <= n; i++)
				{
					if (i == 2 + p * 3)
					{
						printf("1 ");
						p++;
						best++;
					}
					else
					{
						printf("0 ");
					}
				}
				printf("\n%d\n ", best);
			}
		}
	}
	else if (n == 1)
	{
		int best = 0;
		if (m % 3 == 0)
		{
			for (int i = 1; i <= m; i++)
			{
				if (i == 2 + p * 3)
				{
					printf("1\n");
					p++;
					best++;
				}
				else
				{
					printf("0\n");
				}
			}
			printf("\n%d\n ", best);
		}
		else if (n%3==1)
		{
			for (int i = 1; i < m; i++)
			{
				if (i == 2 + p * 3)
				{
					printf("1\n");
					p++;
					best++;
				}
				else
				{
					printf("0\n");
				}
			}
			printf("1\n%d\n ", ++best);
		}
		else
		{
			if (n % 3 == 2)
			{
				for (int i = 1; i <= n; i++)
				{
					if (i == 2 + p * 3)
					{
						printf("1\n");
						p++;
						best++;
					}
					else
					{
						printf("0\n");
					}
				}
				printf("\n%d\n ", best);
			}
		}
	}
	else
	{
		if (m <= n)
		{
			compute(m, n);
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= m; j++)
				{
					printf("%d ", bestx[i][j]);
					p++;
					if (p % m == 0)
					{
						printf("\n");
					}
				}
			}
			printf("%d\n", best);
		}
		else
		{
			swap(&m, &n);
			compute(m, n);
			for (int j = 1; j <= m; j++)
			{
				for (int i = 1; i <= n; i++)
				{
					printf("%d ", bestx[i][j]);
					p++;
					if (p % n == 0)
					{
						printf("\n");
					}
				}
			}
			printf("%d\n", best);
		}
	}
}