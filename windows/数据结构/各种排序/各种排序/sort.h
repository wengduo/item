#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "stack.h"


//申请n个随机数
void kai_kong_jian(char *path, int n);

//读取数据
int *read_array(char *path, int n);

//展示数据
void show_file(int *arr, int n);

//两数交换
void swap(int *p1, int *p2);

//展示排好序的数列
void show(int *arr, int n);

//交换排序，时间复杂度为O(n^2)
void exchange_sort(int *arr, int n);

//冒泡排序，时间复杂度为O(n)到O(n^2)
void bubble_sort(int *arr, int n);

//选择排序，时间复杂度为O(n^2)
void select_sort(int *arr, int n);

//插入排序，时间复杂度为O(n^2)
void insert_sort(int *arr, int n);

//改进版的插入排序
void insert_sort_ex(int *arr, int n);

//希尔排序,时间复杂度O(n^1.3)到O(n^2)
void shell_insert_1(int *arr, int n, int gap);
void shell_insert_2(int *arr, int n, int gap);
void shell_sort(int *arr, int n);

//递归式的快速排序，时间复杂度O(nlogn)到O(n^2)
int partition1(int *arr, int low, int high);
void quick(int *arr, int low, int high);
void digui_quick_sort(int *arr, int n);

//循环式的快速排序，时间复杂度O(nlogn)到O(n^2)
void xuhuan_quick_sort1(int *arr, int n);
//
void xuhuan_quick_sort2(int *arr, int n);
//
//void weiding_sort(int *arr, int low, int high); //设计有问题

//堆排序,时间复杂度O(nlogn)
void heap_sort(int *arr, int n);

//归并排序
void gui_bing(int *arr, int n);

void di_gui_bing(int *arr, int n);