#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int left = 0;
	int right = 0;
	int k = 1;
	FILE *fr = fopen("f:\\2.txt", "r");
	if (fr == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	char ch;
	while ((ch = fgetc(fr)) != EOF)
	{
		if (ch == '"')
		{
			k=k*(-1);
		}
		else if (ch == '/')
		{
			ch = fgetc(fr);
			if (ch == '/')
			{
				while ((ch = fgetc(fr)) != '\n')
				{
					;
				}
			}
			else if (ch == '*')
			{
				ch = fgetc(fr);
				while (((ch = fgetc(fr)) != '*') && (((ch = fgetc(fr)) != '/')))
				{
					;
				}
			}
		}
		else
		{
			if (k==1)
			{
				if (ch == '{')
				{
					left++;
				}
				else if (ch == '}')
				{
					right++;
				}
			}
		}
	}
	if (left == right)
	{
		printf("代码规范\n");
		printf("%d-%d\n", left, right);
	}
	else
	{
		printf("代码不规范\n");
	}
	return 0;
}
int main()
{
	FILE *fr = fopen("f:\\1.txt", "r");
	if(fr==NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	FILE *fw = fopen("f:\\3.txt", "w");
	int k = 0;
	int i = 0;
	char ch;
	char ck;
	fw = fr;
	while ((ch = fgetc(fr)) != EOF)
	{
		if (ch == '\n')
		{
			if (i > k)
			{
				k = i;
				fw = fr;
			}
			i = 0;
		}
		i++;
	}
	while ((ck= fgetc(fw)) != '\n')
	{
		printf("%c\n", ck);
	}
	return 0;
}
int main()
{
	printf("%d\n", sizeof(short));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(long));
	printf("%d\n", sizeof(long long));
	return 0;
}
int main()
{
	char ch;
	int count = 1;
	int k = 1;
	while ((ch = getchar()) != EOF)
	{
		if (k ==1)
		{
			printf("%d:", count++);
			k++;
		} 
		if (ch == '\n')
		{
			k = 1;
		}
		putchar(ch);
	}
	return 0;
}
int main()
{
	FILE *fr = fopen("f:\\2.txt", "r");
	if (fr == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}
	char buff1[200];
	char buff2[200] = { 'h' };
	while (fgets(buff1, 200, fr) != NULL)
	{
		strlen(buff1);
		if (strlen(buff1) > strlen(buff2))
		{
			strcpy(buff2, buff1);
		}
	}
	printf("%s\n", buff2);
	return 0;
}
int main()
{
	long a = 1222222;
	short b = 0;
	b = a;
	printf("%d\n", b);
	return 0;
}
int main()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("%d\n", i);
	}
	return 0;
}
char *func( char x)
{
	char str[4088] = "123456789";
	return str;
}
int main()
{
	char x = 0;
	char *h = func(x);
	printf("%s\n",h);
	return 0;
}
void copy_n(char *p, char *s, int n)
{
	int i;
	for (i = 0; i <n; i++)
	{
		if (*p !='\0')
		{
			*s++ = *p++;
		}
		else
		{
			while (i < n)
			{
				*s++= 0;
				i++;
			}
		}
	}
	*s = '\0';
}
int main()
{
	char src1[] = "bs";
	char dst1[100] = "";
	int n = 1;
	copy_n(src1, dst1, n);
	for (int i = 0; i < 2; i++)
	{
		printf("%s", dst1);
	}
	printf("%s\n", dst1);
	return 0;
}
int float_to_int(float f)
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
	exp = (k=((i << 1) >> 24))-127; 
	if (exp > 23)
	{
		man =(m=(((i << 8) >> 8) | 0x00800000))<< (exp - 23);
	}
	else
	{
		man =(((i << 8) >> 8) | 0x00800000 )>> (23 - exp);
	}
	return (sign*man);
}
int main()
{
	printf("%d\n", float_to_int(1002121.125f));
	return 0;
}
int double_to_longlong(double f)
{
	unsigned long long i = *(long long *)&f;
	long long sign = 0;
	long long exp = 0;
	long long man = 0;
	if (i >> 63 == 0)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	long long k;
	long long m;
	exp = (k = ((i << 1) >> 52)) - 1023;
	if (exp > 52)
	{
		man = (m = (((i << 11) >> 11) | 0x00800000)) << (exp - 52);
	}
	else
	{
		man = (((i << 11) >> 11) | 0x00800000) >> (52 - exp);
	}
	return (sign*man);
}
int main()
{
	double k = 12.125;
	printf("%d\n", double_to_longlong(k));
	return 0;
}
//返回一个二进制数中有几个1
int func(int x)
{
	int countx = 0; 
	while (x)
	{
		countx++;
		x = x&(x - 1);
	}
	return countx++;
}
int main()
{
	printf("%d\n", func(5));
	return 0;
}

int main()
{
	int x = 10;
	int y = 20;
	int k = (~x& y) | ((~x | y)& (x - y));
	int m = (x - y) ^ ((x^y)& ((x - y) ^ x));
	return 0;
}
union node
{ 
	int a;
	char b[4];
};
int main()
{
	union node t;
	t.a=1;
	printf("%d\n",t.b[0]); 
	printf("%d\n",t.b[1]); 
	printf("%d\n",t.b[2]);
	printf("%d\n",t.b[3]);
}