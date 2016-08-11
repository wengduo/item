#include<stdio.h>
#include<string.h>
#include"my_find.h"
#include"exchange_sort.h"

#define ERROR -1
//extern int my_find(int *p, int r, int n, int l);
//extern void exchange_sort(int array[], int n);
/*int my_find(int *p,int n)
{
    int i = 0;
	while ( p[i] != n)  
	{
		i++;
	}
	return i + 1;
}


void exchange_sort(int array[], int n)
{
	int tmp;

	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (array[i] > array[j])
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
		}
	}
}
int my_find(int *p, int r,int n,int l)
{
	int i = (l + r) / 2;
	if (n > p[i])
	{
		l = i;
		my_find(p, r, n, l);

	}
	else if(n<p[i])
	{
		r = i;
		my_find(p, r, n, l);
	}
	else
	{
		return i+1;
	}
}*/

int main()
{  
	int l = 0;
	int arr[] = {  4, 5, 6, 7, 8, 9, 0, 33, 22, 88, 99, 74742,2,1,77,55,44 };
	int k = 5;
	int count = sizeof(arr) / sizeof(arr[0]);
	exchange_sort(arr,count );
	for (int i = 0; i < count; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("%d\n",my_find(arr, count, k,l) );
	return 0;
}
