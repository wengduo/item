#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

struct student
{
	char ����[10];
	char ����[3];
	char �Ա�[3];
	char ����[30];
	char ѧԺ[13];
	char רҵ[10];
	char �绰[12];
	char ѧ��[10];
	char �꼶[2];
}*p,*f,*f1;

struct zhuanye
{
	char ����[8];
	char ԭѧԺ[20];
	char ԭרҵ[20];
	char ��ѧԺ[20];
	char ��רҵ[20];
}*s, *s1, *s2;
int n = 0;
int m = 0;
void GetInfo()
{
	int k;
	printf("������Ҫ���뼸����\n");

	scanf("%d", &k);	
	p += sizeof(p)*n;
	for (int i = 0; i<k; i++)
	{
		printf("����ѧ���Ļ�����Ϣ:����,����,�Ա�,����,ѧԺ,רҵ,�绰,ѧ��,�꼶\n");
		scanf("%s %s %s %s %s %s %s %s %s", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
			p->רҵ, p->�绰, p->ѧ��, p->�꼶);
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
	printf("������ѧ��ѧ��:\n");
	scanf("%s", &number);
	printf("�Ƿ�תרҵ,�ǰ�1,��2\n");
	scanf("%d", &pb);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(p->ѧ��,number) == 0)
		{
			if (pb == 1)
			{
				s += m;
				printf("ѧ���Ļ�����Ϣ:����,����,�Ա�,����,ѧԺ,רҵ,�绰,ѧ��,�꼶\n");
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
				strcpy(s->ԭѧԺ, p->ѧԺ);
				strcpy(s->ԭרҵ, p->רҵ);
				
				//memset(p, 0, sizeof(struct student)+1);
				printf("������ѧ���Ļ�����Ϣ:����,����,�Ա�,����,ѧԺ,רҵ,�绰,ѧ��,�꼶\n");
				scanf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
				strcpy(s->����, p->����);
				strcpy(s->��ѧԺ, p->ѧԺ);
				strcpy(s->��רҵ, p->רҵ);
				s ++;
				s = s1;
				m++;
			}
			else
			{
				printf("ѧ���Ļ�����Ϣ:����,����,�Ա�,����,ѧԺ,רҵ,�绰,ѧ��,�꼶\n");
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
				memset(p, 0, sizeof(struct student));
				printf("������ѧ���Ļ�����Ϣ:����,����,�Ա�,����,ѧԺ,רҵ,�绰,ѧ��,�꼶\n");
				scanf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			printf("��ѧ�����޸�\n");
			j++;
		}
		p++;
	}
	p = f;
	if (j == 0)
	{
		printf("��ѧ��������,����������\n");
		my_change();
	}
}
void my_delete()
{
	char number[10];
	int j = 0;
	printf("������ѧ��ѧ��:\n");
	scanf("%s", number);
	for (int i = 0; i < n; i++)
	{
		if (strcmp( p->ѧ��,number) == 0)
		{
			f++;
			for (j = 0; j < n; j++)
			{
				strcpy(p->����, f->����);
				strcpy(p->����, f->����);// �Ա�, ����, ѧԺ, רҵ, �绰, ѧ��, �꼶
				strcpy(p->�Ա�, f->�Ա�);
				strcpy(p->����, f->����);
				strcpy(p->ѧԺ, f->ѧԺ);
				strcpy(p->רҵ, f->רҵ);
				strcpy(p->�绰, f->�绰);
				strcpy(p->ѧ��, f->ѧ��);
				strcpy(p->�꼶, f->�꼶);
				strcpy(p->����, f->����);
				p ++;
				f ++;
			}
			n--;
			printf("��ѧ����ɾ��!:\n");
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
		printf("��ѧ��������,����������\n");
		my_delete();
	}
}
void my_print1()
{
	printf("*****��ӭʹ�ñ��༶��������ϵͳ*****\n");
	printf("*********��ӭ�������ǵ�ϵͳ*********\n");
	printf("*********ѧ��������Ϣ¼��,�밴 1\n");
	printf("*********ѧ��������Ϣ�鿴,�밴 2\n");
	printf("*********ѧ��������Ϣ�޸�,�밴 3\n");
	printf("*********ѧ��������Ϣɾ��,�밴 4\n");
	printf("*********��ѧ��תרҵ��Ϣ,�밴 5\n");
	printf("*********�˳�ѧ����Ϣϵͳ,�밴 6\n");
}
void my_printf2()
{
	printf("����������,�밴 a            ���������,�밴 b\n");
	printf("���Ա����,�밴 c            ���������,�밴 d\n");
	printf("��ѧԺ����,�밴 e            ��רҵ����,�밴 f\n");
	printf("���绰����,�밴 g            ��ѧ�Ų���,�밴 h\n");
	printf("���꼶����,�밴 i            ��ȫ��Ϣ��,�밴 p\n");
	printf("�˳���ѯ���밴  k\n");
}
void my_search()
{
	char select2 = getchar();
	char buff[30] = { 0 };
	switch (select2)
	{
	case 'a':
		printf("������Ҫ���ҵ�����\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->����, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'b':
		printf("������Ҫ���ҵ�����\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->����, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'c':
		printf("������Ҫ���ҵ��Ա�\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->�Ա�, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'd':
		printf("������Ҫ���ҵļ���\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->����, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'e':
		printf("������Ҫ���ҵ�ѧԺ\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->ѧԺ, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'f':
		printf("������Ҫ���ҵ�רҵ\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->רҵ, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'g':
		printf("������Ҫ���ҵĵ绰\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->�绰, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p++;
		my_search();
		break;
	case 'h':
		printf("������Ҫ���ҵ�ѧ��\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->ѧ��, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
			}
			p++;
		}
		p = f;
		my_search();
		break;
	case 'i':
		printf("������Ҫ���ҵ��꼶\n");
		scanf("%s", &buff);
		for (int i = 0; i < n; i++)
		{
			if (memcmp(p->�꼶, buff, strlen(buff)) == 0)
			{
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
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
				printf("%s--%s--%s--%s--%s--%s--%s--%s--%s\n", p->����, p->����, p->�Ա�, p->����, p->ѧԺ,
					p->רҵ, p->�绰, p->ѧ��, p->�꼶);
				p++;
			}
			p = f;
		}
		else
		{
			printf("��û��¼��\n");
		}
		my_search();
		break;
	case 'k':
		printf("���˳���ѯ\n");
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
			printf("����--ԭѧԺ--ԭרҵ--��ѧԺ--��רҵ\n");
			for (int i = 0; i < m; i++)
			{
				printf("%s--%s--%s--%s--%s\n", s1->����, s1->ԭѧԺ, s1->ԭרҵ, s1->��ѧԺ, s1->��רҵ);
				s1++;
			}
			s1 = s2;
		}
		else
		{
			printf("��û��תרҵ��Ϣ\n");
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
		printf("�������\n");
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
