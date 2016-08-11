#include<stdio.h>



/*int main()
{
	int arr[5][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	int i = 0;
	int j;
	for (int j = 0; j < 5; j++)
	{
		printf("%d ", arr[i][j]);
		if (j == 4)
		{
			j--;
			i++;
		}
		if (i == 5)
		{
			i--;
			while (j >= 0)
			{
				printf("%d ", arr[i][j]);
				j--;
			}
			break;
		}

	}
	j = 0;
	for (i = 3; i > 0; i--)
	{
		
		printf("%d ", arr[i][j]);
		if (i == 1)
		{
			i++;
			j++;
		}
		if (j == 4)
		{
			i++;
			if (i == 3)
			{
				for (i = 2; i < 4; i++)
				{
					j = 3;
					printf("%d ", arr[i][j]);

				}
				break;
			}
		}
		
	}
	i = 3;
	for (j = 2; j > 0; j--)
	{

		printf("%d ", arr[i][j]);
		if (j == 1)
		{
			i--;
			j++;
			
			if (i == 1)
			{
				printf("%d ",arr[2][2]);
				break;
			}
		}
	}
	return 0;
}
//冒泡法排序
int main()
{
	int arr[10] = { 7, 6, 4, 3, 5, 1, 2, 9, 10, 8 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i<length - 1; i++)
	{
		for (int j = 0; j<length - i - 1; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int k = 0; k < length; k++)
	{
		printf("%d ", arr[k]);
	}
	return 0;
}
//交换法排序
int main()
{
	
	int arr[10] = { 7, 6, 4, 3, 5, 1, 2, 9, 10, 8 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i<length - 1; i++)
	{
		for (int j = i + 1; j<length; j++)
		{
			if (arr[i]>arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	for (int k = 0; k < length; k++)
	{
		printf("%d ", arr[k]);
	}
	return 0;
}
//优化版
int main()
{
	int arr[10] = { 7, 6, 4, 3, 5, 1, 2, 9, 10, 8 };
	int length = sizeof(arr) / sizeof(arr[0]);
	bool flag = true;
	int count = 0;
	for (int i = 0; i<length - 1 && flag; i++)
	{
		flag = false;
		for (int j = 0; j<length - i - 1; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flag = true;
			}
			count++;
		}
	}
	for (int k = 0; k < length; k++)
	{
		printf("%d ", arr[k]);
	}
	return 0; 
}
//选择排序法
int main()
{
	int arr[10] = { 7, 6, 4, 3, 5, 1, 2, 9, 10, 8 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int min = 0;
	for (int i = 0; i<length - 1; i++)
	{
		min = i; //定义当前下标为最小值
		for (int j = i + 1; j<length; j++)
		{
			if (arr[min] > arr[j]) //如果存在更小的值
			{
				min = j; //调整min 下标
			}
		}
		if (i != min) //若i 不为最小值，交换
		{
			int tmp = arr[min];
			arr[min] = arr[i];
			arr[i] = tmp;
		}
	}
	for (int i = 0; i < length ; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}
int main()
{
	int arr[10] = { 7, 6, 4, 3, 5, 1, 2, 9, 10, 8 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int low = 0;
	int high = length - 1;
	int mid;
	int key = 2;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key<arr[mid])
		{
			high = mid - 1;
		}
		else if (key>arr[mid])
		{
			low = mid + 1;
		}
		else
		{
			printf("%d\n", mid);
			break;
		}
	}
	return 0;
}*/




int main()
{
	printf("%d\n", 11);


return 0;
}