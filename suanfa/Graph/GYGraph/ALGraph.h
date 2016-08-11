
#ifndef ALGRAPH_H
#define ALGRAPH_H
#include<vector>
#include<list>
#include<utility>
using namespace std;

template<class NameType,class DistType = int>
class ALGraph
{
private:
	vector<pair<NameType,list<DistType> > > adjlist;
	int vexnum,arcnum;
	int kind;
public:
	ALGraph():vexnum(0),arcnum(0),kind(0) {}
	~ALGraph(){}
	void DFS(int v,vector<bool> &visited)
	{
		visited[v] = true;
		cout<<setw(3)<<adjlist[v].first;
		list<DistType>::iterator it = adjlist[v].second.begin();
		for(; it != adjlist[v].second.end(); ++it)
		{
			if(!visited[*it])
			{
				DFS(*it,visited);
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
			cout<<setw(3)<<adjlist[v].first;
			list<DistType>::iterator it = adjlist[v].second.begin();
			for(; it != adjlist[v].second.end(); ++it)
			{
				if(!visited[*it])
				{
					qu.push(*it);
					visited[*it] = true;
				}
			}
		}
	}
public:
	istream & operator>>(istream &in)
	{
		int v,u;
		NameType x;
		cout<<"请输入顶点个数: "<<endl;
		in>>vexnum;
		cout<<"请输入顶点的数据"<<endl;
		for(int i= 0;i<vexnum;++i)
		{
			in>>x;
			adjlist.push_back(make_pair(x,list<DistType>()));
		}
		cout<<"请输入边的个数 : "<<endl;
		in>>arcnum;
		for(int i = 0;i<arcnum; ++i)
		{
			cout<<"输入第 "<<i+1<<"边 "<<endl;
			in>>v>>u;
			adjlist[v].second.push_back(u);
			adjlist[u].second.push_back(v);
		}
		return in;
	}
	ostream & operator<<(ostream &out) const
	{
		out<<"输出顶点的个数: "<< vexnum<<endl;
		out<<"输出顶点的数据: "<<endl;
		for(int i = 0;i<vexnum;++i)
		{
			cout<<adjlist[i].first;
			list<DistType>::const_iterator it = adjlist[i].second.begin();
			for(; it != adjlist[i].second.end(); ++it)
			{
				out<<" -> "<<adjlist[*it].first;
			}
			out<<endl;
		}
		out<<endl;
		return out;
	}
	friend istream & operator>>(istream &in,ALGraph<NameType,DistType> &g)
	{
		g>>in;
		return in;
	}
	friend ostream & operator<<(ostream &out,const ALGraph<NameType,DistType> &g)
	{
		g<<out;
		return out;
	}

};

#endif