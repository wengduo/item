#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#define INT_MAX 10000
#define n 10

int cost[n][n]; //�ߵ�ֵ 
int shortest[n][n]; //�������̾��� 
int path[n][n]; //�����ĵ� 

void introduce()
{ //�ص���Ϣ���� 
	int a;
	printf("��������Ҫ��ѯ�ĵص��ţ�");
	scanf("%d", &a);
	getchar();
	printf("\n");
	switch (a)
	{
	case 1:
		printf("1:����\n\n");
		break;
	case 2:
		printf("2:��ѧ¥\n\n");
		break;
	case 3:
		printf("3:����¥\n\n");
		break;
	case 4:
		printf("4:δ��ٳ�\n\n");
		break;
	case 5:
		printf("5:ͼ���\n\n");
		break;
	case 6:
		printf("6:����\n\n");
		break;
	case 7:
		printf("7:�ﾶ��\n\n");
		break;
	case 8:
		printf("8:�������\n\n");
		break;
	case 9:
		printf("9:����\n\n");
		break;
	case 10:
		printf("10:����¥\n\n");
		break;
	default:
		printf("������ı������\n\n");
		break;
	}
}

void floyed()
{ //��floyed�㷨�����ص������·�� 
	int i, j, k;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			shortest[i][j] = cost[i][j];
			path[i][j] = 0;
		}
	}
	
	for (k = 1; k <= n; k++)
	{
		for (j = 1; j <= n; j++)
		{
			for (i = 1; i <= n; i++)
			{
				if (shortest[i][j]>(shortest[i][k] + shortest[k][j]))
				{
				//��path[]��¼��i��j�����·�����ϵ�j��ǰ���ص����� 
				shortest[i][j] = shortest[i][k] + shortest[k][j];
				path[i][j] = k;
				path[j][i] = k;
				}
			}

		}
	
	}
	
}

void disply(int i, int j)
{
	//��ӡ���ص��·�������·�� 
	int a, b;
	a = i;
	b = j;
	printf("��Ҫ��ѯ�����ص�����·����:\n\n");
	if (shortest[i][j] != INT_MAX)
	{
		if (i<j)
		{
			printf("%d", b);
			while (path[i][j] != 0)
			{
				//��i��j��·���Ͼ����������ӡ���� 
				printf("<-%d", path[i][j]);
				if (i<j)
					j = path[i][j];
				else
					j = path[j][i];
			}
			printf("<-%d", a);
			printf("\n\n");
			printf("(%d->%d)���·���ǣ�%d ��\n", a, b, shortest[a][b]);
		}
		else
		{
			printf("%d", a);
			while (path[i][j] != 0)
			{
				//��i��j·���ϵ�˳���ӡ 
				printf("->%d", path[i][j]);
				if (i < j)  
				{
					j = path[i][j];
				}
				else
				{
					j = path[j][i];
				}
			}
			printf("->%d", b);
			printf("\n\n");
			printf("(%d->%d)���·���ǣ�%5d ��\n", a, b, shortest[a][b]);
		}
	}
	else
		printf("�������\n");
	printf("\n");
}

int shortestdistance()
{
	//�������̾��� 
	int i, j;
	printf("������Ҫ��Ѱ�����ص���:");
	scanf("%d %d", &i, &j);
	if (i>n || i <= 0 || j>n || j<0)
	{
		printf("������Ϣ����\n");
		printf("���������룺");
		scanf("%d %d", &i, &j);
	}
	else
	{
		floyed();
		disply(i, j);
	}
	return 1;
}


int main()
{
	int i, j;
	char k;
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			cost[i][j] = INT_MAX;
		}
		
	}
	cost[1][2] = cost[2][1] = 12;
	cost[1][3] = cost[3][1] = 24;
	cost[3][4] = cost[4][3] = 21;
	cost[2][4] = cost[4][2] = 16;
	cost[2][10] = cost[10][2] = 29;
	cost[3][5] = cost[5][3] = 30;
	cost[5][6] = cost[6][5] = 16;
	cost[6][7] = cost[7][6] = 27;
	cost[10][9] = cost[9][10] = 46;
	cost[4][10] = cost[10][4] = 5;
	cost[4][7] = cost[7][4] = 12;
	cost[7][8] = cost[8][7] = 36;
	cost[8][9] = cost[9][8] = 22;
	cost[1][1] = cost[2][2] = cost[3][3] = cost[4][4] = cost[5][5] = cost[6][6] = cost[7][7] = cost[8][8] = cost[9][9] = cost[10][10] = 0;

	while (1)
	{
		printf("-----------------------------------\n");
		printf("\tѧУ�ص��б�:\n");
		printf("\t1:����  \t2:��ѧ¥\n");
		printf("\t3:����¥  \t4:δ��ٳ�\n");
		printf("\t5:ͼ���  \t6:����\n");
		printf("\t7:�ﾶ��  \t8:�������\n");
		printf("\t9:����  \t10:����¥\n");
		printf("-----------------------------------\n\n");



		printf("\t-----��ӭʹ�ã�-----\n\n");
		printf("\ta.��Ϣ��ѯ\n");
		printf("\tb.���·��\n");
		printf("\tc.�˳�\n\n");
		printf("\t��ѡ��");
		scanf("\n%c", &k);



		switch (k)
		{
		case 'a':
			printf("");
			introduce();

			printf("��Entre������");
			getchar();
			system("cls");
			break;
		case 'b':
			printf("");
			shortestdistance();
			printf("��Entre������");
			getchar();
			getchar();
			system("cls");
			break;
		case 'c':
			printf("ллʹ��");
			exit(0);
		default:
			printf("\t������Ϣ����!���������롣\n");
			getchar();
			getchar();
			system("cls");
			break;
		}

	}
}