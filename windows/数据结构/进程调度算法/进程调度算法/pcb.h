#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ERROR 0
#define OK 1


typedef struct _PCB
{
	char NAME[10];    //进程名字
	int PRIO;        //进程优先级
	int ROUNT;       //轮转时间片       
	int NOWTIME;     //进程到达时间
	int NEEDTIME;    //需要的CPU时间
	char S;      //进程状态
}PCB;

typedef struct _ANODE
{
	int CPUTIME;
	int COUNT; //计数器
	PCB pcb;
	struct _ANODE *next;
	struct _ANODE *prev;
}ANODE;

typedef struct _BNODE //就绪队列
{      
	PCB pcb;
	struct _BNODE *next; 
	struct _BNODE *prev;  
	struct _BNODE *tail;   //尾指针
}BNODE;

typedef struct _CNODE    //完成队列
{   
	PCB pcb;
	struct _CNODE *next;   
	struct _CNODE *prev;    
}CNODE;

bool init_A(ANODE **phead);

bool init_B(BNODE **head);

bool init_C(CNODE **hd);

int ANODE_length(ANODE *phead);

ANODE* insert_A(ANODE *phead);

bool creat_outM(ANODE *phead);

void prisch_AB(ANODE *phead, BNODE *head, CNODE *hd);

void roundsch_AB(ANODE *phead, BNODE *head, CNODE *hd);