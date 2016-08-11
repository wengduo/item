#include <stdio.h>
#include "trip.h"

/*
int main()
{
//	TRIP *pt = (TRIP *)malloc(sizeof(TRIP)*1);

	TRIP t;
	ELEM_TYPE e;

	InitTrip(&t,20,30,50);
	Get(&t,2,&e);
	printf("%d\n",IsAscending(&t));
	return 0;
}
*/

#define  N 10

int find(int *arr, int length, int key)
{
	for (int i=0;i<length; i++)
	{
		if (arr[i] == key)
		{
			return i;
		}
	}
	return -1;
}

void bubble_sort(int *arr, int length)
{
	int tmp;

	//0 9
	//1 8
	//2 7
	for (int i=0;i<length-1;i++)
	{
		for (int j=0;j<length-1-i;j++)
		{
			if (arr[j] > arr[j+1])
			{
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

int bin_find(int *arr, int length, int key)
{
	int left = 0;
	int right = length-1;
	int mid = (left+right)/2;

	while(left <= right)
	{
		if (arr[mid]>key)
		{
			right = mid-1;
			mid = (left+right)/2;
		}
		else if (arr[mid] < key)
		{
			left = mid+1;
			mid = (left+right)/2;
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
	int arr[10] = {3,2,1,5,8,9,0,22,80,60};
	bubble_sort(arr,N);
	printf("%d\n",bin_find(arr, N, -2));
	return 0;
}