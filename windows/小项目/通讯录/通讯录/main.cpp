#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

typedef struct
{
	char score;     /*���*/
	char name[10];  /*����*/
	char num[15];   /*����*/
	char age[8];    /*����*/
}Person;

Person pe[80];

int menu_select()
{
	char c;
	do{
		system("clear");
		printf("    *****ͨѶ¼***** \n");
		printf("    ������������������\n");
		printf("    �� 1. ��Ӽ�¼  ��\n");
		printf("    �� 2. ��ʾ��¼  ��\n");
		printf("    �� 3. ɾ����¼  ��\n");
		printf("    �� 4. ��ѯ��¼  ��\n");
		printf("    �� 5. �޸ļ�¼  ��\n");
		printf("    �� 6. �����¼  ��\n");
		printf("    �� 7. Ĭ�ϼ�¼  ��\n");
		printf("    �� 0. �˳�����  ��\n");
		printf("    ������������������\n");
		printf("    ����ѡ��(0-7):");
		c = getchar();
	} while (c<'0' || c>'7');
	return(c - '0');
}

/* ��Ӽ�¼ */
int Input(Person per[], int n)
{
	int i = 0;
	char sign = 'Y', x[10];
	while (sign != 'n'&&sign != 'N')
	{
		printf("���:");
		scanf("%d", &per[n + i].score);
		printf("����:");
		scanf("%s", per[n + i].name);
		printf("����:");
		scanf("%s", per[n + i].age);
		printf("�绰����:");
		scanf("%s", per[n + i].num);

		gets(x);
		printf("\n�Ƿ�������?(Y/N)");
		scanf("%c", &sign);
		i++;
	}
	return(n + i);
}

/* ��ʾ��¼ */
void Display(Person per[], int n)
{
	int i;
	printf("--------------------------\n");
	printf("��� ���� ����        �绰\n");
	printf("--------------------------\n");
	for (i = 1; i<n + 1; i++)
	{
		printf("%4d%5s%5s%12s\n", per[i - 1].score, per[i - 1].name, per[i - 1].age, per[i - 1].num);
	}
	printf("--------------------------\n");
}

/* ɾ����¼ */
int Delete_a_record(Person per[], int n)
{
	char s[20];
	int i = 0, j;
	printf("��������ɾ����¼�е�����:");
	scanf("%s", s);
	while (strcmp(per[i].name, s) != 0 && i<n) i++;
	if (i == n)
	{
		printf("ͨѶ¼��û�д���!\n");
		return(n);
	}
	for (j = i; j<n - 1; j++)
	{
		strcpy(per[j].num, per[j + 1].num);
		strcpy(per[j].name, per[j + 1].name);
		strcpy(per[j].age, per[j + 1].age);
		per[j].score = per[j + 1].score;
	}
	printf("�Ѿ��ɹ�ɾ��!\n");
	return(n - 1);
}

/* ���Ҽ�¼ */
void Query_a_record(Person per[], int n)
{

	int m;
	printf("    \n��ѡ���ѯ��ʽ:\n");
	printf("    ����������������\n");
	printf("    ��1------���� ��\n");
	printf("    ��2------�绰 ��\n");
	printf("    ��3------���� ��\n");
	printf("    ����������������\n");
	printf("    ��ѡ��:");
	scanf("%d", &m);
	while (m != 1 && m != 2 && m != 3)
	{
		printf("�������������ѡ��:");
		scanf("%d", &m);
	}

	if (m == 1)
	{
		char s[20];
		int i = 0;
		printf("���������ѯ������:");
		scanf("%s", s);
		while (strcmp(per[i].name, s) != 0 && i<n) i++;
		if (i == n)
		{
			printf("ͨѶ¼��û�д���!\n");
			return;
		}
		printf("���˱��: %d\n", per[i].score);
		printf("��������: %s\n", per[i].age);
		printf("�绰����: %s\n", per[i].num);
	}

	if (m == 2)
	{
		char s[20];
		int i = 0;
		printf("���������ѯ�ĵ绰:");
		scanf("%s", s);
		while (strcmp(per[i].num, s) != 0 && i<n) i++;
		if (i == n)
		{
			printf("ͨѶ¼��û�д���!\n");
			return;

		}
		printf("���˱��: %d\n", per[i].score);
		printf("��������: %s\n", per[i].name);
		printf("��������: %s\n", per[i].age);
	}
}

/* �޸����� */
void Change(Person per[], int n)
{
	char s[20];
	int i = 0;
	printf("���������޸ĵļ�¼�е�����:");
	scanf("%s", s);
	while (strcmp(per[i].name, s) != 0 && i<n) i++;
	if (i == n)
	{
		printf("ͨѶ¼��û�д���!\n");
		return;
	}
	printf("���:");
	scanf("%d", &per[i].score);
	printf("����:");
	scanf("%s", per[i].name);
	printf("����:");
	scanf("%s", per[i].age);
	printf("�绰����:");
	scanf("%s", per[i].num);
	printf("�޸ĳɹ���");
}

/* �������� */
void WritetoText(Person per[], int n)
{
	int i = 0;
	FILE *fp;   /*�����ļ�ָ��*/
	if ((fp = fopen("/storage/emulated/0/cyuyan/profiles/ͨѶ¼.txt", "w")) == NULL)
	{
		printf("�޷����ļ�\n");
		system("pause");
		return;
	}
	fprintf(fp, "***************ͨѶ¼***************\n");
	fprintf(fp, "���     ����   ����          �绰\n");
	fprintf(fp, "------------------------------------\n");
	while (i<n)
	{
		fprintf(fp, "%4d%9s%7s%12s\n", per[i].score, per[i].name, per[i].age, per[i].num);
		i++;
	}
	fprintf(fp, "------------------------------------\n");
	fprintf(fp, "************����%d����¼************\n", n);
	fclose(fp);  /*�ر��ļ�*/
	printf("����ɹ�!\n");
}

/* Ĭ������ */
void DefaultData(Person per[], int *n)
{
	int i = 0;
	*n = 10;

	for (int i = 0; i < *n; i++)
	{
		per[i].score = i + 1;
	}

	sscanf("Jack 13700000001 20", "%s %s %s", per[0].name, per[0].num, per[0].age);
	sscanf("Bill 13700000002 25", "%s %s %s", per[1].name, per[1].num, per[1].age);
	sscanf("Bob 13700000003 26", "%s %s %s", per[2].name, per[2].num, per[2].age);
	sscanf("Devin 13700000004 28", "%s %s %s", per[3].name, per[3].num, per[3].age);
	sscanf("Hale 13700000005 21", "%s %s %s", per[4].name, per[4].num, per[4].age);
	sscanf("Henry 13700000006 23", "%s %s %s", per[5].name, per[5].num, per[5].age);
	sscanf("Jim 13700000007 25", "%s %s %s", per[6].name, per[6].num, per[6].age);
	sscanf("Ken 13700000008 22", "%s %s %s", per[7].name, per[7].num, per[7].age);
	sscanf("Max 13700000009 24", "%s %s %s", per[8].name, per[8].num, per[8].age);
	sscanf("Peter 13700000010 21", "%s %s %s", per[9].name, per[9].num, per[9].age);
}

/*������*/
void main()
{
	int n = 0;
	for (;;)
	{
		switch (menu_select())
		{
		case 1:
			printf("\n    ��Ӽ�¼��ͨѶ¼\n");
			n = Input(pe, n);
			printf("�����ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 2:
			printf("\n    ͨѶ¼��¼��\n");
			Display(pe, n);
			printf("�����ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 3:
			printf("\n    ��ͨѶ¼��ɾ����¼\n");
			n = Delete_a_record(pe, n);
			printf("ɾ����ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 4:
			printf("\n    ��ͨѶ¼�в��Ҽ�¼\n");
			Query_a_record(pe, n);
			printf("������ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 5:
			printf("\n    �޸�ͨѶ¼�еļ�¼\n");
			Change(pe, n);
			printf("�޸���ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 6:
			printf("\n    ���湦��\n");
			WritetoText(pe, n);
			printf("������ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 7:
			printf("\n    Ĭ������\n");
			DefaultData(pe, &n);
			printf("������ϣ������������\n");
			Display(pe, n);
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 0:
			printf("\n    ллʹ�ã��ټ�!\n");
			__fpurge(stdin);
			getchar();
			system("clear");
			exit(0);
		}
	}
}