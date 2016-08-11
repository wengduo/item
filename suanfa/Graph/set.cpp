/*************************************************************************
    > File Name: ../set.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年06月24日 星期五 15时23分38秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class UFSets
{
private:
	vector<int> parent;
	int size;
	UFSets(const UFSets &);
	UFSets & operator=(const UFSets &);
	void Print(int i) const
	{
		cout<<i<<"  ";
		for(int j = 0;j<size;++j)
		{
			if(parent[j] == i)
			{
				Print(j);
			}
		}
	}
public:
	UFSets(int sz):size(sz)
	{
		parent.resize(sz,-1);
	}
	~UFSets() {}
	int Find(int root)
	{
		while(parent[root] >= 0)
		{
			root = parent[root];
		}
		return root;
	}
public:
	bool Union(int root1,int root2)
	{
		bool res = false;
		int x = Find(root1);
		int y = Find(root2);
		if(x != y)
		{
			parent[x] += parent[y];
			parent[y] = x;
			res = true;
		}
		return res;
	}

	void Print() const
	{
		int k = 1;
		for(int i = 0;i<size;++i)
		{
			if(parent[i] < 0)
			{
				cout<<"第: "<<k++<<" 集合"<<endl;
				Print(i);
				cout<<endl;
			}
		}
	}
	void PrintQueue(int i) const
	{
		queue<int> qu;
		qu.push(i);
		while(!qu.empty())
		{
			i = qu.front(); qu.pop();
			cout<<i<<" ";
			for(int j = 0;j<size;++j)
			{
				if(parent[j] == i)
				{
					qu.push(j);
				}
			}
		}
	}
	void PrintQueue() const
	{
		int k = 0;
		for(int i = 0;i<size;++i)
		{
			if(parent[i] < 0)
			{
				cout<<"第: "<<++k<<" 集合"<<endl;
				PrintQueue(i);
				cout<<endl;
			}
		}
	}

};

int main(int argc,char *argv[])
{
	UFSets bt(12);
	bt.Print();
	bt.Union(0,4);
	bt.Union(3,1);
	bt.Union(6,10);
	bt.Union(8,9);
	bt.Union(7,4);
	bt.Union(6,8);
	bt.Union(3,5);
	bt.Union(2,11);
	bt.Union(11,0);
	bt.Print();
	return 0;
}
