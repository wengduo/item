#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "stack.h"


//����n�������
void kai_kong_jian(char *path, int n);

//��ȡ����
int *read_array(char *path, int n);

//չʾ����
void show_file(int *arr, int n);

//��������
void swap(int *p1, int *p2);

//չʾ�ź��������
void show(int *arr, int n);

//��������ʱ�临�Ӷ�ΪO(n^2)
void exchange_sort(int *arr, int n);

//ð������ʱ�临�Ӷ�ΪO(n)��O(n^2)
void bubble_sort(int *arr, int n);

//ѡ������ʱ�临�Ӷ�ΪO(n^2)
void select_sort(int *arr, int n);

//��������ʱ�临�Ӷ�ΪO(n^2)
void insert_sort(int *arr, int n);

//�Ľ���Ĳ�������
void insert_sort_ex(int *arr, int n);

//ϣ������,ʱ�临�Ӷ�O(n^1.3)��O(n^2)
void shell_insert_1(int *arr, int n, int gap);
void shell_insert_2(int *arr, int n, int gap);
void shell_sort(int *arr, int n);

//�ݹ�ʽ�Ŀ�������ʱ�临�Ӷ�O(nlogn)��O(n^2)
int partition1(int *arr, int low, int high);
void quick(int *arr, int low, int high);
void digui_quick_sort(int *arr, int n);

//ѭ��ʽ�Ŀ�������ʱ�临�Ӷ�O(nlogn)��O(n^2)
void xuhuan_quick_sort1(int *arr, int n);
//
void xuhuan_quick_sort2(int *arr, int n);
//
//void weiding_sort(int *arr, int low, int high); //���������

//������,ʱ�临�Ӷ�O(nlogn)
void heap_sort(int *arr, int n);

//�鲢����
void gui_bing(int *arr, int n);

void di_gui_bing(int *arr, int n);