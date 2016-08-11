#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
/*int float_to_int(float f)
{
	unsigned int i = *(int *)&f;
	int sign = 0;
	int exp = 0;
	int man = 0;

	if (i >> 31 == 0)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	int k;
	int m;
	exp = (k = ((i << 1) >> 24)) - 127;
	if (exp > 23)
	{
		man = (m = (((i << 8) >> 8) | 0x00800000)) << (exp - 23);
	}
	else
	{
		man = (((i << 8) >> 8) | 0x00800000) >> (23 - exp);
	}

	return (sign*man);
}
int main()
{


	printf("%d\n", float_to_int(100221221.125f));
	return 0;
}*/
/*typedef struct st_type
{
	int i;
	int a[0];
}type_a;
int main()
{
	type_a *p = (type_a*)malloc(sizeof(type_a)+100 * sizeof(int));
	type_a i = { 40, 50, 50 };
	printf("%d\n", sizeof(type_a));
	printf("%d %d %d\n", i.i, i.a[0], i.a[1]);
	return 0;
}

#include <memory.h>
#include <string.h>
#include <stdio.h>

char string1[60] = "The quick brown dog jumps over the lazy fox";
char string2[60] = "The quick brown fox jumps over the lazy dog";
                          1         2         3         4         5
*                  12345678901234567890123456789012345678901234567890
*/
/*int main()
{
	printf("Source:\t\t%s\n", string1 + 40);
	printf("Destination:\t%s\n", string1 + 16);
	memcpy(string1 + 10, string1 + 4, 40);
	printf("Result:\t\t%s\n", string1);
	printf("Length:\t\t%d characters\n\n", strlen(string1));
	memcpy(string1 + 16, string2 + 40, 3);
	printf("Function:\tmemmove with overlap\n");
	printf("Source:\t\t%s\n", string2 + 4);
	printf("Destination:\t%s\n", string2 + 10);
	memmove(string2 + 10, string2 + 4, 40);
	printf("Result:\t\t%s\n", string2);
	printf("Length:\t\t%d characters\n\n", strlen(string2));
	printf("Function:\tmemcpy with overlap\n");
	printf("Source:\t\t%s\n", string1 + 4);
	printf("Destination:\t%s\n", string1 + 10);
	memcpy(string1 + 10, string1 + 4, 40);
	printf("Result:\t\t%s\n", string1);
	printf("Length:\t\t%d characters\n\n", strlen(string1));
	return 0;
}
*/
/*
int func(int n)
{
	return -n;
}
int main()
{

	int i = 10;
	printf("%d\n", func(i));
	return 0;
}
*/
/*
int func(int m, int n)
{
	int sum=0;
	for (int i = m; i <=  n; i++)
	{
		sum = sum + i;
	}
	return sum;
}
int main()
{
	printf("%d\n", func(10, 20));
	return 0;
}}
void swap(int i, int j)
{
	int tmp;
	tmp = i;
	i = j;
	j = tmp;

}
int main()
{
	int x = 20;
	int y = 200;
	printf("d%\n", x);
	return 0;
}*/
//接受输入无限制
/*char *get_input(char end)
{
	char ch;
	int size=10;
	char *buff = (char *)malloc(sizeof(char)*size);
	assert(buff!=NULL);
	char *tmp = buff;
	int count = 0;
	while ((ch = getchar()) != end)
	{
		*buff++ = ch;
		count++;
		if (count >= size)
		{
			tmp = (char *)realloc(tmp, size*size);
			size = size*size;
			buff = tmp + count;
		}
	}
	*buff = 0;
	return tmp;
}
int main()
{
	char *str = get_input('\n');
	printf("%s\n",str);
	free(str);
	return 0;
}*/
//malloc(0)   realloc(p,0)
/*define MALLOC 
void *alloc(size_t size)
{
	void *new_mem = malloc(size);
	if (new_mem == NULL)
	{
		printf("alloc mem error\n");
		exit(-1);
	}
	return new_mem;
}
int main()
{
	int *new_mem = MALLOC(10, int);
	return 0;
}*/

//
/*int main()
{

	return 0;
}*/

//关机程序
/*void func()
{
	char input[100];
	char buff[100] = "你也爱我";
	scanf_s("%s", &input);
	flag:system("shutdown -s -t 30");
	if (memcmp(input, buff, strlen(input)) == 0)
	{
		printf("请在输入一次你爱我，以表真心\n");
		func();
	}
	else
	{
		printf("原来你不爱我\n");
		goto flag;
	}
}
int main()
{
	printf("请输入你也爱我，不然就关机\n");
	func();
	return 0;
}
int main()
{
	char *p = (char *)malloc(sizeof(char)* 0);
	printf("%s\n", p);
	char *p1 = (char *)malloc(sizeof(char)* 10);
	void *s = realloc(p1, 0);
	free(p);
	free(p1);
	return 0;
}


struct y
{
	char mail[30];
	char username[20];
	char name[10];
	char id[25];
	char password[20];
	char telephone[20];
	char mail1[30];
}*p;
int main()
{
	FILE *fr = fopen("g:\\12306.txt", "r");
	assert(fr != NULL);
	char buff[200];
	char buff1[20];
	int  select;
	int line = 0;
	struct y *p = (struct y *)malloc(sizeof(struct y) * 160000);
	struct y *s = p;
	assert(p != NULL);
	while (fgets(buff, 200, fr) != NULL)
	{
		strcpy(p->mail, strtok(buff, "-\n"));
		strcpy(p->username, strtok(NULL, "-\n"));
		strcpy(p->name, strtok(NULL, "-\n"));
		strcpy(p->id, strtok(NULL, "-\n"));
		strcpy(p->password, strtok(NULL, "-\n"));
		strcpy(p->telephone, strtok(NULL, "-\n"));
		strcpy((p++)->mail1, strtok(NULL, "-\n"));
		line++;
	}
	p = s;
	scanf("%d", &select);
	switch (select)
	{
	case 1:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (strncmp(s->mail, buff1, strlen(buff1)) == 0)
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		break;
	case 2:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (strncmp(s->username, buff1, strlen(buff1)) == 0)
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		break;
	case 3:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (0 == strncmp(s->name, buff1, strlen(buff1)))
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		s = p;
		break;
	case 4:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (strncmp(p->id, buff1, strlen(buff1)) == 0)
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		break;
	case 5:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (strncmp(s->password, buff1, strlen(buff1)) == 0)
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		break;
	case 6:scanf("%s", &buff1);
		for (int i = 0; i <= line; i++)
		{
			if (strncmp(s->telephone, buff1, strlen(buff1)) == 0)
			{
				printf("%s----%s----%s----%s----%s----%s----%s\n", s->mail, s->username,
					s->name, s->id, s->password, s->telephone, s->mail1);
			}
			s++;
		}
		break;
	default:printf("输入不合理\n");
	}
	free(p);
	return 0;
}
int my_delete(char *p, char *s)
{
	char *tmp = p;
	int k = strlen(s);
	char *f = strstr(p, s);
	if (f == NULL)
	{
		return 0;
	}
	else
	{
		p = f+k;
		while (*f++ = *p++);
		printf("%s\n", tmp);
		return 1;
	}
}
int main()
{
	char a[] = "adbccvyu";
	char b[] = "adbd";
	printf("%d\n",my_delete(a, b));
	return 0;
}*/
int main()
{

	return 0;
}