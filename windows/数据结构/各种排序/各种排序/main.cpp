#include<string.h>
#include<math.h>
//#include <vld.h>
#include"sort.h"

extern int count;
void my_search(int *arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		int tmp = arr[i];
		int j;
		for (j = i - 1; j >= 0; j--)
		{
			count++;
			if (tmp < arr[j])
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
int main()
{
	//int n = 1000;
	//kai_kong_jian("F://����.txt", n);
	//int *arr = read_array("F://����.txt", n);
	//clock_t t1 = clock();
	//int arr[] = { 1, 1, 1, 0 };
	//0,1
	//1,0
	//1,0,1,0
	//0,1,0,1
	//1,0,0,0
	//1,1,1,0
	int arr[] = { 7, 8,89, 23, 78, 99, 52, 48, 37, 46, 20, 19, 72, 6, 5,5,6};
	//int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printf("ԭʼ������:");
	show(arr, n);
	//exchange_sort(arr, n);
	bubble_sort(arr, n);
	//select_sort(arr, n);
	//insert_sort(arr, n);
	//insert_sort_ex(arr, n);
	//shell_sort(arr, n);
	//digui_quick_sort(arr, n);
	//xuhuan_quick_sort1(arr, n);////5w����
	//xuhuan_quick_sort2(arr, n);
	//my_search(arr, n);
	//heap_sort(arr, n
	//gui_bing(arr, n);
	//di_gui_bing(arr, n);
	//clock_t t2 = clock();
	printf("�źõ�����:");
	show(arr, n);
	
	//printf("%ld����", t2 - t1);
	//show_file(arr, n);
	//printf("%d\n", count);
	//free(arr);
	return 0;
}

///////////////////////////////////////////////////////////////////////
//  ����            1��             5��                    10��                
//��������          2330           51714                 170882
//ѡ������          325            7598                  31481
//ð������          2447           63575                 251455
//��������          181            4500-4700             18370
//shell����         51             1150                  4230(���ȶ���
//ѭ����������      90-11(400)     500                   1000(���ȶ���
//�ݹ��������      4-9            25-40                 50-70(���ȶ���
//������            5-10           30-40                 60-80(���ȶ���
//int my_pow(int m, int n)
//{
//	if (n < 0)
//	{
//		return -1;
//	}
//	else if (n == 0)
//	{
//		return 1;
//	}
//	else
//	{
//		while (--n)
//		{
//			m *= 10;
//		}
//	}
//	return m;
//}
//int my_h(char *p)
//{
//	int sum = 0;
//	int k = strlen(p)-1;
//	while (*p)
//	{
//		int j = (*p - '0')* my_pow(10,k--);
//		sum += j;
//		p++;
//	}
//	return sum;
//}
//int main()
//{
//	char buff[] = "1";
//	//printf("%d\n", my_pow(10, 3));
//	printf("%d\n", my_h(buff));
//
//	return 0;
//}

/*int mainl()
{
	int a;
	printf("%d\n", a);
}*/