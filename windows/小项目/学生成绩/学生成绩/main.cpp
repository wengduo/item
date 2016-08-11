#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXN 35
#define MAX_NAME 256

/* ѧ����Ϣ */
typedef struct student
{
	int  no;
	char name[MAX_NAME];
	double  Chinese;
	double  math;
	double  mark_ave;
	double  mark_tot;
} STUDENT;

int len = 0;

/* �˵� */
void menu()
{
	printf("\n");
	printf("*****ѧ���ɼ�����ϵͳ****\n");
	printf("    1 ������Ϣ\n");
	printf("    2 �����Ϣ\n");
	printf("    3 ��ƽ��������\n");
	printf("    4 ��ѧ�Ų���\n");
	printf("    5 ������Ϣ\n");
	printf("    6 ��ѧ��ɾ��\n");
	printf("    7 ��ƽ����ͳ����Ϣ\n");
	printf("    8 ���浽�ļ�\n");
	printf("    9 ��ȡĬ����Ϣ\n");
	printf("    0 �˳�\n");
	printf("*************************\n");
	printf("%s\n", "��ѡ��:");
}

/* ������Ϣ�ӳ��� */
void input(STUDENT *data, int *len)
{
	int no;
	putchar('\n');
	printf("%s\n", "�����룬�˳�������-1.");
	printf("%s\n", "ѧ�� ���� ���� ��ѧ");
	printf("��: 1 jack 93 95\n");

	scanf("%d %s %lf %lf", &data[*len].no, data[*len].name, &data[*len].Chinese, &data[*len].math);
	data[*len].mark_ave = (data[*len].Chinese + data[*len].math) / 2.0;
	data[*len].mark_tot = data[*len].Chinese + data[*len].math;
	(*len)++;
}


/* �����Ϣ�ӳ��� */
void output(STUDENT *data, int len)
{
	int i;
	system("clear");
	printf("%4s", "ѧ��");
	printf("%6s", "����");
	printf("%6s", "����");
	printf("%6s", "��ѧ");
	printf("%8s", "ƽ����");
	printf("%6s", "�ܷ�");
	putchar('\n');
	printf("*************************\n");
	for (i = 0; i< len; i++)
	{
		printf("%4d", data[i].no);
		printf("%6s", data[i].name);
		printf("%6.1lf", data[i].Chinese);
		printf("%6.1lf", data[i].math);
		printf("%8.1lf", data[i].mark_ave);
		printf("%6.1lf", data[i].mark_tot);
		putchar('\n');
	}
	printf("*************************\n");
	putchar('\n');
}

/* �����ӳ��� */
void sort(STUDENT *data, int len)
{
	int i, j, k;
	STUDENT temp;
	for (i = 0; i<len - 1; i++) {
		for (k = i, j = i + 1; j<len; j++)
		if (data[k].mark_ave > data[j].mark_ave) k = j;
		if (k != i) {

			temp = data[i];
			data[i] = data[k];
			data[k] = temp;
		}
	}

	output(data, len);
}

/* �����ӳ��� */
void find(STUDENT *data, int len)
{
	int find_no, result = 0;
	int i;

	printf("%s\n", "������Ҫ����ѧ����ѧ��.");
	scanf("%d", &find_no);
	while (data[result].no != find_no && result < len) result++;
	if (result >= len) {
		printf("%s\n", "δ��ѯ�������Ϣ");
	}
	else {
		printf("%s\n", "��ѯ��Ϣ���£�");
		printf("*************************\n");
		putchar('\n');
		printf("%4s", "ѧ��");
		printf("%6s", "����");
		printf("%6s", "����");
		printf("%6s", "��ѧ");
		printf("%8s", "ƽ����");
		printf("%6s", "�ܷ�");
		putchar('\n');
		printf("%4d", data[result].no);
		printf("%6s", data[result].name);
		printf("%6.1lf", data[result].Chinese);
		printf("%6.1lf", data[result].math);
		printf("%8.1lf", data[result].mark_ave);
		printf("%6.1lf\n", data[result].mark_tot);

		printf("*************************\n");
		putchar('\n');
	}
}

/* �����ӳ��� */
void insert(STUDENT *data, int *len)
{
	int no, pos;
	double Chinese, math, mark_ave, mark_tot;
	int i;
	char name[MAX_NAME];
	printf("%s\n", "�����¼�¼.");
	printf("%s\n", "��ʽ��ѧ�� ���� ���� ��ѧ");
	scanf("%d %s %lf %lf", &no, name, &Chinese, &math);
	mark_ave = (Chinese + math) / 2.0;
	mark_tot = Chinese + math;
	pos = 0;
	while ((data[pos].mark_ave < mark_ave) && (pos < *len))
		pos++;
	for (i = *len - 1; i >= pos; i--)
		data[i + 1] = data[i];
	data[pos].no = no;
	strcpy(data[pos].name, name);
	data[pos].Chinese = Chinese;
	data[pos].math = math;
	data[pos].mark_ave = mark_ave;
	data[pos].mark_tot = mark_tot;
	(*len)++;
}

/* ɾ���ӳ��� */
void delete_item(STUDENT *data, int *len)
{
	int no, i, pos;
lab: pos = 0;
	printf("%s\n", "����Ҫɾ����ѧ��ѧ��.");
	scanf("%d", &no);

	while ((data[pos].no != no) && (pos < *len)) pos = pos + 1;
	if (pos >= *len) {
		printf("%s\n", "δ�ҵ���Ҫɾ����ѧ��");
	}
	else {
		for (i = pos + 1; i < *len; i++)
			data[i - 1] = data[i];
		*len = *len - 1;
		if (*len == 0) {
			printf("%s\n", "��û���κμ�¼");
			return;
		}
	}
}

/* ͳ���ӳ��� */
void stat(STUDENT *data, int len)
{
	int no_59 = 0, no_69 = 0, no_79 = 0, no_89 = 0, no_100 = 0;
	int i;
	for (i = 0; i < len; i++) {
		if (data[i].mark_ave <= 59) no_59++;
		else if (data[i].mark_ave <= 69) no_69++;
		else if (data[i].mark_ave <= 79) no_79++;
		else if (data[i].mark_ave <= 89) no_89++;
		else no_100++;
	}
	printf("*************************\n");
	printf("%10s", "����");
	printf("%10s\n", "ѧ��");

	printf("%10s", "0--59");
	printf("%10d\n", no_59);

	printf("%10s", "60--69");
	printf("%10d\n", no_69);

	printf("%10s", "70--79");
	printf("%10d\n", no_79);

	printf("%10s", "80--89");
	printf("%10d\n", no_89);

	printf("%10s", "90--100");
	printf("%10d\n", no_100);
	printf("*************************\n");
}

/* �����ݱ��浽�ļ� */
void save(STUDENT *data, int len)
{
	int i;
	FILE *fp;
	fp = fopen("/storage/emulated/0/cyuyan/profiles/�ɼ�ͳ�Ʊ�.txt", "w");
	fprintf(fp, "%8s", "ѧ��");
	fprintf(fp, "%8s", "����");
	fprintf(fp, "%8s", "����");
	fprintf(fp, "%8s", "��ѧ");
	fprintf(fp, "%12s", "ƽ����");
	fprintf(fp, "%10s\n", "�ܷ�");
	fprintf(fp, "============================================================\n");
	putchar('\n');
	for (i = 0; i< len; i++)
	{
		fprintf(fp, "%8d", data[i].no);
		fprintf(fp, "%8s", data[i].name);
		fprintf(fp, "%8.1lf", data[i].Chinese);
		fprintf(fp, "%8.1lf", data[i].math);
		fprintf(fp, "%12.1lf", data[i].mark_ave);
		fprintf(fp, "%10.1lf\n", data[i].mark_tot);
	}
	fprintf(fp, "============================================================\n");
	fclose(fp);
}

/* Ĭ������ */
void defdata(STUDENT *data)
{
	int i = 0;
	len = 10;

	for (int i = 0; i < len; i++)
	{
		data[i].no = i + 1;
	}

	sscanf("Jack 65.0 68.0 66.5 133.0", "%s %lf %lf %lf %lf",
		data[0].name, &data[0].Chinese, &data[0].math, &data[0].mark_ave, &data[0].mark_tot);
	sscanf("Bill 70.0 82.0 76.5 152.0", "%s %lf %lf %lf %lf",
		data[1].name, &data[1].Chinese, &data[1].math, &data[1].mark_ave, &data[1].mark_tot);
	sscanf("Bob 70.0 72.0 71.0 142.0", "%s %lf %lf %lf %lf",
		data[2].name, &data[2].Chinese, &data[2].math, &data[2].mark_ave, &data[2].mark_tot);
	sscanf("Devin 98.0 62.0 85.5 170.0", "%s %lf %lf %lf %lf",
		data[3].name, &data[3].Chinese, &data[3].math, &data[3].mark_ave, &data[3].mark_tot);
	sscanf("Hale 84.0 69.0 76.5 153.0", "%s %lf %lf %lf %lf",
		data[4].name, &data[4].Chinese, &data[4].math, &data[4].mark_ave, &data[4].mark_tot);
	sscanf("Henry 80.0 91.0 85.5 171.0", "%s %lf %lf %lf %lf",
		data[5].name, &data[5].Chinese, &data[5].math, &data[5].mark_ave, &data[5].mark_tot);
	sscanf("Jim 86.0 82.0 84.0 168.0", "%s %lf %lf %lf %lf",
		data[6].name, &data[6].Chinese, &data[6].math, &data[6].mark_ave, &data[6].mark_tot);
	sscanf("Ken 96.0 98.0 97.0 194.0", "%s %lf %lf %lf %lf",
		data[7].name, &data[7].Chinese, &data[7].math, &data[7].mark_ave, &data[7].mark_tot);
	sscanf("Max 85.0 88.0 86.5 173.0", "%s %lf %lf %lf %lf",
		data[8].name, &data[8].Chinese, &data[8].math, &data[8].mark_ave, &data[8].mark_tot);
	sscanf("Peter 90.0 91.0 90.5 181.0", "%s %lf %lf %lf %lf",
		data[9].name, &data[9].Chinese, &data[9].math, &data[9].mark_ave, &data[9].mark_tot);
}

/* ������ */
void main()
{
	STUDENT data[MAXN];
	int choice;
	menu();
	scanf("%d", &choice);
	while (choice != 0) {

		switch (choice)
		{
		case 1:
			input(data, &len);
			printf("������ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 2:
			output(data, len);
			printf("�����ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 3:
			sort(data, len);
			printf("�������,�����������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 4:
			find(data, len);
			printf("�������,�����������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 5:
			insert(data, &len);
			printf("������ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 6:
			delete_item(data, &len);
			printf("ɾ����ϣ������������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 7:
			stat(data, len);
			printf("ͳ����ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 8:
			save(data, len);
			printf("������ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
		case 9:
			defdata(data);
			output(data, len);
			printf("��ȡ��ϣ����س�������");
			__fpurge(stdin);
			getchar();
			system("clear");
			break;
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
}