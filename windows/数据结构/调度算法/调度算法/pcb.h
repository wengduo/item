#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _PCB
{
	char NAME[10];   //��������
	int PRIO;        //�������ȼ�
	int ROUNT;       //��תʱ��Ƭ       
	int NOWTIME;     //���̵���ʱ��
	int NEEDTIME;    //��Ҫ��CPUʱ��
	int VOERTIME;
	int FH;
	char S;          //����״̬
}PCB;

typedef struct _NODE
{
	PCB pcb;
	int CPUTIME;
	int COUNT; //������
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