#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>




/*void *my_calloc(size_t num, size_t size)
{
	char *p = (char *)malloc(sizeof(char)* 1024);
	if (p == NULL)
	{
		printf("�ڴ�����ʧ��");
		exit(-1);
	}
	char *tmp = p;
	int i = 0;
	for (size_t i = 0; i < num;i++)
	{
		*p = 0;
		p++;
	}
	return tmp;
}
int main()
{
	int *p=(int *)my_calloc( 10,sizeof(int));
	*p = 100;
	free(p);
	//printf("%s", *p);

	return 0;
}
void revword(char *p1, char *p2)
{
	char tmp = 0;
	int i = 0;
	int length = p2 - p1;
	p2--;


	while (i < length / 2)
	{
		tmp = *p2;
		*p2 = *p1;
		*p1 = tmp;

		i++;
		p1++;
		p2--;
	}
}

void func(char *str)
{
	char *start = str;
	while (*str)
	{
		if (*str == ' ')
		{
			revword(start, str);
			start = str + 1;
		}
		str++;
	}
	revword(start, str);
}

int main()
{
	char str[] = "hello world abc 1234567 ";

	_strrev(str);
	func(str);

	printf("%s\n", str);

	return 0;

}




int main()
{
//"r",���ļ������طǿգ��򿪴��ļ�
//"r"�����ļ�������NULL���޹���

//"w",���ļ�����ո��ļ���������������ͷд
//"w"�����ļ����½����ļ�����������

//"a", ���ļ����������������ļ�ĩβ  ׷��д��
//"a"�����ļ����½����ļ�����������
	FILE *fr = fopen("f:\\2.txt.txt","r");
	if (fr == NULL)
	{
		printf("�ļ���ʧ��\n");
		exit(-1);
	}

	FILE *fw = fopen("f:\\bak.txt","w");

	char ch;

	while((ch = fgetc(fr)) != EOF)
	{	
//��ch�ַ��ŵ�fwָ���Ӧ���ļ���
		fputc(ch, fw);
	}
	return 0;
}
int main()
{
	FILE *fw = fopen("f:\\10.txt","w");

	char ch = 0;

	while((ch = getchar()) != '#')
	{
		fputc(ch, fw);
	}
	return 0;

}


		int main()
		{
		FILE *fr = fopen("f:\\bak.txt","r");

		char ch;

		while((ch = fgetc(fr)) != EOF)
		{
		printf("%c",ch);
		}
		return 0;
		}



fgets
fputs

*/
int main()
{
FILE *fr = fopen("f:\\g.txt","r");
if (fr == NULL)
{
printf("error");
exit(-1);
}

char str1[50];
fgets(str1,50,fr);
char ch = '\n';

return 0;
}



/*
int main()
{
char str[] = "hello";
FILE *fw = fopen("c:\\f.txt","w");



fputs(str,fw);
fflush(fw);

fputs(str,fw);



fclose(fw);


int *p = NULL;
*p = 100;



return 0;//��������������
}



struct STU
{
int num;
char name[20];
double score;
};

int main()
{
struct STU su = {118,"yule",99.9};


return 0;
}


struct STU
{
int num;
char name[20];
double score;
};


int main()
{
struct STU su[3] = {{118,"liubei",99.9},{120,"guanyu",89.9},{10086,"zhangfei",59.9}};

FILE *fw = fopen("c:\\su.txt","wb");//   "wb"



fwrite(su,sizeof(struct STU),3,fw);


//fwrite(su, sizeof(su),1,fw);


//for (int i=0;i<3;i++)
//{
//	fwrite(su,sizeof(struct STU),1,fw);
//}

fclose(fw);

return 0;
}




int main()
{
FILE *fr = fopen("D:\\Download\\��Ӱ\\������.mkv","rb");
FILE *fw = fopen("D:\\Download\\��Ӱ\\bak.mkv","wb");
if (fr == NULL)
{
printf("error\n");
exit(-1);
}

//1.����һ���Ƚϴ���ڴ�ռ䣬���յ�Ӱ����
char *buff = (char *)malloc(sizeof(char) * 100*1024*1024);
if (buff == NULL)
{
printf("error\n");
exit(-1);
}
size_t rs = 0;
while( (rs = fread(buff,sizeof(char), 100*1024*1024, fr)) == sizeof(char)*100*1024*1024)
{
//��Ŀ���ļ�����buff���100MB����д��
fwrite(buff, sizeof(char), 100*1024*1024, fw);
}
fwrite(buff, sizeof(char), rs, fw);

//???

fclose(fw);
fclose(fr);

return 0;
}



int main()
{
	FILE * fr = fopen("f:\\12306.txt", "r");
	assert(fr != NULL);

	size_t line = 0;

	char buff[200];

	while (fgets(buff, 200, fr) != NULL)
	{
		line++;
	}
	printf("%u\n", line);


	char *p = (char *)malloc(sizeof(char)* 200 * line);//12W BYTE
	assert(p != NULL);

	fseek(fr, 0, SEEK_SET);

	int tmp = line;
	char *s = p;

	while (tmp--)
	{
		fgets(p, 200, fr);
		p = p + 200;
	}

	printf("���������ѯ����:");
	scanf("%s", buff);


	for (int i = 0; i<line; i++)
	{
		if (strstr(s, buff) != NULL)
		{
			printf("%s", s);
		}
		s += 200;
	}


	return 0;


}*/






