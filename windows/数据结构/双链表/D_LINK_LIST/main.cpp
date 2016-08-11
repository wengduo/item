#include "list.h"
#include<vld.h>

int main()
{
	HEAD head;
	
	InitDHead(&head);
	for (int i = 1; i<=8; i++)
	{
		InsertDHead(&head, i * 10);
		//InsertDTail(&head, i * 10);
	}
	printf("\n");
	//InsertDByPos(&head, 6, 5);
	//DeleteWhat(&head, 10);
	//DeleteWhere(&head, 10);
	//DisplayList(&head);
	//fanDList(&head);
	
	printf("%d\n", GetlengDList(&head));
	//InsertDByPos(&head, 10, 5);
	DisplayList(&head);
	int k = GetlengDList(&head);
	for (int i = 0; i < k; i++)
	{
		printf("0x%p ", head.arr[i]);
	}
	printf("\n");
	//huan_Dlist(&head);
	DestoryDList(&head);
	//free(head.arr);
	return 0;

}