#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>    

#define MAX 50    

typedef struct node1{
	int school;  /*ѧУ���*/
	int record;  /*��Ŀ�ɼ�*/
	struct node1 *next;  /*����*/
}Schools;

typedef struct {
	int item;  /*��Ŀ���*/
	Schools *firstschool; /*����ָ�������е�һ�����*/
}ITEM;

typedef struct {
	int z; /* ��Ŀ���� */
	ITEM a[MAX];
}ALLitems;

typedef struct node2 {
	int item;    /*��ѧУ�񽱵���Ŀ*/
	int record;  /*��Ŀ�ɼ�*/
	struct node2 *next;  /*����*/
}Items;

typedef struct {
	int school;  /*ѧУ���*/
	int score;  /*ѧУ�ܷ�*/
	int boys;  /*�������ܷ�*/
	int girls;  /*Ů�����ܷ�*/
	Items *firstitem; /*����ָ�������е�һ������Ŀ�Ľ��*/
}SCHNode;

typedef struct {
	int n; /* ѧУ���� */
	SCHNode b[MAX];
}ALLNode;

ALLitems *g1;
ALLNode *g2;

void enterScore(ALLitems *g1, ALLNode *g2)
{
	Schools *p1;
	Items *p2;
	int i = 0, j, k, m, w, h, x;
	p1 = (Schools *)malloc(sizeof(Schools));
	p2 = (Items *)malloc(sizeof(Items));
	if (!p1 || !p2)
		exit(1);

	printf("\n���������Ŀ��Ϣ:\n");
	printf("����������Ŀ����M(<=20):");
	scanf("%d", &m);
	if (m<0 || m>20)
	{
		printf("��������,m��20���ڵ�����,����������:");
		scanf("%d", &m);
	}
	printf("����Ů����Ŀ����W(<=20):");
	scanf("%d", &w);
	if (w<0 || w>20)
	{
		printf("��������,w��20���ڵ�����,����������:");
		scanf("%d", &w);
	}
	printf("����μ��˶����ѧУ����N(<=20):");
	scanf("%d", &g2->n);
	if (g2->n<0 || g2->n>20)
	{
		printf("��������,n��20���ڵ�����,����������:");
		scanf("%d", &g2->n);
	}
	g1->z = m + w;
	printf("����Ŀ���Ϊ����1-%d,Ů��%d-%d", m, m + 1, g1->z);
	printf("\n\n��¼�˶���ɼ�");
	printf("\n\n(����0��־����)\n");
	for (k = 1; k <= g1->z; k++)
	{
		g1->a[k].item = k;
		g1->a[k].firstschool = NULL;
	}
	for (k = 1; k <= g2->n; k++)
	{
		g2->b[k].school = k;
		g2->b[k].firstitem = 0;
		g2->b[k].score = 0;
		g2->b[k].boys = 0;
		g2->b[k].girls = 0;
	}
	g2->b[0].score = 0;
	g2->b[0].boys = 0;
	g2->b[0].girls = 0;
	scanf("%d", &i);
	while (i != 0)
	{
		printf("\n��Ŀ���:");
		scanf("%d", &i);
		if (i != 0)
		{
			printf("1.ǰ����   2.ǰ����\n");
			printf("��ѡ��:");
			scanf("%d", &j);
			if (j != 1 && j != 2)
			{
				printf(" ��������,������ѡ��:");
				scanf("%d", &j);
			}
			if (j == 1)
			{
				h = 3;
				do{
					printf("��%d��:ѧУ(ѧУ���Ϊ����(<50))", h);
					scanf("%d", &x);
					p1 = (Schools *)malloc(sizeof(Schools));
					p1->school = x;
					p2 = (Items *)malloc(sizeof(Items));
					p2->item = i;
					if (h == 3) p2->record = p1->record = 2;
					if (h == 2) p2->record = p1->record = 3;
					if (h == 1) p2->record = p1->record = 5;
					p1->next = g1->a[i].firstschool;
					g1->a[i].firstschool = p1;
					p2->next = g2->b[x].firstitem;
					g2->b[x].firstitem = p2;
					/* �ۼ��ܷ� */
					g2->b[x].score = g2->b[x].score + p2->record;
					/* �ۼ��������ܷ� */
					if (i <= m) g2->b[x].boys = g2->b[x].boys + p2->record;
					/* �ۼ�Ů�����ܷ� */
					else  g2->b[x].girls = g2->b[x].girls + p2->record;
					h--;
				} while (x != 0 && h != 0);
			}
			if (j == 2)
			{
				h = 5;
				do{
					printf("��%d��:ѧУ(ѧУ���Ϊ����)", h);
					scanf("%d", &x);
					p1 = (Schools *)malloc(sizeof(Schools));
					p1->school = x;
					p2 = (Items *)malloc(sizeof(Items));
					p2->item = i;
					if (h == 5) p2->record = p1->record = 1;
					if (h == 4) p2->record = p1->record = 2;
					if (h == 3) p2->record = p1->record = 3;
					if (h == 2) p2->record = p1->record = 5;
					if (h == 1) p2->record = p1->record = 7;
					p1->next = g1->a[i].firstschool;
					g1->a[i].firstschool = p1;
					p2->next = g2->b[x].firstitem;
					g2->b[x].firstitem = p2;
					/* �ۼ��ܷ� */
					g2->b[x].score = g2->b[x].score + p2->record;
					/* �ۼ��������ܷ� */
					if (i <= m) g2->b[x].boys = g2->b[x].boys + p2->record;
					/* �ۼ�Ů�����ܷ� */
					else  g2->b[x].girls = g2->b[x].girls + p2->record;
					h--;
				} while (x != 0 && h != 0);
			}
		}
	}
}

void save()
{
	FILE *fp1, *fp2;
	fp1 = (FILE *)malloc(sizeof(FILE));
	fp2 = (FILE *)malloc(sizeof(FILE));
	if ((fp1 = fopen("/storage/emulated/0/cyuyan/profiles/sports1", "wb")) == NULL)
	{
		printf("cannot open file.\n");
		return;
	}
	if (fwrite(g1, sizeof(ALLitems), 1, fp1) != 1)
		printf("file write error.\n");
	fclose(fp1);
	if ((fp2 = fopen("/storage/emulated/0/cyuyan/profiles/sports2", "wb")) == NULL)
	{
		printf("cannot open file.\n");
		return;
	}
	if (fwrite(g2, sizeof(ALLNode), 1, fp2) != 1)
		printf("file write error.\n");
	fclose(fp2);
}

/* �����ѧУ�ܷ� */
void outPutScore(ALLNode *g2)
{
	int k;
	printf("****** �����ѧУ�ܷ� ******\n");
	printf("ѧУ���  �ܷ�\n");
	for (k = 1; k <= g2->n; k++)
		printf("%8d%6d\n", k, g2->b[k].score);
	printf("\n");
}

/* ��ѧУ���������� */
void sortBySchoolNo(ALLNode *g2)
{
	int k;
	Items *p2;
	p2 = (Items *)malloc(sizeof(Items));
	printf("****** ��ѧУ���������� ******\n");
	printf("ѧУ���    �����  \n");
	scanf("%d", &k);

	for (k = 1; k <= g2->n; k++)
	{
		printf("%8d\t", k);
		p2 = g2->b[k].firstitem;
		while (p2 != NULL)
		{
			printf("��Ŀ%d:��%d�� ", p2->item, p2->record);
			p2 = p2->next;
		}
		printf("\n");
	}
	printf("\n");
}

/* ��ѧУ�ܷ�������� */
void sortBySchoolScore(ALLNode *g2)
{
	int i, j, k;
	Items *p2;
	printf("****** ��ѧУ�ܷ�������� ******\n");
	printf("ѧУ���    �ܷ�\n");
	scanf("%d", &k);
	//printf("����Ҫ��ѯ����Ŀ���:");

	for (i = 2; i <= g2->n; i++)
	{
		printf("%8d", k);
		p2 = g2->b[k].firstitem;
		while (p2 != NULL)
		{
			printf("%d    %d\n", g2->b[k].school, g2->b[k].score);
			p2 = p2->next;
		}
		printf("\n");


		g2->b[0].score = g2->b[i].score;
		g2->b[0].boys = g2->b[i].boys;
		g2->b[0].girls = g2->b[i].girls;
		g2->b[0].school = g2->b[i].school;
		j = i - 1;
		while (g2->b[0].score<g2->b[j].score&&j>0)
		{
			g2->b[j + 1].score = g2->b[j].score;
			g2->b[j + 1].boys = g2->b[j].boys;
			g2->b[j + 1].girls = g2->b[j].girls;
			g2->b[j + 1].school = g2->b[j].school;
			j--;
		}
		g2->b[j + 1].score = g2->b[0].score;
		g2->b[j + 1].boys = g2->b[0].boys;
		g2->b[j + 1].girls = g2->b[0].girls;
		g2->b[j + 1].school = g2->b[0].school;
	}
	for (k = 1; k <= g2->n; k++)
		printf("%d    %d\n", g2->b[k].school, g2->b[k].score);
}

/* ���������ܷ�������� */
void sortByManTeam(ALLNode *g2)
{
	int i, j, k;
	Items *p2;
	p2 = (Items *)malloc(sizeof(Items));
	printf("****** ���������ܷ�������� ******\n");
	printf("ѧУ���    �������ܷ�\n");
	scanf("%d", &k);
	//printf("����Ҫ��ѯ��ѧУ���:");
	for (i = 2; i <= g2->n; i++)
	{
		printf("%d\t", k);
		p2 = g2->b[k].firstitem;
		while (p2 != NULL)
		{
			printf("%d    %d\n", g2->b[k].school, g2->b[k].boys);
			p2 = p2->next;
		}
		printf("\n");
		g2->b[0].score = g2->b[i].score;
		g2->b[0].boys = g2->b[i].boys;
		g2->b[0].girls = g2->b[i].girls;
		g2->b[0].school = g2->b[i].school;
		j = i - 1;
		while (g2->b[0].boys<g2->b[j].boys&&j>0)
		{
			g2->b[j + 1].score = g2->b[j].score;
			g2->b[j + 1].boys = g2->b[j].boys;
			g2->b[j + 1].girls = g2->b[j].girls;
			g2->b[j + 1].school = g2->b[j].school;
			j--;
		}
		g2->b[j + 1].score = g2->b[0].score;
		g2->b[j + 1].boys = g2->b[0].boys;
		g2->b[j + 1].girls = g2->b[0].girls;
		g2->b[j + 1].school = g2->b[0].school;
	}
	for (k = 1; k <= g2->n; k++)
		printf("%d    %d\n", g2->b[k].school, g2->b[k].boys);
}

/* ��Ů�����ܷ�������� */
void sortByWomanTeam(ALLNode *g2)
{
	int i, j, k;
	Items *p2;
	p2 = (Items *)malloc(sizeof(Items));
	printf("****** ��Ů�����ܷ�������� ******\n");
	printf("ѧУ���    Ů�����ܷ�\n");

	scanf("%d", &k);
	// printf("����Ҫ��ѯ����Ŀ���:");

	for (i = 2; i <= g2->n; i++)
	{
		printf("%d", k);
		p2 = g2->b[k].firstitem;
		while (p2 != NULL)
		{
			printf("%d    %d\n", g2->b[k].school, g2->b[k].girls);
			p2 = p2->next;
		}
		printf("\n");



		g2->b[0].score = g2->b[i].score;
		g2->b[0].boys = g2->b[i].boys;
		g2->b[0].girls = g2->b[i].girls;
		g2->b[0].school = g2->b[i].school;
		j = i - 1;
		while (g2->b[0].girls<g2->b[j].girls&&j>0)
		{
			g2->b[j + 1].score = g2->b[j].score;
			g2->b[j + 1].boys = g2->b[j].boys;
			g2->b[j + 1].girls = g2->b[j].girls;
			g2->b[j + 1].school = g2->b[j].school;
			j--;
		}
		g2->b[j + 1].score = g2->b[0].score;
		g2->b[j + 1].boys = g2->b[0].boys;
		g2->b[j + 1].girls = g2->b[0].girls;
		g2->b[j + 1].school = g2->b[0].school;
	}

	for (k = 1; k <= g2->n; k++)
		printf("%d    %d\n", g2->b[k].school, g2->b[k].girls);
}

/* ��ѧУ��Ų�ѯѧУĳ����Ŀ��� */
void queryBySchoolNo(ALLNode *g2)
{
	int i, j;
	Items *p2;
	printf("****** ��ѧУ��Ų�ѯѧУĳ����Ŀ��� ******\n");
	printf("����Ҫ��ѯ��ѧУ���:");
	scanf("%d", &i);
	printf("����Ҫ��ѯ����Ŀ���:");
	scanf("%d", &j);
	p2 = g2->b[i].firstitem;
	while (p2 != NULL)
	{
		if (p2->item == j)
			printf("ѧУ���:%d    ��Ŀ%d:��%d��\n", i, p2->item, p2->record);
		p2 = p2->next;
	}
	printf("\n");
}

/* ����Ŀ��Ų�ѯȡ�����ε�ѧУ */
void queryBySchoolGrade(ALLitems *g1)
{
	int i;
	Schools *p1;
	printf("\n*** ����Ŀ��Ų�ѯȡ�����ε�ѧУ ***\n");
	printf("����Ҫ��ѯ����Ŀ���:");
	scanf("%d", &i);
	printf("��Ŀ���   ȡ�����ε�ѧУ\n");
	printf("%d\n", i);
	p1 = g1->a[i].firstschool;
	while (p1 != NULL)
	{
		printf(" ѧУ%d:��%d��  ", p1->school, p1->record);
		p1 = p1->next;
	}
	printf("\n\n");
}

/* �˵� */
void menu()
{
	printf("* * * * * * * * * * * * * * *\n");
	printf("        �˶������ͳ��ϵͳ     \n");
	printf("* * * * * * * * * * * * * * *\n");
	printf("* 1.�������Ŀ�ɼ�          *\n");
	printf("* 2.ͳ�Ƹ�ѧУ�ܷ�          *\n");
	printf("* 3.��ѧУ����������      *\n");
	printf("* 4.��ѧУ�ܷ��������      *\n");
	printf("* 5.���������ܷ��������    *\n");
	printf("* 6.��Ů�����ܷ��������    *\n");
	printf("* 7.��ѧУ��Ų�ѯѧУ��Ŀ  *\n");
	printf("* 8.����Ŀ�Ų�ȡ������ѧУ  *\n");
	printf("* 0.�˳�����                *\n");
	printf("* * * * * * * * * * * * * * *\n");
	printf("   ��ѡ��(0-8):");
}

int main()
{
	int choice;
	g2 = (ALLNode*)malloc(sizeof(ALLNode));
	g1 = (ALLitems*)malloc(sizeof(ALLitems));
	if (!g2 || !g1)
		exit(1);

	menu();
	scanf("%d", &choice);

	for (;;)
	{
		switch (choice)
		{
		case 1:
			enterScore(g1, g2);
			save();
			printf("������ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 2:
			outPutScore(g2);
			printf("�����ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 3:
			sortBySchoolNo(g2);
			printf("������ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 4:
			sortBySchoolScore(g2);
			printf("��ȡ��ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 5:
			sortByManTeam(g2);
			printf("������ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 6:
			sortByWomanTeam(g2);
			printf("������ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 7:
			queryBySchoolNo(g2);
			printf("��ѯ��ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 8:
			queryBySchoolGrade(g1);
			printf("��ѯ��ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 0:
			exit(0);
		default:
			break;
		}
		if (choice == 0)
		{
			return;
		}

		menu();
		scanf("%d", &choice);
	}
	return 0;
}