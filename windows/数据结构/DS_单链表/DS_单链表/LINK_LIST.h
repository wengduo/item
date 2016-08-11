#include <stdio.h>
#include <stdlib.h>


typedef float ELEM_TYPE;


typedef struct _NODE
{
	ELEM_TYPE data;
	struct _NODE *next;
}NODE;


//初始化单链表
bool InitList(NODE *phead);
//单链表的头部插入
bool InsertHead(NODE *phead, ELEM_TYPE val);
//单链表的中部插入
bool InsertZhong(NODE *phead, ELEM_TYPE val, int k);
//单链表的尾部插入
bool InsertTail(NODE *phead, ELEM_TYPE val);
//展示单链表
void DisplayList(NODE *phead);
//销毁单链表
bool DestoryList(NODE *phead);
//得到单链表的长度
int GetLength(NODE *phead,int n);
//
bool IsEmpty(NODE *phead);
//根据位置删除链表
bool DeleteListWhere(NODE *phead, int n);
//根据数值删除链表
bool DeleteListWhat(NODE *phead, int val);
//就地逆置单链表
bool FanList(NODE *phead);
