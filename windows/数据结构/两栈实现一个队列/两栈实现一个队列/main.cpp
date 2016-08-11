#include "stack.h"

int main()
{
	LINK_STACK phead1;
	LINK_STACK phead2;
	ELEM_TYPE e;
	InitStack(&phead1);
	InitStack(&phead2);
	for (int i = 1; i <= 10; i++)
	{
		printf("%d ", EnQueue(&phead1, &phead2, 10 * i));
	}
	printf("\n");
	for (int j = 1; j <= 8; j++)
	{
		printf("%d\n", DeQueue(&phead1, &phead2, &e));
	}
	return 0;
}