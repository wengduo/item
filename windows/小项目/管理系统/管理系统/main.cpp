#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

struct student
{
	char 姓名[10];
	char 年龄[3];
	char 性别[3];
	char 籍贯[30];
	char 学院[13];
	char 专业[10];
	char 电话[12];
	char 学号[10];
	char 年级[2];
}*p,*f,*f1;

struct zhuanye
{
	char 姓名[8];
	char 原学院[20];
	char 原专业[20];
	char 现学院[20];
	char 现专业[20];
}*s, *s1, *s2;
int n = 0;
int m = 0;
void GetInfo()
{
	int k;
	printf("请输入要输入几个人\n");

	scanf("%d", &k);	
	p += sizeof(p)*n;
	for (int i = 0; i<k; i++)
	{
		printf("输入学生的基本信息:姓名,年龄,性别,籍贯,学院,专业,电话,学号,年级\n");
		scanf("%s %s %s %s %s %s %s %s %s", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
			p->专业, p->电话, p->学号, p->年级);
		n++;
		p++;
	}
	p = f;
}
void my_change()
{
	char number[10];
	int pb = 0;
	int j = 0;
	printf("请输入学生学号:\n");
	scanf("%s", &number);
	printf("是否转专业,是按1,否按2\n");
	scanf("%d", &pb);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(p->学号,number) == 0)
		{
			if (pb == 1)
			{
				s += m;
				printf("学生的基本信息:姓名,年龄,性别,籍贯,学院,专业,电话,学号,年级\n");
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
				strcpy(s->原学院, p->学院);
				strcpy(s->原专业, p->专业);
				
				//memset(p, 0, sizeof(struct student)+1);
				printf("请输入学生的基本信息:姓名,年龄,性别,籍贯,学院,专业,电话,学号,年级\n");
				scanf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
				strcpy(s->姓名, p->姓名);
				strcpy(s->现学院, p->学院);
				strcpy(s->现专业, p->专业);
				s ++;
				s = s1;
				m++;
			}
			else
			{
				printf("学生的基本信息:姓名,年龄,性别,籍贯,学院,专业,电话,学号,年级\n");
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
				memset(p, 0, sizeof(struct student));
				printf("请输入学生的基本信息:姓名,年龄,性别,籍贯,学院,专业,电话,学号,年级\n");
				scanf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			printf("该学生已修改\n");
			j++;
		}
		p++;
	}
	p = f;
	if (j == 0)
	{
		printf("该学生不存在,请重新输入\n");
		my_change();
	}
}
void my_delete()
{
	char number[10];
	int j = 0;
	printf("请输入学生学号:\n");
	scanf("%s", number);
	for (int i = 0; i < n; i++)
	{
		if (strcmp( p->学号,number) == 0)
		{
			f++;
			for (j = 0; j < n; j++)
			{
				strcpy(p->姓名, f->姓名);
				strcpy(p->年龄, f->年龄);// 性别, 籍贯, 学院, 专业, 电话, 学号, 年级
				strcpy(p->性别, f->性别);
				strcpy(p->籍贯, f->籍贯);
				strcpy(p->学院, f->学院);
				strcpy(p->专业, f->专业);
				strcpy(p->电话, f->电话);
				strcpy(p->学号, f->学号);
				strcpy(p->年级, f->年级);
				strcpy(p->姓名, f->姓名);
				p ++;
				f ++;
			}
			n--;
			printf("该学生已删除!:\n");
			p = f1;
			f = f1;
		}
		else
		{
			f++;
			p++;
		}
	}
	if (j == 0)
	{
		printf("该学生不存在,请重新输入\n");
		my_delete();
	}
}
void my_print1()
{
	printf("*****欢迎使用本班级档案管理系统*****\n");
	printf("*********欢迎进入我们的系统*********\n");
	printf("*********学生基本信息录入,请按 1\n");
	printf("*********学生基本信息查看,请按 2\n");
	printf("*********学生基本信息修改,请按 3\n");
	printf("*********学生基本信息删除,请按 4\n");
	printf("*********看学生转专业信息,请按 5\n");
	printf("*********退出学生信息系统,请按 6\n");
}
void my_printf2()
{
	printf("按姓名查找,请按 a            按年龄查找,请按 b\n");
	printf("按性别查找,请按 c            按籍贯查找,请按 d\n");
	printf("按学院查找,请按 e            按专业查找,请按 f\n");
	printf("按电话查找,请按 g            按学号查找,请按 h\n");
	printf("按年级查找,请按 i            按全信息找,请按 p\n");
	printf("退出查询，请按  k\n");
}
void my_search()
{
	char select2 = getchar();
	char buff[30] = { 0 };
	switch (select2)
	{
	case 'a':
		printf("请输入要查找的姓名\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->姓名, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'b':
		printf("请输入要查找的年龄\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->年龄, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'c':
		printf("请输入要查找的性别\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->性别, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'd':
		printf("请输入要查找的籍贯\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->籍贯, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'e':
		printf("请输入要查找的学院\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->学院, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'f':
		printf("请输入要查找的专业\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->专业, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'g':
		printf("请输入要查找的电话\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->电话, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p++;
		my_search();
		break;
	case 'h':
		printf("请输入要查找的学号\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->学号, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'i':
		printf("请输入要查找的年级\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->年级, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'p':
		if (n != 0)
		{
			for (int i = 0; i < n; i++)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->姓名, p->年龄, p->性别, p->籍贯, p->学院,
					p->专业, p->电话, p->学号, p->年级);
				p++;
			}
			p = f;
		}
		else
		{
			printf("还没有录用\n");
		}
		my_search();
		break;
	case 'k':
		printf("已退出查询\n");
		break;
	default:
		my_search();
		break;
	}
}
void my_scanf1(FILE *fw)
{
	char arr[2] = "\n";
	int select1 = 0;
	scanf("%d", &select1);
	switch (select1)
	{
	case 1:
		GetInfo();
		my_scanf1(fw);
		break;
	case 2:
		my_printf2();
		my_search();
		my_scanf1(fw);
		break;
	case 3:
		my_change();
		my_scanf1(fw);
		break;
	case 4:
		my_delete();
		my_scanf1(fw);
		break;
	case 5:
		if (m != 0)
		{
			printf("姓名--原学院--原专业--现学院--现专业\n");
			for (int i = 0; i < m; i++)
			{
				printf("%s--%s--%s--%s--%s\n", s1->姓名, s1->原学院, s1->原专业, s1->现学院, s1->现专业);
				s1++;
			}
			s1 = s2;
		}
		else
		{
			printf("还没有转专业信息\n");
		}
		my_scanf1(fw);
		break;
	case 6:
			  for (int i = 0; i < n; i++)
			  {
				  fwrite(p, sizeof(struct student), 1, fw);
				  p++;
			  }
			  fclose(fw);
			  p = f;
			  break;
	default:
		printf("输入错误\n");
		my_scanf1(fw);
		break;
	}
}

int main()
{
	            
	p = (struct student *)malloc(sizeof(struct student) * 100);
	s = (struct zhuanye *)malloc(sizeof(struct zhuanye) * 100);
	//memset(p, sizeof(struct student), 100);
	//memset(s, sizeof(struct zhuanye), 100);
	f = p;
	f1 = p;
	s1 = s;
	s2 = s;
	FILE *fr = fopen("g:\\student.txt", "r");
	assert(fr != NULL);
	char buff[200] = { 0 };
	while ((fgets(buff, sizeof(struct student)+1, fr) != NULL) && (fr!=NULL))
	{
		memcpy(p, buff,sizeof(struct student));
		p++;
		n++;
	}
	p = f;
	FILE *fw = fopen("g:\\student.txt", "wb");
	assert(fw != NULL);
	my_print1();
	my_scanf1(fw);
	free(p);
	free(s);
	fclose(fr);
	return 0;
}
