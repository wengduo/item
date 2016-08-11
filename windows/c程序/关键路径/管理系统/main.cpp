#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 26   //��󶥵����� 
#define MAXM 100000   //�������� 

typedef char VertexType; //�����������û��Զ���
typedef int EdgeType; //���ϵ�Ȩֵ�������û��Զ���

typedef struct Edge{ //�߼����� 
	int u;
	int v; //��β�ͻ�ͷ 
	int next; //ָ��ͬһ����β����һ���� 
	EdgeType w; //Ȩֵ�����ڷ���ͼ���Բ���Ҫ 
} EdgeLib;

//void PrintGraph(int first[], EdgeLib edge[], int n);//���ͼ
//void CriticalPath(EdgeLib edge[], int In[], int first[], int n);//��ؼ�·�� 
//void PrintPath(EdgeLib edge[], int first[], int Etv[], int Ltv[], int path[], int top, int end);


void PrintGraph(int first[], EdgeLib edge[], int n)//���ͼ
{
	int i, j;

	for (i = 0; i<n; i++)
	{
		printf("G[%d] = %c: ", i, i + 'a');
		j = first[i]; //ָ��i�ĵ�һ���� 
		while (j != -1)
		{
			printf("<%c, %c>, ", edge[j].u + 'a', edge[j].v + 'a');
			j = edge[j].next; //ָ����һ���� 
		}
		printf("\n");
	}
	printf("\n");
}

int TopoLogicalSort(int topo[], int Etv[], EdgeLib edge[], int In[], int first[], int n)
{
	int i, k, front, rear;

	front = rear = 0;
	for (i = 0; i<n; i++)//�����Ϊ0�Ķ�������� 
	{
		Etv[i] = 0; //��ʼ�����¼����緢���¼�Ϊ0 
		if (In[i] == 0)
		{
			topo[rear++] = i;
		}
	}

	while (front < rear)//���ù������������ȡ�������� 
	{
		k = topo[front++];
		for (i = first[k]; i != -1; i = edge[i].next)
		{
			if (--In[edge[i].v] == 0)
				topo[rear++] = edge[i].v;

			if (Etv[edge[i].v] < Etv[edge[i].u] + edge[i].w)//���¸������¼������緢��ʱ�� 
				Etv[edge[i].v] = Etv[edge[i].u] + edge[i].w;
		}
	}

	return (rear == n);//���countС�ڶ�������˵�����ڻ� 
}
void CriticalPath(EdgeLib edge[], int In[], int first[], int n)//��ؼ�·�� 
{
	int i, j;
	int topo[MAXN], path[MAXN];
	int Etv[MAXN], Ltv[MAXN];//�洢�¼��������������ʱ�� 

	if (!TopoLogicalSort(topo, Etv, edge, In, first, n))
	{
		puts("�����ڹؼ�·��");
		return;
	}

	for (i = 0; i<n; i++)
	{
		Ltv[i] = Etv[n - 1]; //��ʼ�����¼��������¼�Ϊ���һ���¼�������ʱ�� 
	}

	for (j = n - 2; j >= 0; j--)
	{
		for (i = first[topo[j]]; i != -1; i = edge[i].next)
		{
			if (Ltv[edge[i].u] > Ltv[edge[i].v] - edge[i].w)//���¸������¼���������ʱ�� 
				Ltv[edge[i].u] = Ltv[edge[i].v] - edge[i].w;
		}
	}

	path[0] = topo[0];
	PrintPath(edge, first, Etv, Ltv, path, 1, topo[n - 1]);
}

void PrintPath(EdgeLib edge[], int first[], int Etv[], int Ltv[], int path[], int top, int end)//���������������ؼ�·�� 
{
	int i, u = path[top - 1];

	if (u == end)
	{
		printf("%d", path[0]); //����ؼ�·�� 
		for (i = 1; i<top; i++)
		{
			printf("->%d", path[i]);
		}
		printf("\n");
		return;
	}

	for (i = first[u]; i != -1; i = edge[i].next)
	{
		if (Etv[edge[i].v] == Ltv[edge[i].v])//�ؼ��¼�
		{
			path[top++] = edge[i].v; //��ջ 
			PrintPath(edge, first, Etv, Ltv, path, top, end);
			top--; //��ջ 
		}
	}
}
int main()
{
	int i, m, n;
	int In[MAXN], first[MAXN]; //�洢������Ϣ
	EdgeLib edge[MAXM]; //�洢����Ϣ 

	for (i = 0; i<MAXN; i++)//��ʼ��ͼ 
	{
		first[i] = -1;
		In[i] = 0;
	}

	printf("�����붥�������ͱ�����:");
	scanf("%d%d", &n, &m);
	for (i = 0; i<m; i++)
	{
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
		edge[i].next = first[edge[i].u];
		first[edge[i].u] = i;
		In[edge[i].v]++;
	}

	CriticalPath(edge, In, first, n);//��ؼ�·��

	return 0;
}