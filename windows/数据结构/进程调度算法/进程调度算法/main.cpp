
#include "pcb.h"

int main()
{
	char ch;
	ANODE *phead; //���
	init_A(&phead);
	creat_outM(phead);
	BNODE *head;  //�ڴ�
	init_B(&head);
	CNODE *hd;
	init_C(&hd);
	printf("������Ҫѡ����ȵ��㷨(p--����������,r--ʱ��Ƭ��ת��):\n");
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
//{                        //��ӡ���������еĽ���״̬
//	QueuePtr p, q;
//	p = ready.READY;
//	q = finish.FINISH;
//	//�����еĽ���
//	if (ready.RUN->next != NULL)
//	{
//		printf("%s", ready.RUN->next->pcb.NAME);
//		printf(":%s\t", ready.RUN->next->pcb.STATE);
//		printf("������:%d\n", ready.RUN->next->pcb.PRIO);
//
//	}
//
//	//�������еĽ���
//	while (p != ready.TAIL){
//		printf("%s", p->next->pcb.NAME);
//		printf(":%s\t", p->next->pcb.STATE);
//		printf("������:%d\n", p->next->pcb.PRIO);
//		p = p->next;
//	}
//	//��ɶ��еĽ���
//	while (q != finish.TAIL){
//		printf("%s", q->next->pcb.NAME);
//		printf(":%s\t", q->next->pcb.STATE);
//		printf("������:%d\n", q->next->pcb.PRIO);
//		q = q->next;
//	}
//	return OK;
//}
//
//Status Printr(READYQueue ready, FINISHQueue finish){                        //��ӡ���������еĽ���״̬
//	QueuePtr p, q;
//	p = ready.READY;
//	q = finish.FINISH;
//	//�����еĽ���
//	if (ready.RUN->next != NULL)
//	{
//		printf("%s", ready.RUN->next->pcb.NAME);
//		printf(":%s\t", ready.RUN->next->pcb.STATE);
//		printf("ʣ��ʱ��:%d\n", ready.RUN->next->pcb.NEEDTIME);
//
//	}
//
//	//�������еĽ���
//	while (p != ready.TAIL){
//		printf("%s", p->next->pcb.NAME);
//		printf(":%s\t", p->next->pcb.STATE);
//		printf("ʣ��ʱ��:%d\n", p->next->pcb.NEEDTIME);
//		p = p->next;
//	}
//	//��ɶ��еĽ���
//	while (q != finish.TAIL){
//		printf("%s", q->next->pcb.NAME);
//		printf(":%s\t", q->next->pcb.STATE);
//		printf("ʣ��ʱ��:%d\n", q->next->pcb.NEEDTIME);
//		q = q->next;
//	}
//	return OK;
//}
//
//Status Create(READYQueue &ready){
//	QueuePtr p;
//	int i = 0;
//	int n;
//	printf("��������̸���:");
//	scanf("%d", &n);
//	while (i<n)
//	{
//		p = (QueuePtr)malloc(sizeof(QNode));
//		printf("�����%d������:", i + 1);
//		scanf("%s", p->pcb.NAME);
//		printf("���������Ҫ��ʱ��:");
//		scanf("%d", &p->pcb.NEEDTIME);
//		printf("������̵Ľ���������:");
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
//	ready.RUN->next->pcb.STATE = "RUN";     //�޸Ľ���״̬
//	if (ready.TAIL == ready.READY->next)
//		ready.READY = ready.TAIL;
//	else
//		ready.READY->next = ready.READY->next->next;  //ͷָ�����
//
//	printf("\n%s���Ӿ������е�������\n", ready.RUN->next->pcb.NAME);
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
//	s->next = NULL;					//��δ��ɵĽ��̲����������
//	ready.TAIL->next = s;
//	ready.TAIL = s;
//
//	//���������Ӵ�С����
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
//		ready.TAIL->next = p;   //���뵽��������
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
//			finish.TAIL->next = ready.RUN->next;     //���뵽��ɶ���
//			finish.TAIL = ready.RUN->next;           //βָ�����
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
//			printf("%s����������������\n", ready.RUN->next->pcb.NAME);
//			Insert1(ready);
//			Fisrt(ready);
//		}
//
//		i++;
//		printf("\n����ִ�е�%d��ʱ��Ƭ�Ľ����\n", i);
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
//			finish.TAIL->next = ready.RUN->next;     //���뵽��ɶ���
//			finish.TAIL = ready.RUN->next;           //βָ�����
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
//				printf("%s����������������\n", ready.RUN->next->pcb.NAME);
//				Insert2(ready);
//				Fisrt(ready);
//
//			}
//		}
//		i++;
//		printf("\n����ִ�е�%d��ʱ��Ƭ�Ľ����\n", i);
//		Printr(ready, finish);
//	}
//	return OK;
//}
//
