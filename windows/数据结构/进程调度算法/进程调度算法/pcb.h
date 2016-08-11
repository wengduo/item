#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ERROR 0
#define OK 1


typedef struct _PCB
{
	char NAME[10];    //��������
	int PRIO;        //�������ȼ�
	int ROUNT;       //��תʱ��Ƭ       
	int NOWTIME;     //���̵���ʱ��
	int NEEDTIME;    //��Ҫ��CPUʱ��
	char S;      //����״̬
}PCB;

typedef struct _ANODE
{
	int CPUTIME;
	int COUNT; //������
	PCB pcb;
	struct _ANODE *next;
	struct _ANODE *prev;
}ANODE;

typedef struct _BNODE //��������
{      
	PCB pcb;
	struct _BNODE *next; 
	struct _BNODE *prev;  
	struct _BNODE *tail;   //βָ��
}BNODE;

typedef struct _CNODE    //��ɶ���
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