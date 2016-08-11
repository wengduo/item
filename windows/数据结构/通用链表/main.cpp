#include<stdio.h>
#include<vld.h>
#include "seq.h"
#include<ctype.h>
void zhong_hou(char *p)
{
	char buff1[100];
	int i = 0;
	NODE *s;
	list_init(&s);
	while (*p)
	{
		if (isdigit(*p))
		{
			buff1[i++] = *p++;
		}
		else if (*p == ' ')
		{
			p++;
		}
		else
		{
			if (list_iskong(s))
			{
				list_insert(s, p,0);
			}
			else
			{
				GetTopD(&stack, &op);
				*mid               op
					//待比较的操作符，   栈顶的操作符
				if (*mid > op)//   PrioCom(*mid,OUT,op,IN)
				{
					Push(&stack, *mid);
					mid++;
				}
				else if (*mid < op)
				{
					do
					{
						Pop(&stack, &op);
						*last = op;
						last++;
						GetTopD(&stack, &op);
					} while (*mid < op);//继续比较

					Push(&stack, *mid);
				}
				else
				{
					Pop(&stack, &op);
					mid++;
				}
		}
	}
	list_destory(s);
}
int main()
{
	
	
	
	
	return 0;
}

