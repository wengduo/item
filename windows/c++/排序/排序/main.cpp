
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
	char *path = "F://����.txt";
	creat_file(path , n);
	//int *arr = read_array("F://����.txt", n);
	clock_t t1 = clock();
	//guibing_sort(arr, n);
	out_sort(path, n);
	clock_t t2 = clock();
	printf("%ld����", t2 - t1);
	//show(arr, n);
	show_file(path, n);
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
//�鲢              2              16                    47(�ȶ���
//������            10��2172��   100��19501)         1000��185327��