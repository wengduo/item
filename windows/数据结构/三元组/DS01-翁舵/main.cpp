#include <stdio.h>
#include<stdlib.h>
#include "trip.h"

//////////////////////////////////////////三元组练习////////////////
/*int main()
{
	TRIP *pt = (TRIP *)malloc(sizeof(TRIP)* 1);
	ELEM_TYPE e = 0;
	bool k;
	InitTrip(pt, 20, 30, 50);
	DestoryTrip(pt);
	InitTrip(pt, 20, 30, 50);
	Get(pt, 2, &e);
	Put(pt, 2, e);
	k=IsAscending(pt);
	k=IsDescending(pt);
	Max(pt, &e);
	Min(pt, &e);
	free(pt);
	return 0;
}*/


//////////////////////////排序练习///////////////////////////////////
//冒泡排序
void Maopao_sort(int *arr, int len)
{
	int tmp;
	for (int i = 0; i<len - 1; i++)
	{
		for (int j = 0; j<len - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
//交换排序
void Jiaohuan_sort(int *arr, int len)
{
	int tmp;
	for (int i = 0; i<len; i++)
	{
		for (int j = i + 1; j<len; j++)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}
//选择排序
void Xuanze_sort(int *arr, int len)
{
	int min = 0;
	int tmp;
	for (int i = 0; i<len; i++)
	{
		min = i;
		for (int j = i + 1; j<len; j++)   //找到最小值的下标
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}
		if (i != min)
		{
			tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}
//插入排序
void insert_sort(int *arr, int len)
{
	int i = 0;
	int j = 0;
	int tmp = arr[0];
	for (i = 1; i<len; i++)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--)  //j走几个，排好几个
		{
			if (arr[j] > tmp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = tmp;
	}
}
//二分查找
int bin_find(int *arr, int len, int key)
{
	int left = 0;
	int right = len - 1;
	int mid = (left + right) / 2;
	while (left <= right)
	{
		if (arr[mid]>key)
		{
			right = mid - 1;
			mid = (left + right) / 2;
		}
		else if (arr[mid] < key)
		{
			left = mid + 1;
			mid = (left + right) / 2;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}


int main()
{
	int arr[10] = { 3, 2, 1, 5, 8, 9, 0, 7, 4, 6 };
	int h = sizeof(arr) / sizeof(arr[0]);
	//Maopao_sort(arr, h);
	//Jiaohuan_sort(arr, h);
	//Xuanze_sort(arr, h);
	insert_sort(arr, h);
	printf("%d\n", bin_find(arr, h, 0));
	return 0;
}