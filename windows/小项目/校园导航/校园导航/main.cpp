#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#define INT_MAX 10000
#define n 10

int cost[n][n]; //边的值 
int shortest[n][n]; //两点间最短距离 
int path[n][n]; //经过的点 

void introduce()
{ //地点信息介绍 
	int a;
	printf("请输入您要查询的地点编号：");
	scanf("%d", &a);
	getchar();
	printf("\n");
	switch (a)
	{
	case 1:
		printf("1:西门\n\n");
		break;
	case 2:
		printf("2:教学楼\n\n");
		break;
	case 3:
		printf("3:工科楼\n\n");
		break;
	case 4:
		printf("4:未央操场\n\n");
		break;
	case 5:
		printf("5:图书馆\n\n");
		break;
	case 6:
		printf("6:篮球场\n\n");
		break;
	case 7:
		printf("7:田径场\n\n");
		break;
	case 8:
		printf("8:室内球馆\n\n");
		break;
	case 9:
		printf("9:饭堂\n\n");
		break;
	case 10:
		printf("10:宿舍楼\n\n");
		break;
	default:
		printf("您输入的编号有误！\n\n");
		break;
	}
}

void floyed()
{ //用floyed算法求两地点间的最短路径 
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
				//用path[]记录从i到j的最短路径点上点j的前驱地点的序号 
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
	//打印两地点的路径及最短路程 
	int a, b;
	a = i;
	b = j;
	printf("您要查询的两地点间最短路径是:\n\n");
	if (shortest[i][j] != INT_MAX)
	{
		if (i<j)
		{
			printf("%d", b);
			while (path[i][j] != 0)
			{
				//把i到j的路径上经过点逆序打印出来 
				printf("<-%d", path[i][j]);
				if (i<j)
					j = path[i][j];
				else
					j = path[j][i];
			}
			printf("<-%d", a);
			printf("\n\n");
			printf("(%d->%d)最短路程是：%d 米\n", a, b, shortest[a][b]);
		}
		else
		{
			printf("%d", a);
			while (path[i][j] != 0)
			{
				//把i到j路径上点顺序打印 
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
			printf("(%d->%d)最段路程是：%5d 米\n", a, b, shortest[a][b]);
		}
	}
	else
		printf("输入错误！\n");
	printf("\n");
}

int shortestdistance()
{
	//两点间最短距离 
	int i, j;
	printf("请输入要找寻的两地点编号:");
	scanf("%d %d", &i, &j);
	if (i>n || i <= 0 || j>n || j<0)
	{
		printf("输入信息有误！\n");
		printf("请重新输入：");
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
		printf("\t学校地点列表:\n");
		printf("\t1:西门  \t2:教学楼\n");
		printf("\t3:工科楼  \t4:未央操场\n");
		printf("\t5:图书馆  \t6:篮球场\n");
		printf("\t7:田径场  \t8:室内球馆\n");
		printf("\t9:饭堂  \t10:宿舍楼\n");
		printf("-----------------------------------\n\n");



		printf("\t-----欢迎使用！-----\n\n");
		printf("\ta.信息查询\n");
		printf("\tb.最短路径\n");
		printf("\tc.退出\n\n");
		printf("\t请选择：");
		scanf("\n%c", &k);



		switch (k)
		{
		case 'a':
			printf("");
			introduce();

			printf("按Entre键继续");
			getchar();
			system("cls");
			break;
		case 'b':
			printf("");
			shortestdistance();
			printf("按Entre键继续");
			getchar();
			getchar();
			system("cls");
			break;
		case 'c':
			printf("谢谢使用");
			exit(0);
		default:
			printf("\t输入信息有误!请重新输入。\n");
			getchar();
			getchar();
			system("cls");
			break;
		}

	}
}