#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<string.h>
struct task
{
	int num;
	int end;
	int punish;
};
void sortend(struct task arr[], int n)
{
	int  i = 0;
	int  j = 0;
	struct task temp;

	for (i = 0; i<n - 1; i++)
	{
		for (j = 0; j<n - 1 - i; j++)
		{
			if (arr[j].end >= arr[j + 1].end)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void bianli(struct task brr[], int n)
{
	int h = 0;
	int m = 0;
	int sum=0;
	for (int i = 0; i < n; i++)
	{
		if ((h<brr[i].punish) && (brr[i].end>0))
		{
			h = brr[i].punish;
			m = i;
		}
	}
	brr[m].punish = 0;
	brr[m].end = 0;
	for (int k = m+1; k< n; k++)
	{
		brr[k].end--;
	}
	for (int j = 0; j < n; j++)
	{
		if (brr[j].end >= 0)
		{
			sum += brr[j].end;
		}
	}
	if (sum > 0)
	{
		bianli(brr, n);
	}
}
int func(struct task *p, int n)
{
	int index = 0;
	sortend(p, n);
	bianli(p, n);
	for (int k = 0; k < n; k++)
	{
		if (((p + k)->punish)>0)
		{
			index += ((p + k)->punish);
		}
	}
	return index;
}
int main()
{
	int  n = 0;
	int  i = 0;
	int  index;
	struct task array[10];
	printf("������һ���ж�������\n");
	scanf("%d", &n);
	printf("��ֱ���������Ľ���ʱ��ʹ�����\n");
	for (i = 0; i<n; i++)
	{
		printf("�������%d�����������źͽ���ʱ���Լ�������\n", i + 1);
		scanf("%d %d %d", &array[i].num, &array[i].end, &array[i].punish);
	}
	index = func(array, n);
	printf("��������İ���֮���������κ�ʱ���õ������ٴ���Ϊ:%d\n", index);
	return 0;
}