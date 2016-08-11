/*************************************************************************
    > File Name: graph.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年06月24日 星期五 11时12分25秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <list>
#include <utility>
#include <iterator>
#include <queue>

template<class NameType,class DistType = int>
class Graph
{
private:
	std::vector<NameType,list<DistType>> adjlist;
	int vexnum;
	int arcnum;
	int kind;
public:
	Graph():vexnum(0),arcnum(0),kind(0)
	{}
	~Graph()
	{}
	void Dfs(int v,std::vector<bool> &visted)
	{
		visted[v] = true;
		std::list<DistType>::iterator it = adjlist[v].second.begin();
		for(;it != adjlist[v].second.end();++it)
		{
			if(!visted[*it])
			{
				Dfs(*it,visted);
			}
		}
	}

	void Dfs(int v)
	{
		if(v < 0 || v > vexnum) return;
		std::vector<bool> visted(vexnum,false);
		Dfs(v,visted);
		printf("\n");
	}

	void Bfs(int v)
	{
		if(v < 0 || v > vexnum) return;
		std::vector<bool> visted(vexnum,false);
		std::queue<int> qu;
		visted[v] = true;
		while(!qu.empty())
		{
			v = qu.front();qu.pop();
			std::list<DistType>::iterator it = adjlist[v].second.begin();
			for(;it != adjlist[v].second.end();++it)
			{
				if(!visted[*it])
				{
					qu.push(*it);
					visted[*it] = true;
				}
			}
		}
	}
public:
	istream & operator>>(istream &in)
	{
		int v;
		int u;
		NameType x;
		std::cout <<"请输入顶点数:"<< std::endl;
		in >> vexnum;
		std::cout <<"请输入定点数据"<< std::endl;
		for(int i = 0; i< vexnum; ++i)
		{
			in >> x;
			adjlist.push_back(make_pair(x,list<DistType>()));
			std::cout <<"请输入第"<< i+1 <<"边的个数" << std::endl;
			in >> v >> u;
			adjlist[v].second.push_back(u);
			adjlist[u].second.push_back(v);
		}
		return in;
	}
	ostream & operator<<(ostream &out) const
	{
		out <<"输出顶点的个数:" << vexnum << std::endl;
		out <<"输出定点的数据:" << std::endl;
		for(int i = 0; i < vexnum ; ++i)
		{
			std::cout << adjlist[i].first;
			std::list<DistType>::const_iterator it = adjlist[i].second.begin();
			for(;it != adjlist[i].second.end(); ++it)
			{
				out >> "->" << adjlist[*it].first;
			}
			out << std::endl;
		}
		out << std::endl;
		return out;
	}

	friend istream & operator>>(istream &in,Graph<NameType,DistType> &g)
	{
		g >> in;
		return in;
	}

	friend ostream & operator<<(ostream &out,const Graph<NameType,DistType> &g)
	{
		g << out;
		return out;
	}
};

int main(int argc,char *argv[])
{
	
	return 0;
}
