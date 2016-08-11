#define _CRT_SECURE_NO_WARNINGS
#include"seq.h"
#include <ctype.h>
#include<string.h>
float EvalLast(char *p)
{
	float s1 = 0.0f;
	float s2 = 0.0f;
	float i = 1.0;
	NODE s;
	list_init(&s);
	p = strtok(p, " ");
	while (p != NULL)
	{
		if (isdigit(*p))
		{
			int k = strlen(p);
			s1 = *p++ - '0';
			k--;
			while (k>0)
			{
				if (strncmp(p, ".", 1) == 0)
				{
					p++;
					while (--k > 0)
					{
						s2 = s2 + (float)(*p - '0')/10;
						s1 = s1 + s2;
					}
				}
				else
				{
					s1 = s1 * 10 + (*p++ - '0');
				}
				k--;
			}
			printf("%lf\n", s1);
			list_insert(&s, 0, 0, s1);
		}
		else
		{
			switch (*p)
			{
			case '+':
				//printf("%lf\n", s.next->next->size + s.next->size);
				list_insert(&s,0 , 0, s.next->next->size + s.next->size);
				list_delete(&s, 1);
				list_delete(&s, 1);
				break;
			case '-':
				list_insert(&s, 0, 0, s.next->next->size - s.next->size);
				list_delete(&s, 1);
				list_delete(&s, 1);
				break;
			case '*':
				list_insert(&s, 0, 0, (s.next->next->size) * (s.next->size));
				list_delete(&s, 1);
				list_delete(&s, 1);
				break;
			case '/':
				//printf("%lf\n", s.next->next->size + s.next->size);
				list_insert(&s, 0, 0, (s.next->next->size) / (s.next->size));
				list_delete(&s, 1);
				list_delete(&s, 1);
				break;
			default:
				list_destory(&s);
				printf("胡写\n");
				exit(-1);
			}
			p++;
		}
		p = strtok(NULL, " ");
	}
	s1 = s.next->size;
	list_destory(&s);
	return s1;
}
bool bi_jiao(char *p,NODE *s)
{
	if (*p == '+' || *p == '-')
	{
		if (3 > s->next->size)
		{
			return true;
		}
		return false;
	}
	else if(*p == '*'||*p == '/')
	{
		if (5 > s->next->size)
		{
			return true;
		}
		return false;
	}
	else
	{
		if (*p == '(')
		{
			return true;
		}
		else if (*p == ')')
		{
			if (s->next->size == 2.0)
			{
				return true;
			}
			return false;
		}
		else
		{
			printf("运算符超限\n");
			exit(-1);
		}
	}
}

void jin_zhan(char *p, NODE *s)
{
	switch (*p)
	{
	case '+':
		list_insert(s, 0, p, 4.0);
		break;
	case '-':
		list_insert(s, 0, p, 4.0);
		break;
	case '*':
		list_insert(s, 0, p, 6.0);
		break;
	case '/':
		list_insert(s, 0, p, 6.0);
		break;
	case '(':
		list_insert(s, 0, p, 2.0);
		break;
	default:
		printf("运算符超限\n");
		list_destory(s);
		exit(-1);
	}
}
void zhong_hou(char *p)
{
	NODE s;
	list_init(&s);
	char *p1 = p;
	char buff1[100];
	int i = 0;
	while (*p)
	{
		if (isdigit(*p))
		{
			while (isdigit(*(p + 1))||(*(p+1) == '.'))
			{
				buff1[i++] = *p++;
			}
			buff1[i++] = *p++;
			buff1[i++] = ' ';
		}
		else if (*p == ' ')
		{
			p++;
		}
		else
		{
			if (list_iskong(&s))
			{
				jin_zhan(p,&s);
			}
			else
			{
				if (bi_jiao(p, &s))
				{
					jin_zhan(p, &s);
				}
				else 
				{
					char ps = *(char *)list_gettop(&s);
					do
					{
						
						if (ps != '(')
						{
							buff1[i++] = ps;
							buff1[i++] = ' ';
						}
						list_delete(&s, 0);
						if (list_iskong(&s))
						{
							break;
						}
						ps = *(char *)list_gettop(&s);
					} while (!bi_jiao(p, &s));
					if (*p == ')')
					{
						
						list_delete(&s, 0);
					}
					else
					{
						jin_zhan(p, &s);
					}
				}
			}
			p++;
		}
	}
	while (!list_iskong(&s))
	{
		char *ps = (char *)list_gettop(&s);
		buff1[i++] = *ps;
		buff1[i++] = ' ';
		list_delete(&s, 0);
	}
	buff1[i] = 0;
	memcpy(p1, buff1,strlen(buff1)+1);
}

int main()
{
	float rs = 0.0f;
	char buff[200]="6+(7-1)*3+10.5/2";
	printf("请输入四则表达式：");
	//gets(buff);
	printf("\n中缀表达式:%s\n", buff);
	zhong_hou(buff);
	printf("\n后缀表达式:%s\n", buff);
	rs = EvalLast(buff);
	printf("最终结果为%f\n", rs);

	return 0;
}
