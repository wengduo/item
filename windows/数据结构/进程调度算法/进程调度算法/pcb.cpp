#include "pcb.h"
int m = 2;

bool init_A(ANODE **phead)
{
	if (phead == NULL)
	{
		return false;
	}

	ANODE *tmp = (ANODE *)malloc(sizeof(ANODE)* 1);
	assert(tmp != NULL);
	tmp->next = NULL;
	tmp->COUNT = 0;
	tmp->CPUTIME = 0;
	tmp->prev = NULL;

	(*phead) = tmp;

	return true;
}

bool init_B(BNODE **head)
{
	if (head == NULL)
	{
		return false;
	}

	BNODE *tmp = (BNODE *)malloc(sizeof(BNODE)* 1);
	assert(tmp != NULL);
	tmp->next = NULL;
	tmp->tail = NULL;
	tmp->prev = NULL;

	(*head) = tmp;

	return true;
}

bool init_C(CNODE **hd)
{
	if (hd == NULL)
	{
		return false;
	}

	CNODE *tmp = (CNODE *)malloc(sizeof(CNODE)* 1);
	assert(tmp != NULL);
	tmp->next = NULL;
	tmp->prev = NULL;

	(*hd) = tmp;

	return true;
}

int ANODE_length(ANODE *phead)
{
	if (phead->next == NULL)
	{
		return 0;
	}

	int count = 0;
	ANODE *p = phead->next;
	while (p !=  NULL)
	{
		count++;
		p = p->next;
	}

	return count;
}

int CNODE_length(CNODE *hd)
{
	if (hd->next == NULL)
	{
		return 0;
	}

	int count = 0;
	CNODE *p = hd->next;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}

	return count;
}

ANODE* insert_A(ANODE *phead)
{
	if (phead == NULL)
	{
		return NULL;
	}

	ANODE *tmp = (ANODE *)malloc(sizeof(ANODE)* 1);
	assert(tmp != NULL);
	tmp->next = NULL;
	tmp->prev = NULL;

	ANODE *p = phead;
	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = tmp;
	tmp->prev = p;

	return tmp;
}

bool insert_B(BNODE *head, ANODE *p)
{
	if (head == NULL)
	{
		return false;
	}

	BNODE *tmp = (BNODE *)malloc(sizeof(BNODE)* 1);
	assert(tmp != NULL);
	tmp->pcb = p->pcb;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->tail = tmp;

	BNODE *p1 = head;
	while (p1->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = tmp;  //error
	tmp->prev = p1;

	return true;
}

bool insert_C(CNODE *hd,BNODE *p)
{
	if (hd == NULL)
	{
		return false;
	}

	CNODE *tmp = (CNODE *)malloc(sizeof(CNODE)* 1);
	assert(tmp != NULL);
	tmp->pcb = p->pcb;
	tmp->next = NULL;
	tmp->prev = NULL;

	CNODE *p1 = hd;
	while (p1->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = tmp;
	tmp->prev = p1;

	return true;
}

static bool display_A(ANODE *phead)
{
	if (phead == NULL)
	{
		return 0;
	}

	printf("外存队列\n");
	printf("进程名 进程状态 进程到达时间 进程使用时间 进程优先级\n");

	ANODE *p = phead->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	%d	%d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO);
		printf("\n");
		p = p->next;
	}

	return 0;
}

static bool display_B(BNODE *head)
{
	if (head == NULL)
	{
		return 0;
	}

	printf("就绪队列\n");
	printf("进程名 进程状态 进程到达时间 进程使用时间 进程优先级\n");

	BNODE *p = head->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	%d	%d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO);
		printf("\n");
		p = p->next;
	}

	return 0;
}

static bool display_C(CNODE *hd)
{
	if (hd == NULL)
	{
		return 0;
	}

	printf("完成队列\n");
	printf("进程名 进程状态 进程到达时间 进程使用时间 进程优先级\n");

	CNODE *p = hd->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	%d	%d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO);
		printf("\n");
		p = p->next;
	}

	return 0;
}

bool creat_outM(ANODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	int n;
	int i = 0;
	printf("请输入进程个数:");
	scanf("%d", &n);
	while (i < n)
	{
		ANODE *tmp = insert_A(phead);
		printf("输入第%d进程名:", i + 1);
		scanf("%s", &tmp->pcb.NAME);
		printf("输入进程到达的时间:");
		scanf("%d", &tmp->pcb.NOWTIME);
		printf("输入进程需要的时间:");
		scanf("%d", &tmp->pcb.NEEDTIME);
		printf("输入进程的进程优先级:");
		scanf("%d", &tmp->pcb.PRIO);
		tmp->pcb.S = 'w';
		tmp->pcb.ROUNT = 2;
		i++;
	}
	display_A(phead);

	return true;
}

void prisch_AB(ANODE *phead, BNODE *head, CNODE *hd)
{
	;
}




bool delete_A(ANODE *p)
{
	if (p == NULL)
	{
		return false;
	}

	p->prev->next = p->next;
	free(p);

	return true;
}

void my_diaodu(ANODE *phead, BNODE *head)
{
	if (phead->next == NULL)
	{
		printf("error1\n");
		exit(0);
		return;
	}
	ANODE *p = phead->next;
	while (p != NULL)
	{
		if (phead->COUNT >= p->pcb.NOWTIME)
		{
			p->pcb.S = 'R';
			insert_B(head, p);
			ANODE *p1 = p->next;
			delete_A(p);///////////error
			p = p1;
		}
		else
		{
			p = p->next;
		}
		
	}
}

bool my_zhixing(BNODE *head)
{
	if (head->next == NULL)
	{
		printf("error\n");
		return false;
	}

	BNODE *p = head->next;
	p->pcb.NEEDTIME--;
	p->pcb.ROUNT--;
	if (p->pcb.NEEDTIME == 0)
	{
		p->pcb.S = 'F';
	}

	return true;
}

void roundsch_AB(ANODE *phead, BNODE *head, CNODE *hd)
{
	if (phead->next == NULL)
	{
		printf("无进程\n");
	}

	ANODE *p = phead->next;
	while (1)
	{
		my_diaodu(phead, head);
		
		if (head->next != NULL)
		{
			int n = 2;
			while (n--)
			{
				my_zhixing(head);
				BNODE *p1 = head->next;
				if (p1 != NULL)
				{
					if (p1->pcb.NEEDTIME != 0)
					{
						p1->prev->next = p1->next;
						if (p1->next == NULL)
						{
							head->next = p1;
						}
						else
						{
							head->tail->next = p1;//error
							p1->next = NULL;
							p1->prev = head->tail;
							head->tail = p1;
						}
					}
					else
					{
						insert_C(hd, p1);
						p1->prev->next = p1->next;
						free(p1);
					}
				}

				phead->COUNT++;
				my_diaodu(phead, head);
			}

			phead->CPUTIME++;
			printf("第%d次时间轮转\n", phead->CPUTIME);
			if (phead->next != NULL)
			{
				display_A(phead);
			}
			if (head->next != NULL)
			{
				display_B(head);
			}
			if (hd->next != NULL)
			{
				display_C(hd);
			}
		}

		phead->COUNT++;
		if (CNODE_length(hd) == 2)
		{
			break;
		}
	}
}