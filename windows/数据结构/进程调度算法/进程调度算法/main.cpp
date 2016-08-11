
#include "pcb.h"

int main()
{
	char ch;
	ANODE *phead; //外存
	init_A(&phead);
	creat_outM(phead);
	BNODE *head;  //内存
	init_B(&head);
	CNODE *hd;
	init_C(&hd);
	printf("请输入要选择调度的算法(p--优先数调度,r--时间片轮转法):\n");
	while (1)
	{
		do{
			ch = getchar();
			scanf("%c", &ch);
		} while (ch != 'p' && ch != 'r');

		switch (ch)
		{
		case 'p':
			prisch_AB(phead, head, hd);
			break;
		case 'r':
			roundsch_AB(phead, head, hd);
			break;
		}
		break;
	}
	return 0;
}

//Status Print(READYQueue ready, FINISHQueue finish)
//{                        //打印就绪队列中的进程状态
//	QueuePtr p, q;
//	p = ready.READY;
//	q = finish.FINISH;
//	//运行中的进程
//	if (ready.RUN->next != NULL)
//	{
//		printf("%s", ready.RUN->next->pcb.NAME);
//		printf(":%s\t", ready.RUN->next->pcb.STATE);
//		printf("优先数:%d\n", ready.RUN->next->pcb.PRIO);
//
//	}
//
//	//就绪队列的进程
//	while (p != ready.TAIL){
//		printf("%s", p->next->pcb.NAME);
//		printf(":%s\t", p->next->pcb.STATE);
//		printf("优先数:%d\n", p->next->pcb.PRIO);
//		p = p->next;
//	}
//	//完成队列的进程
//	while (q != finish.TAIL){
//		printf("%s", q->next->pcb.NAME);
//		printf(":%s\t", q->next->pcb.STATE);
//		printf("优先数:%d\n", q->next->pcb.PRIO);
//		q = q->next;
//	}
//	return OK;
//}
//
//Status Printr(READYQueue ready, FINISHQueue finish){                        //打印就绪队列中的进程状态
//	QueuePtr p, q;
//	p = ready.READY;
//	q = finish.FINISH;
//	//运行中的进程
//	if (ready.RUN->next != NULL)
//	{
//		printf("%s", ready.RUN->next->pcb.NAME);
//		printf(":%s\t", ready.RUN->next->pcb.STATE);
//		printf("剩余时间:%d\n", ready.RUN->next->pcb.NEEDTIME);
//
//	}
//
//	//就绪队列的进程
//	while (p != ready.TAIL){
//		printf("%s", p->next->pcb.NAME);
//		printf(":%s\t", p->next->pcb.STATE);
//		printf("剩余时间:%d\n", p->next->pcb.NEEDTIME);
//		p = p->next;
//	}
//	//完成队列的进程
//	while (q != finish.TAIL){
//		printf("%s", q->next->pcb.NAME);
//		printf(":%s\t", q->next->pcb.STATE);
//		printf("剩余时间:%d\n", q->next->pcb.NEEDTIME);
//		q = q->next;
//	}
//	return OK;
//}
//
//Status Create(READYQueue &ready){
//	QueuePtr p;
//	int i = 0;
//	int n;
//	printf("请输入进程个数:");
//	scanf("%d", &n);
//	while (i<n)
//	{
//		p = (QueuePtr)malloc(sizeof(QNode));
//		printf("输入第%d进程名:", i + 1);
//		scanf("%s", p->pcb.NAME);
//		printf("输入进程需要的时间:");
//		scanf("%d", &p->pcb.NEEDTIME);
//		printf("输入进程的进程优先数:");
//		scanf("%d", &p->pcb.PRIO);
//		p->pcb.STATE = "W";
//		p->pcb.ROUNT = 2;
//		p->pcb.COUNT = 0;
//		i++;
//		p->next = NULL;
//		ready.TAIL->next = p;
//		ready.TAIL = p;
//	}
//
//	return OK;
//}
//
//Status Fisrt(READYQueue &ready){
//	if (ready.READY == ready.TAIL)
//		return ERROR;
//	ready.RUN->next = ready.READY->next;
//	ready.RUN->next->pcb.STATE = "RUN";     //修改进程状态
//	if (ready.TAIL == ready.READY->next)
//		ready.READY = ready.TAIL;
//	else
//		ready.READY->next = ready.READY->next->next;  //头指针后移
//
//	printf("\n%s被从就绪队列调度运行\n", ready.RUN->next->pcb.NAME);
//	return OK;
//}
//
//Status Insert1(READYQueue &ready){
//	int i = 0, j = 0;
//	QueuePtr p = ready.READY, q;
//	ElemPCB temp;
//
//	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
//	s->pcb = ready.RUN->next->pcb;
//	s->next = NULL;					//将未完成的进程插入就绪队列
//	ready.TAIL->next = s;
//	ready.TAIL = s;
//
//	//按优先数从大到小排序
//	for (p; p != ready.TAIL; p = p->next)
//	{
//		for (q = p->next; q != ready.TAIL; q = q->next)
//		{
//			if (p->next->pcb.PRIO < q->next->pcb.PRIO)
//			{
//				temp = p->next->pcb;
//				p->next->pcb = q->next->pcb;
//				q->next->pcb = temp;
//			}
//		}
//	}
//
//
//
//	return OK;
//
//}
//Status Insert2(READYQueue &ready){
//	QueuePtr p = ready.RUN->next;
//	if (p->pcb.NEEDTIME > 0)
//	{
//		ready.TAIL->next = p;   //插入到就绪队列
//		ready.TAIL = p;
//		ready.RUN->next = NULL;
//
//	}
//	return OK;
//
//}
//
//Status Prisch(READYQueue &ready, FINISHQueue &finish){
//	int i = 0;
//
//	while (ready.RUN->next != NULL)
//	{
//		ready.RUN->next->pcb.CPUTIME++;
//		ready.RUN->next->pcb.NEEDTIME--;
//		ready.RUN->next->pcb.PRIO -= 3;
//
//		if (ready.RUN->next->pcb.NEEDTIME == 0)
//		{
//
//			finish.TAIL->next = ready.RUN->next;     //插入到完成队列
//			finish.TAIL = ready.RUN->next;           //尾指针后移
//			ready.RUN->next->pcb.STATE = "FINISH";
//			ready.RUN->next = NULL;
//
//			if (ready.READY != ready.TAIL)
//			{
//				Fisrt(ready);
//			}
//
//		}
//		else if (ready.READY != ready.TAIL && (ready.RUN->next->pcb.PRIO) < (ready.READY->next->pcb.PRIO))
//		{
//			ready.RUN->next->pcb.STATE = "W";
//			printf("%s被调到就绪队列里\n", ready.RUN->next->pcb.NAME);
//			Insert1(ready);
//			Fisrt(ready);
//		}
//
//		i++;
//		printf("\n进程执行第%d个时间片的结果：\n", i);
//		Print(ready, finish);
//	}
//	return OK;
//}
//
//Status Roundsch(READYQueue &ready, FINISHQueue &finish){
//	int i = 0;
//	while (ready.RUN->next != NULL)
//	{
//		ready.RUN->next->pcb.CPUTIME++;
//		ready.RUN->next->pcb.NEEDTIME--;
//		ready.RUN->next->pcb.COUNT++;
//		if (ready.RUN->next->pcb.NEEDTIME == 0)
//		{
//			finish.TAIL->next = ready.RUN->next;     //插入到完成队列
//			finish.TAIL = ready.RUN->next;           //尾指针后移
//			ready.RUN->next->pcb.STATE = "FINISH";
//			ready.RUN->next = NULL;
//
//			if (ready.READY != ready.TAIL)
//			{
//				Fisrt(ready);
//			}
//		}
//		else if (ready.RUN->next->pcb.COUNT == ready.RUN->next->pcb.ROUNT)
//		{
//			ready.RUN->next->pcb.COUNT = 0;
//			if (ready.READY != ready.TAIL)
//			{
//				ready.RUN->next->pcb.STATE = "W";
//				printf("%s被调到就绪队列里\n", ready.RUN->next->pcb.NAME);
//				Insert2(ready);
//				Fisrt(ready);
//
//			}
//		}
//		i++;
//		printf("\n进程执行第%d个时间片的结果：\n", i);
//		Printr(ready, finish);
//	}
//	return OK;
//}
//
