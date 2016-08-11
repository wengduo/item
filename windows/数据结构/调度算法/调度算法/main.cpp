#include "pcb.h"

int main()
{
	char ch;
	NODE *phead; //外存
	init_list(&phead);
	creat_outM(phead);
	NODE *head;  //就绪
	init_list(&head);
	NODE *hd;    //完成
	init_list(&hd);
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