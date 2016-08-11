#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 6
int bestx[MAX][MAX];
int arr[MAX][MAX];
int m;
int n;
int k = 0;
int best = INT_MAX;
void change(int i, int j)
{
	while (i--&&j--)
}
void restore(int i, int j)
{

}
void my_search(int i, int j)
{
	do
	{
		j++;
		if (j > n)
		{
			i++;
			j = 1;
		}
	} while (!((arr[i][j] == 0) || (i > m)));
	if (i > m)
	{
		if (k < best)
		{
			best = k;
			//memcpy(bestx, x, sizeof(bestx));
			int p = 0;
			for (int i = 0; i <= m; i++)
			{
				for (int j = 0; j <= n; j++)
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
			return;
		}
	}

}
int main()
{
	scanf("%d-%d", &m, &n);
	memset(arr, 0, sizeof(arr) / sizeof(arr[0]));
	memset(bestx, 0, sizeof(arr) / sizeof(arr[0]));
	for (int i = 0; i <= m; i++)
	{
		arr[i][n]=1;
		if (i == m)
		{
			while (i)
			{
				arr[n-1][i--] = 1;
			}
			arr[n - 1][i--] = 1;
			break;
		}

	}
	my_search(0, 0);
	return 0;
}