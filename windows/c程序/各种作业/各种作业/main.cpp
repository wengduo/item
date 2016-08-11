//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>



/*int main()
{
	int A = 0;
	int B = 0;
	int C = 0;
	int count = 1;
	for (int i = 0; i < 7 * 21; i++)
	{
		if (A<=21 * 5)
		{
			A++;
		}
		if (B < 21 * 6)
		{
			B++;
		}
		
		C++;
		if (A % 5 == 0 || B % 6 == 0 || C % 7 == 0)
		{
			count++;
		}
	}
	printf("%d\n", count);
	return 0;
}

int main()
{
	int n = 10;
	int m = 5;
	for (int i = 0; i <= n; i++)
	{
		if (i <= m)
		{
            for (int j = 0; j <= n/2-i; j++)
		    {
			     printf(" ");
	        }
		    for (int k = 0; k <= 2*i; k++)
		   {
			     printf("*");
		
		   }
		}
		else
		{
			for (int j = 0;j <=( i - m); j++)
			{
				printf(" ");
			}
			for (int k = 0; k <= n - 2 * (i - 5); k++)
			{
				printf("*");
			}
		}
		
		printf("\n");
	}

	return 0;
}
void swap(int *m, int *n)
{
	int tmp;
	tmp = *m;
	*m = *n;
	*n = tmp;

}
int main()
{
	int x = 10;
	int y = 20;
	swap(&x,&y);
	printf("%d-%d\n",x,y);

	return 0;
}*/
int main()
{
	int n = 10;
	int k = 0;
	int i=0;
	for (; i <= n; i++)
	{
		char ch = 'A';
		if (i <= n / 2)
		{
			for (int j = 0; j <= n / 2 + i; j++)
			{
				if (j < n / 2 - i)
				{
					printf(" ");
				}
				else if (j<n / 2)
				{
					printf("%c", ch++);
				}
				else
				{
					printf("%c", ch--);
				}
			}
		}
		else
		{
			for (int j =0; j<10-k; j++)
			{
				if (j<i-n / 2 )
				{
					printf(" ");
				}
				else if (j<n / 2)
				{
					printf("%c", ch++);
				}
				else
				{
					printf("%c", ch--);
				}
			}
			k++;
		}
		printf("\n");
	}

	return 0;
}