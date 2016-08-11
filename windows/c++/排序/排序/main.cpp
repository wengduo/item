
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <vld.h>
#include <time.h>
#include "sort.h"

int main()
{
	int n = 1000000;
	char *path = "F://数据.txt";
	creat_file(path , n);
	//int *arr = read_array("F://数据.txt", n);
	clock_t t1 = clock();
	//guibing_sort(arr, n);
	out_sort(path, n);
	clock_t t2 = clock();
	printf("%ld毫秒", t2 - t1);
	//show(arr, n);
	show_file(path, n);
	//free(arr);
	return 0;
}
///////////////////////////////////////////////////////////////////////
//  排序            1万             5万                    10万                
//交换排序          2330           51714                 170882
//选择排序          325            7598                  31481
//冒泡排序          2447           63575                 251455
//插入排序          181            4500-4700             18370
//shell排序         51             1150                  4230(不稳定）
//循环快速排序      90-11(400)     500                   1000(不稳定）
//递归快速排序      4-9            25-40                 50-70(不稳定）
//堆排序            5-10           30-40                 60-80(不稳定）
//归并              2              16                    47(稳定）
//外排序            10万（2172）   100万（19501)         1000万（185327）