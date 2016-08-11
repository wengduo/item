#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _PCB
{
	char NAME[10];   //进程名字
	int PRIO;        //进程优先级
	int ROUNT;       //轮转时间片       
	int NOWTIME;     //进程到达时间
	int NEEDTIME;    //需要的CPU时间
	int VOERTIME;
	int FH;
	char S;          //进程状态
}PCB;

typedef struct _NODE
{
	PCB pcb;
	int CPUTIME;
	int COUNT; //计数器
	struct _NODE *tail;
	struct _NODE *next;
	struct _NODE *prev;
}NODE;

bool init_list(NODE **phead);

int NODE_length(NODE *phead);

NODE* insert_list(NODE *phead);

bool creat_outM(NODE *phead);

void prisch_list(NODE *phead, NODE *head, NODE *hd);

void roundsch_list(NODE *phead, NODE *head, NODE *hd);