#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 26   //最大顶点数量 
#define MAXM 100000   //最大边数量 

typedef char VertexType; //顶点类型由用户自定义
typedef int EdgeType; //边上的权值类型由用户自定义

typedef struct Edge{ //边集数组 
	int u;
	int v; //弧尾和弧头 
	int next; //指向同一个弧尾的下一条边 
	EdgeType w; //权值，对于非网图可以不需要 
} EdgeLib;

//void PrintGraph(int first[], EdgeLib edge[], int n);//输出图
//void CriticalPath(EdgeLib edge[], int In[], int first[], int n);//求关键路径 
//void PrintPath(EdgeLib edge[], int first[], int Etv[], int Ltv[], int path[], int top, int end);


void PrintGraph(int first[], EdgeLib edge[], int n)//输出图
{
	int i, j;

	for (i = 0; i<n; i++)
	{
		printf("G[%d] = %c: ", i, i + 'a');
		j = first[i]; //指向i的第一条边 
		while (j != -1)
		{
			printf("<%c, %c>, ", edge[j].u + 'a', edge[j].v + 'a');
			j = edge[j].next; //指向下一条边 
		}
		printf("\n");
	}
	printf("\n");
}

int TopoLogicalSort(int topo[], int Etv[], EdgeLib edge[], int In[], int first[], int n)
{
	int i, k, front, rear;

	front = rear = 0;
	for (i = 0; i<n; i++)//将入度为0的顶点入队列 
	{
		Etv[i] = 0; //初始化各事件最早发生事件为0 
		if (In[i] == 0)
		{
			topo[rear++] = i;
		}
	}

	while (front < rear)//采用广度优先搜索获取拓扑序列 
	{
		k = topo[front++];
		for (i = first[k]; i != -1; i = edge[i].next)
		{
			if (--In[edge[i].v] == 0)
				topo[rear++] = edge[i].v;

			if (Etv[edge[i].v] < Etv[edge[i].u] + edge[i].w)//更新各顶点事件的最早发生时间 
				Etv[edge[i].v] = Etv[edge[i].u] + edge[i].w;
		}
	}

	return (rear == n);//如果count小于顶点数，说明存在环 
}
void CriticalPath(EdgeLib edge[], int In[], int first[], int n)//求关键路径 
{
	int i, j;
	int topo[MAXN], path[MAXN];
	int Etv[MAXN], Ltv[MAXN];//存储事件的最早和最晚发生时间 

	if (!TopoLogicalSort(topo, Etv, edge, In, first, n))
	{
		puts("不存在关键路径");
		return;
	}

	for (i = 0; i<n; i++)
	{
		Ltv[i] = Etv[n - 1]; //初始化各事件最晚发生事件为最后一个事件发生的时间 
	}

	for (j = n - 2; j >= 0; j--)
	{
		for (i = first[topo[j]]; i != -1; i = edge[i].next)
		{
			if (Ltv[edge[i].u] > Ltv[edge[i].v] - edge[i].w)//更新各顶点事件的最晚发生时间 
				Ltv[edge[i].u] = Ltv[edge[i].v] - edge[i].w;
		}
	}

	path[0] = topo[0];
	PrintPath(edge, first, Etv, Ltv, path, 1, topo[n - 1]);
}

void PrintPath(EdgeLib edge[], int first[], int Etv[], int Ltv[], int path[], int top, int end)//深度优先搜索输出关键路径 
{
	int i, u = path[top - 1];

	if (u == end)
	{
		printf("%d", path[0]); //输出关键路径 
		for (i = 1; i<top; i++)
		{
			printf("->%d", path[i]);
		}
		printf("\n");
		return;
	}

	for (i = first[u]; i != -1; i = edge[i].next)
	{
		if (Etv[edge[i].v] == Ltv[edge[i].v])//关键事件
		{
			path[top++] = edge[i].v; //入栈 
			PrintPath(edge, first, Etv, Ltv, path, top, end);
			top--; //退栈 
		}
	}
}
int main()
{
	int i, m, n;
	int In[MAXN], first[MAXN]; //存储顶点信息
	EdgeLib edge[MAXM]; //存储边信息 

	for (i = 0; i<MAXN; i++)//初始化图 
	{
		first[i] = -1;
		In[i] = 0;
	}

	printf("请输入顶点数量和边数量:");
	scanf("%d%d", &n, &m);
	for (i = 0; i<m; i++)
	{
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].next = first[edge[i].u];
		first[edge[i].u] = i;
		In[edge[i].v]++;
	}

	CriticalPath(edge, In, first, n);//求关键路径

	return 0;
}