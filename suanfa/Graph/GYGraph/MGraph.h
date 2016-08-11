
#ifndef MGRAPH_H
#define MGRAPH_H
#include<functional>
#include<vector>
#include<queue>
#include<iomanip>
using namespace std;
// 
#include"MinSpanTree.h"
#include"yhp_set.h"
const int MAXINT=0x7fffffff;

template<class Type>
void Swap(Type &a,Type &b)
{
	Type c = a;
	a = b;
	b = c;
}
template<class NameType,class DistType>
class MGraph
{
private:
	vector<NameType> vexs;
	vector<vector<DistType> > edges;
	int vexnum,arcnum;
	int kind; // 0
	void DFS(int v,vector<bool> &visited)
	{
		visited[v] = true;
		cout<<setw(3)<<vexs[v];
		for(int i = 0;i<vexnum;++i)
		{
			if(!visited[i] && edges[v][i] == 1)
			{
				DFS(i,visited);
			}
		}
	}
public:
	MGraph():vexnum(0),arcnum(0),kind(0) {}
	~MGraph() {}
	int GetVexNum() const { return vexnum;}
	int GetArcNum() const { return arcnum;}
	void Prim(MinSpanTree<DistType> &mst)
	{
		int v = 0;
		int k = 0;
		MinSpanNode<DistType> item;
		for(int i = 0;i<vexnum;++i)
		{
			if(i != v)
			{
				item.head = v;
				item.tail = i;
				item.cost = edges[v][i];
				mst[k++] = item;
			}
		}
		k = 0;
		while(k < vexnum-1)
		{
			int i = k;
			for(int j = i+1;j<vexnum-1;++j)
			{
				if(mst[i].cost > mst[j].cost)
				{
					i = j;
				}
			}
			Swap(mst[k],mst[i]);
			v = mst[k].tail;
			for(int j = k+1;j<vexnum-1;++j)
			{
				if(mst[j].cost > edges[v][mst[j].tail])
				{
					mst[j].head = v;
					mst[j].cost = edges[v][mst[j].tail];
				}
			}
			++k;
		}

	}
	void Kruskal(MinSpanTree<DistType> &mst)
	{
		UFSets bt(vexnum);
		typedef priority_queue<MinSpanNode<DistType>,
			vector<MinSpanNode<DistType> >,
			greater<MinSpanNode<DistType> > > MinHeap;
		MinHeap mh;
		MinSpanNode<DistType> item;
		for(int i = 1;i<vexnum;++i)
		{
			for(int j = 0;j<i;++j)
			{
				if(edges[i][j] != MAXINT)
				{
					item.head = i;
					item.tail = j;
					item.cost = edges[i][j];
					mh.push(item);
				}
			}
		}
		///
		int k = 0;
		for(int i = 0;i<vexnum-1 && !mh.empty();++i )
		{
			item = mh.top(); mh.pop();
			if(bt.Union(item.head,item.tail))
			{
				mst[k++] = item;
			}
		}
	}
	void DFS(int v)
	{
		if(v < 0 || v > vexnum) return ;
		vector<bool> visited(vexnum,false);
		DFS(v,visited);
		cout<<endl;
	}
	void BFS(int v)
	{
		if(v < 0 || v > vexnum) return ;
		vector<bool> visited(vexnum,false);
		queue<int> qu;
		qu.push(v);
		visited[v] = true;
		while(!qu.empty())
		{
			v = qu.front(); qu.pop();
			cout<<setw(3)<<vexs[v];
			for(int i = 0;i<vexnum;++i)
			{
				if(!visited[i] && edges[v][i] == 1)
				{
					qu.push(i);
					visited[i] = true;
				}
			}
		}
		cout<<endl;
	}
public:
	istream & operator>>(istream &in)
	{
		DistType w;
		int v,u;
		NameType x;
		cout<<"请输入顶点个数: "<<endl;
		in>>vexnum;
		cout<<"请输入顶点的数据"<<endl;
		for(int i= 0;i<vexnum;++i)
		{
			in>>x;
			vexs.push_back(x);
		}
		////edges/////////////
		edges.resize(vexnum);
		for(int i = 0;i<vexnum;++i)
		{
			edges[i].resize(vexnum,MAXINT);
		}
		for(int i = 0;i<vexnum;++i)
		{
			edges[i][i] = 0;
		}

		cout<<"请输入边的个数 : "<<endl;
		in>>arcnum;
		for(int i = 0;i<arcnum; ++i)
		{
			cout<<"输入第 "<<i+1<<"边 "<<endl;
			in>>v>>u>>w;
			edges[v][u] = w;
			edges[u][v] = w;
		}
		return in;
	}
	ostream & operator<<(ostream &out) const
	{
		out<<"输出顶点的个数: "<< vexnum<<endl;
		out<<"输出顶点的数据: "<<endl;
		for(int i = 0;i<vexnum;++i)
		{
			out<<setw(3)<<vexs[i];
		}
		out<<endl;
		out<<"输出边的个数: "<<arcnum<<endl;
		out<<"输出邻接矩阵: "<<endl;
		for(int i = 0;i<vexnum; ++i)
		{
			for(int j = 0;j<vexnum;++j)
			{
				if(edges[i][j] != MAXINT)
				{
					out<<setw(3)<<edges[i][j];
				}else
				{
					out<<setw(3)<<"@";
				}
			}
			out<<endl;
		}
		out<<endl;
		return out;
	}
	friend istream & operator>>(istream &in,MGraph<NameType,DistType> &g)
	{
		g>>in;
		return in;
	}
	friend ostream & operator<<(ostream &out,const MGraph<NameType,DistType> &g)
	{
		g<<out;
		return out;
	}

};


#endif
