#include<stdio.h>



void l_copy(int *arr, int *brr, int count)
{
	for (int i = 0; i < count; i++)
	{
		arr[i++] = brr[i++];
	}
}
void merge(int *arr, int *brr, int l, int m, int r)
{
	int i = 1;
	int j = m + 1;
	int k = 1;
	while ((i <= m) && (j <= r))
	{
		if (arr[i] <= arr[j])
		{
			brr[k++] = arr[i++];
		}
		else
		{
			brr[k++] = arr[j++];
		}
	}
	if (i > m)
	{
		for (int q = i; q <= r; q++)
		{
			brr[k++] = arr[q];
		}
	}
	else
	{
		for (int q = i; q <= m; q++)
		{
			brr[k++] = arr[q];
		}
	}
}
void mergesort(int *arr,int *brr,int left, int right)
{
	if (left < right)
	{
		int i = (left + right) / 2;
		mergesort(arr,brr, left, i);
		mergesort(arr, brr,i + 1, right);
		merge(arr, brr, left, i, right);
		l_copy(arr, brr, right);
	}
}



int main()
{
	int arr[] = { 1, 2, 6, 4, 5, 3, 7, 8, 9, 18, 14, 13 };
	int brr[20] = {};
	int h = sizeof(arr) / sizeof(arr[0]);
	mergesort(arr,brr, 0, h);
	printf("%d ", arr);
	return 0;
}