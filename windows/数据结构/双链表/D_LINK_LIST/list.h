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
//结点表 
//指针数组
//初始化双链表头 
bool InitDHead(HEAD *phead);
//初始化双链表
bool InitDList(DNODE *phead);
//展示双链表
bool DisplayList(HEAD *phead);
//双链表的头部插入
bool InsertDHead(HEAD *phead, int val);
//双链表的尾部插入
bool InsertDTail(HEAD *phead, int val);
//双链表的中部插入
bool InsertDByPos(HEAD *phead, int pos, int val);
//双链表的值删
bool DeleteWhat(HEAD *phead, int val);
//双链表的位置删
bool DeleteWhere(HEAD *phead, int pos);
//销毁双链表
bool DestoryDList(HEAD *phead);
//逆序双链表
bool fanDList(HEAD *phead);
//检查双链表是否有环
bool huanDList(HEAD *phead);
//得到双链表的长度
int GetlengDList(HEAD *phead);

