#include "pcb.h"
int n1;
bool init_list(NODE **phead)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	assert(tmp != NULL);
	
	tmp->COUNT = 0;
	tmp->CPUTIME = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->tail = NULL;

	(*phead) = tmp;
	(*phead)->tail = tmp;

	return true;
}

NODE* insert_list(NODE *phead)
{
	if (phead == NULL)
	{
		return NULL;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE)* 1);
	assert(tmp != NULL);
	tmp->next = NULL;
	tmp->prev = NULL;

	return tmp;
}

bool list_add(NODE *phead, NODE *tmp)
{
	if (phead == NULL)
	{
		return false;
	}

	NODE *pt = phead;
	if (pt->next == NULL)
	{
		phead->next = tmp;
		tmp->prev = phead;

		return true;
	}

	while (pt->next != NULL)
	{
		NODE *pt1 = pt;
		pt = pt->next;

		if (pt->pcb.NOWTIME > tmp->pcb.NOWTIME)
		{
			pt1->next = tmp;
			tmp->prev = pt1;
			tmp->next = pt;
			pt->prev = tmp;

			break;
		}
		if (pt->next == NULL)
		{
			pt->next = tmp;
			tmp->prev = pt;
			break;
		}
	}
	return true;
}

static bool display_A(NODE *phead)
{
	if (phead == NULL)
	{
		return 0;
	}

	printf("外存队列\n");
	printf("进程名 进程状态 到达时间 使用时间 优先级\n");

	NODE *p = phead->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	 %d	  %d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO);
		printf("\n");
		p = p->next;
	}

	return 0;
}

static bool display_B(NODE *phead)
{
	if (phead == NULL)
	{
		return 0;
	}

	printf("就绪队列\n");
	printf("进程名 进程状态 到达时间 使用时间 优先级\n");

	NODE *p = phead->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	 %d	  %d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO);
		printf("\n");
		p = p->next;
	}

	return 0;
}

static bool display_C(NODE *phead)
{
	if (phead == NULL)
	{
		return 0;
	}

	printf("完成队列\n");
	printf("进程名 进程状态 到达时间 使用时间 优先级 完成时间\n");

	NODE *p = phead->next;
	while (p != NULL)
	{
		printf("%s	%c	%d	 %d	   %d	 %d", p->pcb.NAME, p->pcb.S, p->pcb.NOWTIME, p->pcb.NEEDTIME, p->pcb.PRIO,p->pcb.VOERTIME);
		printf("\n");
		p = p->next;
	}

	return 0;
}
bool creat_outM(NODE *phead)
{
	if (phead == NULL)
	{
		return false;
	}

	int i = 0;
	printf("请输入进程个数:");
	scanf("%d", &n1);
	while (i < n1)
	{
		NODE *tmp = insert_list(phead);
		printf("输入第%d进程名:", i + 1);
		scanf("%s", &tmp->pcb.NAME);
		printf("输入进程到达的时间:");
		scanf("%d", &tmp->pcb.NOWTIME);
		printf("输入进程需要的时间:");
		scanf("%d", &tmp->pcb.NEEDTIME);
		printf("输入进程的进程优先级:");
		scanf("%d", &tmp->pcb.PRIO);
		tmp->pcb.S = 'W';
		tmp->pcb.VOERTIME = 0;
		tmp->pcb.ROUNT = 2;
		tmp->pcb.FH = 0;

		list_add(phead, tmp);
		i++;
	}
	display_A(phead);

	return true;
}

bool insert_B(NODE *phead,NODE *head, NODE *p)
{
	if (head == NULL)
	{
		return false;
	}

	NODE *p1 = head;
	NODE *p3 = p1;
	while (p1->next != NULL)
	{
		p3 = p1;
		p1 = p1->next;

	}
	if (p1->pcb.FH == phead->COUNT)
	{
		printf("errorllll\n");
		p3->next = p;
		p->next = p1;
		p1->prev = p;
		p->prev = p3;
	}
	else
	{
		p1->next = p;
		p->next = NULL;
		p->prev = p1;
		head->tail = p;
	}
	return true;
}
void my_diaodu(NODE *phead, NODE *head)
{
	if (phead->next == NULL)
	{
		return;
	}
	NODE *p = phead->next;
	while (phead->COUNT == p->pcb.NOWTIME)
	{
		p->pcb.S = 'S';
		phead->next = p->next;
		if (p->next != NULL)
		{
			p->next->prev = phead;
		}
		insert_B(phead,head, p);
		p = phead->next;
		if (p == NULL)
		{
			break;
		}
	}
}

int NODE_length(NODE *hd)
{
	if (hd->next == NULL)
	{
		return 0;
	}

	int count = 0;
	NODE *p = hd->next;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}

	return count;
}

bool insert_C(NODE *hd, NODE *p)
{
	if (hd == NULL)
	{
		return false;
	}

	NODE *p1 = hd;
	while (p1->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = p;
	p->next = NULL;
	p->prev = p1;
	return true;
}
bool my_zhixing(NODE *phead, NODE *head, NODE *hd, int n)
{
	if (head->next == NULL)
	{
		printf("error\n");
		return false;
	}

	NODE *p = head->next;
	p->pcb.NEEDTIME--;
	if (p->pcb.NEEDTIME == 0)
	{
		p->pcb.S = 'F';
		if ((n1-1) == NODE_length(hd))
		{
			p->pcb.VOERTIME = phead->COUNT;
		}
		else
		{
			p->pcb.VOERTIME = phead->COUNT + 1;
		}
		if (n == 1)
		{
			phead->COUNT++;
		}
		head->next = p->next;
		insert_C(hd, p);
		if (n == 1)
		{
			n--;
		}
	}
	if (p->pcb.NEEDTIME != 0 && n == 0)
	{
		if (p->next != NULL)
		{
			head->next = p->next;
			head->tail->next = p;
			p->pcb.S = 'S';
			p->pcb.FH = phead->COUNT + 1;
			head->tail = p;
			p->next = NULL;
			p->pcb.ROUNT = 2;
		}
	}

	return true;
}

void all_display(NODE *phead, NODE *head, NODE *hd)
{
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
void roundsch_list(NODE *phead, NODE *head, NODE *hd)
{
	if (phead->next == NULL)
	{
		printf("无进程\n");
		return;
	}
	int k = 6;
	while (1)
	{
		my_diaodu(phead, head);
		if (head->next != NULL)
		{
			head->next->pcb.S = 'R';
			int n = head->next->pcb.ROUNT;
			while (n--)
			{
				my_zhixing(phead,head,hd,n);
				phead->COUNT++;
				if (n != 0 && phead->next != NULL)
				{
					my_diaodu(phead, head);
				}
				
			}
			printf("第%d次时间轮转 cpu:%d\n", ++phead->CPUTIME,phead->COUNT);
			all_display(phead, head, hd);
		}
		else
		{
			phead->COUNT++;
		}
		if (NODE_length(hd) == n1)
		{
			break;
		}
	}
}

bool insert_BB(NODE *head, NODE *p)
{
	if (head == NULL)
	{
		return false;
	}

	NODE *tmp = (NODE *)malloc(sizeof(NODE));

	tmp = p;
	tmp->next = NULL;
	tmp->prev = NULL;

	NODE *pt = head;
	if (pt->next == NULL)
	{
		head->next = tmp;
		tmp->prev = head;

		return true;
	}

	while (pt->next != NULL)
	{
		NODE *pt1 = pt;
		pt = pt->next;

		if (pt->pcb.PRIO > tmp->pcb.PRIO)
		{
			pt1->next = tmp;
			tmp->prev = pt1;
			tmp->next = pt;
			pt->prev = tmp;

			break;
		}

		if (pt->next == NULL)
		{
			pt->next = tmp;
			tmp->prev = pt1;

			break;
		}
	}

	return true;
}


void my_diaodu1(NODE *phead, NODE *head)
{
	if (phead->next == NULL)
	{
		return;
	}
	NODE *p = phead->next;
	while (phead->COUNT >= p->pcb.NOWTIME)
	{
		p->pcb.S = 'S';
		phead->next = p->next;
		if (p->next != NULL)
		{
			p->next->prev = phead;
		}
		insert_BB(head, p);
		p = phead->next;
		if (p == NULL)
		{
			break;
		}
	}
}

bool my_zhixing1(NODE *phead,NODE *head, NODE *hd)
{
	if (head->next == NULL)
	{
		printf("error\n");
		return false;
	}

	NODE *p = head->next;
	p->pcb.NEEDTIME--;
	if (p->pcb.NEEDTIME == 0)
	{
		p->pcb.S = 'F';
		p->pcb.VOERTIME = phead->COUNT + 1;
		head->next = p->next;
		if (p->next != NULL)
		{
			p->next->prev = head;
		}
		insert_C(hd, p);
	}

	return true;
}
void prisch_list(NODE *phead, NODE *head, NODE *hd)
{
	if (phead->next == NULL)
	{
		printf("无进程\n");
		return;
	}
	while (1)
	{
		my_diaodu1(phead, head);
		if (head->next != NULL)
		{
			if (head->next->next != NULL)
			{
				head->next->next->pcb.S = 'R';
			}
			head->next->pcb.S = 'S';
			my_zhixing1(phead,head, hd);
			phead->COUNT++;
		}
		else
		{
			phead->COUNT++;
		}
		printf("第%d次优先级运行 cpu:%d\n", ++phead->CPUTIME, phead->COUNT);
		all_display(phead, head, hd);
		if (NODE_length(hd) == n1)
		{
			break;
		}
	}
}