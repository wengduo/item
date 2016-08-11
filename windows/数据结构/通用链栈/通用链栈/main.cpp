#include<stdio.h>
#include<vld.h>
#include"seq.h"



static void print(void *date, char ps)
{
	switch (ps)
	{
	case 'i':
		printf("%d ", *(int *)date);
		break;
	case 'c':
		printf("%c ", *(char *)date);
		break;
	case 'd':
		printf("%lf ", *(double *)date);
		break;
	case 'f':
		printf("%f ", *(float *)date);
		break;
	default:
		printf("类型错误\n");
		break;
	}

}
bool mycompare(void *date, void *val, char ps)
{
	switch (ps)
	{
	case 'i':
		if (*(int *)date == *(int *)val)
		{
			return true;
		}
		return false;
	case 'c':
		if (strncmp((char *)date, (char *)val, 1) == 0)
		{
			return true;
		}
		return false;
	case 'd':
		if (*(double *)date == *(double *)val)
		{
			return true;
		}
		return false;
	case 'f':
		if (*(float *)date == *(float *)val)
		{
			return true;
		}
		return false;
	default:
		printf("类型错误\n");
		return false;
	}
}
int main()
{
	NODE s;
	list_init(&s);
	double a = 10;
	double b = 20;
	double c = 30;
	list_insert(&s, 0, &a);
	list_insert(&s, 0, &b);
	list_insert(&s, 0, &c);
	list_display(&s, print, 'd');
	printf("\n");
	printf("%d\n", list_length(&s));
	//double j = 10;
	//printf("%d\n",list_dizhi(&s, &j, mycompare, 'd'));
	list_delete(&s, 2);
	list_delete(&s, 1);
	list_display(&s, print, 'd');
	list_destory(&s);
	
	return 0;
}

