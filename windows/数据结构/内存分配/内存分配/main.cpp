#define _CRT_SECURE_NO_WARNINGS
#include "seq.h"


int main()
{
	printf("�������ڴ��С\n");
	int n;
	scanf("%d", &n);
	NODE *phead;  //������
	init_list(&phead, 0);
	init_list_a(phead, n);
	//init_list_b(phead, n);
	NODE *head;
	init_list(&head, 0);
	NODE *hd;
	init_list(&hd, 0);
	printf("�״���Ӧ�㷨-1 ѭ���״���Ӧ�㷨-2 �����Ӧ�㷨-3 ���Ӧ�㷨-4\n");
	int ch;
	scanf("%d", &ch);
	while (1)
	{
		if (ch == 1)
		{
			first_fit(phead, head, hd);
			break;
		}
		else if (ch == 2)
		{
			next_fit(phead, head);
			break;
		}
		else if (ch == 3)
		{
			best_fit(phead, head);
			break;
		}
		else if (ch == 4)
		{
			best_fit1(phead, head);
			break;
		}
	}
	return 0;
}