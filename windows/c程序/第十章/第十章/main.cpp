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
		printf("内存申请失败");
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
//"r",有文件，返回非空，打开此文件
//"r"，无文件，返回NULL，无关联

//"w",有文件，清空该文件，建立关联，从头写
//"w"，无文件，新建该文件，建立关联

//"a", 有文件，建立关联，从文件末尾  追加写入
//"a"，无文件，新建该文件，建立关联
	FILE *fr = fopen("f:\\2.txt.txt","r");
	if (fr == NULL)
	{
		printf("文件打开失败\n");
		exit(-1);
	}

	FILE *fw = fopen("f:\\bak.txt","w");

	char ch;

	while((ch = fgetc(fr)) != EOF)
	{	
//把ch字符放到fw指针对应的文件中
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



return 0;//正常返回主函数
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
FILE *fr = fopen("D:\\Download\\电影\\虎虎虎.mkv","rb");
FILE *fw = fopen("D:\\Download\\电影\\bak.mkv","wb");
if (fr == NULL)
{
printf("error\n");
exit(-1);
}

//1.开辟一个比较大的内存空间，接收电影数据
char *buff = (char *)malloc(sizeof(char) * 100*1024*1024);
if (buff == NULL)
{
printf("error\n");
exit(-1);
}
size_t rs = 0;
while( (rs = fread(buff,sizeof(char), 100*1024*1024, fr)) == sizeof(char)*100*1024*1024)
{
//向目标文件，把buff里的100MB数据写入
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

	printf("请输出待查询内容:");
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






