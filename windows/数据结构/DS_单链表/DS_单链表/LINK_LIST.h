#include <stdio.h>
#include <stdlib.h>


typedef float ELEM_TYPE;


typedef struct _NODE
{
	ELEM_TYPE data;
	struct _NODE *next;
}NODE;


//��ʼ��������
bool InitList(NODE *phead);
//�������ͷ������
bool InsertHead(NODE *phead, ELEM_TYPE val);
//��������в�����
bool InsertZhong(NODE *phead, ELEM_TYPE val, int k);
//�������β������
bool InsertTail(NODE *phead, ELEM_TYPE val);
//չʾ������
void DisplayList(NODE *phead);
//���ٵ�����
bool DestoryList(NODE *phead);
//�õ�������ĳ���
int GetLength(NODE *phead,int n);
//
bool IsEmpty(NODE *phead);
//����λ��ɾ������
bool DeleteListWhere(NODE *phead, int n);
//������ֵɾ������
bool DeleteListWhat(NODE *phead, int val);
//�͵����õ�����
bool FanList(NODE *phead);
