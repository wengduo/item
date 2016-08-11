#include <stdlib.h>
#include<stdio.h>

typedef struct _DHEAD
{
	int data;
	int size;
	struct _DNODE *next;
	struct _DNODE *prev;
	int **arr;
}HEAD;
typedef struct _DNODE
{
	int data;
	struct _DNODE *next;
	struct _DNODE *prev;
}DNODE;
//���� 
//ָ������
//��ʼ��˫����ͷ 
bool InitDHead(HEAD *phead);
//��ʼ��˫����
bool InitDList(DNODE *phead);
//չʾ˫����
bool DisplayList(HEAD *phead);
//˫�����ͷ������
bool InsertDHead(HEAD *phead, int val);
//˫�����β������
bool InsertDTail(HEAD *phead, int val);
//˫������в�����
bool InsertDByPos(HEAD *phead, int pos, int val);
//˫�����ֵɾ
bool DeleteWhat(HEAD *phead, int val);
//˫�����λ��ɾ
bool DeleteWhere(HEAD *phead, int pos);
//����˫����
bool DestoryDList(HEAD *phead);
//����˫����
bool fanDList(HEAD *phead);
//���˫�����Ƿ��л�
bool huanDList(HEAD *phead);
//�õ�˫����ĳ���
int GetlengDList(HEAD *phead);

