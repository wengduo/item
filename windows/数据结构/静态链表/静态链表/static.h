
#define MAXSIZE 100
#include<stdio.h>

//typedef int ELEM_TYPE;
typedef struct
{
	int date;//������
	int cur;//��һ�����ݵ��±�
}compare,STATICLIST[MAXSIZE];

bool list_init(STATICLIST phead);

bool list_insert(STATICLIST phead, int val, int i);

int list_length(STATICLIST phead);

bool list_display(STATICLIST phead);

bool list_delete(STATICLIST phead,int i);