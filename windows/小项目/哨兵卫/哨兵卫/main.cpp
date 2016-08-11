#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<LIMITS.H>
#include"my_printf.h"
#include"my_scanf.h"
#define MLEN 20

 
int d[6][3] = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, -1 }, { 0, -1, 0 }, { 0, 0, 1 }, { 0, 1, 0 } };
int x[MLEN + 1][MLEN + 1];  
int y[MLEN + 1][MLEN + 1];  
int bestx[MLEN + 1][MLEN + 1];   
int best;       
int k = 0;     
int t = 0;    
int t1;
int t2;
int more;
void change(int i, int j)
{
	x[i][j] = 1;
	k++;
	for (int s = 1; s <= 5; s++)  
	{
		int p = i + d[s][1];
		int q = j + d[s][2];
		y[p][q]++;
		if ((y[p][q] == 1))
		{
			t++;
		}
	}
}
void restore(int i, int j)
{
	x[i][j] = 0;
	k--;
	for (int s = 1; s <= 5; s++)
	{
		int p = i + d[s][1];
		int q = j + d[s][2];
		y[p][q]--;
		if ((y[p][q] == 0))
		{
			t--;
		}
	}
}
void search(int i, int j,int m,int n)   
{
	do
	{                         
		j++;
		if (j > m)
		{
			i++;
			j = 1;
		}
		
	} while (!((y[i][j] == 0) || (i > n)));   


	if (i > n)    
	{
		if (k < best)   
		{
			best = k;
			memcpy(bestx, x, sizeof(bestx));
			return;
		}
	}

	if (k + (t1 - t) / 5 >= best)  
	{
		return;
	}

	if ((i < n - 1) && (k + (t2 - t) / 5 >= best))  
	{
		return;
	}
	if (i < n)
	{
		change(i + 1, j);  
		search(i, j,m,n);
		restore(i + 1, j);
	}
	if (((y[i + 1][j] == 0) && (y[i][j + 1] == 0)))
	{
		change(i,j );
		search(i, j,m,n);
		restore(i, j);
	}
	if ((j < n) && ((y[i][j + 1] == 0) || (y[i][j + 2] == 0)))
	{
		change(i , j+1);
		search(i, j,m,n);
		restore(i , j+1);
	}

	
}
void compute(int m,int n)
{
	more = m/4 + 1;
	if (m % 4 == 3)
	{
		more++;
	}
	else if (m % 4 == 2)
	{
		more += 2;
	}
	t2 = m*n + more + 4;
	t1 = m*n + 4;
	best = INT_MAX;     
	memset(y, 0, sizeof(y));   
	memset(x, 0, sizeof(x));   
	for (int i = 0; i <= m + 1; i++)
	{
		y[0][i] = 1;
		y[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++)
	{
		y[i][m + 1] = 1;
	}
 	search(1, 0,m,n);  //从y的（1，0）开始搜索查看
}
void swap(int *p1, int *p2)
{
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
int main()
{
	my_scanf();
	return 0;
}