#include "pcb.h"

int main()
{
	char ch;
	NODE *phead; //���
	init_list(&phead);
	creat_outM(phead);
	NODE *head;  //����
	init_list(&head);
	NODE *hd;    //���
	init_list(&hd);
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
			prisch_list(phead, head, hd);
			break;
		case 'r':
			roundsch_list(phead, head, hd);
			break;
		}
		break;
	}
	return 0;
}