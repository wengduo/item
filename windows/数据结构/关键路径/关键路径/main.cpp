#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
//#define MAX 0
//int m; //������
//int linjie[50][50] = { 0 };//�ڽӾ���
//int max = MAX; //�ؼ�·����Ȩֵ֮��
//int best = 0;
//int lujing[50] = { 0 };
//int lujing1[50] = { 0 };
//int k = 1;
//int finish = 0;
//
//void chushihua()
//{
//	printf("\t\t\t\t�㷨��ʼ\n");
//	printf("�����붥����:");
//	std::cin >> m;//������
//	printf("�������յ���:");
//	std::cin >> finish;
//	for (int i = 0; i < m; i++)
//	{
//		printf("�������%d��:", i);
//		for (int j = 0; j < m; j++)
//		{
//			std::cin >> linjie[i][j];
//		}
//	}
//	printf("\t\t\t\t��ʼ�����\n");
//}
//
//bool panduan(int j)
//{
//	for (int n = 0; n < k; n++)
//	{
//		if (lujing[n] == j)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//void digui(int i,int j)
//{
//	while (j < m)
//	{
//		if (linjie[i][j] != 0)
//		{
//			if (!panduan(j))
//			{
//				return;
//			}
//			best += linjie[i][j];
//			lujing[k++] = j;
//			if (j == finish)
//			{
//				if (best > max)
//				{
//					max = best;
//					memcpy(lujing1, lujing, sizeof(lujing));
//				}
//			}
//			digui(j, 0);
//			k--;
//			best -= linjie[i][j];
//			j++;
//		}
//		else
//		{
//			j++;
//		}
//	}
//}
//
//int main()
//{
//	int i = 0;
//	int j = 0;
//	chushihua();
//	digui(i,j);
//	printf("%d\n", max);
//	printf("·��: V%d",lujing1[0]);
//	for (int h = 1; h < m; h++)
//	{
//		
//		printf("->V%d",lujing1[h]);
//		if (lujing1[h] == finish)
//		{
//			break;
//		}
//	}
//	printf("\n\t\t\t�㷨����\n");
//	return 0;
//}

//
//#define STACK_INIT_SIZE 100
//#define STACKINCREMENT  10
//
//#define MAX 20
//typedef int VertexType;
//typedef struct ArcNode//����
//{
//	int adjvex;//����ָ��Ķ����λ��
//	struct ArcNode *nextarc;
//}ArcNode;
//typedef struct VNode//ͷ���
//{
//	VertexType data;//������Ϣ
//	ArcNode *firstarc;//ָ���һ�������û��Ķ���ָ��
//}VNode, *AdjList;
//typedef struct
//{
//	AdjList vertices;
//	int vexnum;//ͼ��**��ǰ**������
//}ALGraph;
//typedef struct//ջ�Ķ���
//{
//	int *base;
//	int *top;
//	int stacksize;
//}SqStack;
///////////ջ�Ĳ�����������
//void initialStack(SqStack *s)
//{
//	s->base = (int *)malloc(STACK_INIT_SIZE*sizeof(int));
//	if (!s->base) exit(0);
//	s->top = s->base;
//	s->stacksize = STACK_INIT_SIZE;
//}
//void Push(SqStack *s, int e)
//{
//	if (s->top - s->base >= s->stacksize)
//	{
//		s->base = (int *)realloc(s->base, (STACK_INIT_SIZE + STACKINCREMENT)*sizeof(int));
//		if (!s->base) exit(0);
//		s->top = s->base + s->stacksize;
//		s->stacksize += STACKINCREMENT;
//	}
//	*(s->top)++ = e;
//}
//void Pop(SqStack *s, int *e)
//{
//	if (s->top == s->base) exit(0);
//	*e = *--(s->top);
//}
//void GetTop(SqStack *s, int *e)
//{
//	if (s->top == s->base) exit(0);
//	*e = *(s->top - 1);
//}
//int StackEmpty(SqStack *s)
//{
//	if (s->base == s->top)
//		return(1);
//	else
//		return(0);
//}
///////����ͼ���ڽӾ���
//void CreatAjacentMatrix(int *array, int n)//�����ڽӾؾ���(n��n��)
//{
//	int a;
//	int i, j, flag = 0;
//	printf("������һ��%d��%d�еĹ���ͼ���ڽӾ���:\n", n, n);
//	for (i = 0; i<n; i++)
//		for (j = 0; j<n; j++)
//		{
//			scanf("%d", &a);
//			*(array + i*n + j) = a;
//		}
//}
//void PrintAjacentMatrix(int *array, int n)
//{
//	int i, j;
//	for (i = 0; i<n; i++)
//	{
//		for (j = 0; j<n; j++)
//			printf("%5d ", *(array + i*n + j));
//		printf("\n");
//	}
//}
//
//////���ڽӾ��󵼳�Ϊͼ���ڽӱ���ʽ
//void CreatAdjList(int *array, int n, ALGraph *G)
//{
//	int i, j;
//	ArcNode *p;//����
//	G->vexnum = n;//��ʼ��������
//	G->vertices = (VNode *)malloc((n + 1)*sizeof(VNode));//ͷ�������,����n+1���ȵ�����ռ�
//	for (i = 1; i <= n; i++)//��ʼ��ͷ�������
//	{
//		G->vertices[i].data = i;
//		G->vertices[i].firstarc = NULL;
//	}
//	//////////
//	for (i = 0; i<n; i++)
//		for (j = 0; j<n; j++)
//		{
//			if (*(array + i*n + j) == 1)
//			{
//				p = (ArcNode *)malloc(sizeof(ArcNode));
//				p->adjvex = j + 1;
//				p->nextarc = G->vertices[i + 1].firstarc;
//				G->vertices[i + 1].firstarc = p;
//			}
//		}
//}
//
//void FindInDegree(ALGraph G, int *indegree)//�Զ��������
//{
//	int i, j;
//	ArcNode *p;
//	for (i = 1; i <= G.vexnum; i++)
//		indegree[i] = 0;//indispensable
//	for (i = 1; i <= G.vexnum; i++)//��ÿ��������������ڽӱ�
//		for (j = 1; j <= G.vexnum; j++)
//			for (p = G.vertices[j].firstarc; p; p = p->nextarc)
//				if (G.vertices[i].data == p->adjvex)//==
//					indegree[i]++;
//}
//
///////////���������㷨
//int TopologicalSort(ALGraph G)
//{
//	//����ͼ�����ڽӱ�洢�ṹ
//	//��G�޻�·����flag=0,���G�Ķ����һ����������,�������������ͼ�л�·����ʾ.
//	int i, count, k;
//	int *indegree = (int *)malloc((G.vexnum + 1)*sizeof(int));
//	SqStack S;
//	ArcNode *p;
//	FindInDegree(G, indegree);//�Զ��������indegree[G.vexnum]
//	initialStack(&S);//Ϊ�����ظ�������Ϊ0�Ķ��㣬������һջ�ݴ���������Ϊ0�Ķ���
//	for (i = 1; i <= G.vexnum; i++)
//		if (!indegree[i])
//			Push(&S, i);//0��ȵ��ջ
//	count = 0;//����������������Ϊ�ж��Ƿ��л�·�ĸ���
//	while (!StackEmpty(&S))
//	{
//		Pop(&S, &i);
//		printf("%d  ", i);//���i�Ŷ��㲢����
//		count++;
//		for (p = G.vertices[i].firstarc; p; p = p->nextarc)
//		{
//			k = p->adjvex;//����������򣬼���i�Ŷ����ÿ���ڽӵ����ȼ�1
//			if (!(--indegree[k]))//����ȼ���Ϊ0������ջ
//				Push(&S, k);
//		}
//	}
//	if (count<G.vexnum)//������ͼ�л�·
//		return 0;
//	else
//		return 1;
//}
//void main()
//{
//	int n;
//	int *A;
//	ALGraph G;
//	printf("���������봴�����ڽӾؾ����������(��������):\n");
//	scanf("%d", &n);
//	A = (int *)malloc(n*n*sizeof(int));
//	CreatAjacentMatrix(A, n);
//	printf("�����ͼ���ڽӾ���A:\n");
//	PrintAjacentMatrix(A, n);
//	CreatAdjList(A, n, &G);
//	printf("������ͼ��һ������������������ʾ:\n");
//	if (TopologicalSort(G))
//		printf("\n");
//	else
//		printf("������ͼ�л�·!\n");
//}
#define MAX 0
int x; //������
int a[50][50] = { 0 };//�ڽӾ���
int max = MAX; //�ؼ�·����Ȩֵ֮��
int best = 0;
int qidian[10] = { 0 };
int qi = 0;
int lujing[50] = { 0 };
int lujing1[50] = { 0 };
int k = 1;
int finish = 0;
int QQ(int *A, int P, int R)
{
	int I;
	for (I = 0; I<P; I++)
	{
		if (A[I] == R) return 1;
	}
	return 0;
}

void digui(int i,int j)
{
	while (j < x)
	{
		if (a[i][j] != 0)
		{
			best += a[i][j];
			lujing[k++] = j;
			if (j == finish)
			{
				if (best > max)
				{
					max = best;
					memcpy(lujing1, lujing, sizeof(lujing));
				}
			}
			digui(j, 0);
			k--;
			best -= a[i][j];
			j++;
		}
		else
		{
			j++;
		}
	}
}

void my_qi(int *A)
{
	for (int h1 = 0; h1 < x; h1++)
	{
		bool flag = true;
		for (int h = 0; h < x; h++)
		{
			if (a[h][h1] != 0)
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
		{
			qidian[qi++] = h1;
		}
	}
}

int main()
{
	int i, j, b, q, mm[10], p = 0;
	printf("���������봴�����ڽӾ���������(��������):\n");
	scanf("%d", &x);
	printf("������һ��%d��%d�еĹ���ͼ���ڽӾ���\n", x, x);
	for (i = 0; i<x; i++)
		for (j = 0; j<x; j++)
			scanf("%d", &a[i][j]);
	printf("�����ͼ���ڽӾ���\n");
	for (i = 0; i<x; i++)
	{
		for (j = 0; j<x; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
	for (q = 0; q<x; q++)
		for (i = 0; i<x; i++)
		{
			for (j = 0, b = 0; j<x; j++)   // bΪ·��
			{
				if (QQ(mm, p, i) || QQ(mm, p, j)) continue;//mm�������������˳��p�Ǹ���
				b += a[j][i];
			}
			if ((b == 0) && (!QQ(mm, p, i))) { mm[p] = i; p++; }
		}
	if (p == x)
	{
		printf("\n������ͼ��һ����������������ʾ��\n");
		for (i = 0; i < p; i++)
		{
			printf("%5d", mm[i]);
		}
		my_qi(mm);
		finish = mm[i - 1];
		for (int h = 0; h < qi; h++)
		{
			lujing[0] = qidian[h];
			digui(qidian[h], 0);
		}
		printf("\n%d\n", max);
		printf("·��: V%d", lujing1[0]);
		for (int h = 1; h < x; h++)
		{

			printf("->V%d", lujing1[h]);
			if (lujing1[h] == finish)
			{
				break;
			}
		}
	}
	else
	{
		printf("�л�·\n");
	}
	return 0;
}