

#ifndef YHP_SET_H
#define YHP_SET_H
#include<vector>
#include<algorithm>
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
/*

template<class Type> 
class Set
{
private:
	vector<Type> data;
public:
	Set(int sz=100)
	{
		data.resize(100);
	}
	Set(const Set<Type> &s):data(s.data){}
	~Set() {}

	void MakeEmpty()
	{
		data.clear();
	}
	void AddMember(const Type &_X)
	{
		vector<Type>::iterator it = find(data.begin(),data.end(),_X);
		if(it == data.end())
		{
			data.push(_X);
			sort(data.begin(),data.end());
		}
	}
	void DelMember(const Type &_X)
	{
		vector<Type>::iterator it = find(data.begin(),data.end(),_X);
		if(it != data.end())
		{
			data.erase(it);
		}
	}
	bool operator==(const Set<Type> &_Y)
	{
		return this->data == _Y.data;
	}
	bool operator !=(const Set<Type> &_Y)
	{
		return !(*this == _Y);
	}
	int Contains(const Type &_X)
	{
		vector<Type>::iterator it = find(data.begin(),data.end(),_X);
		if(it == data.end())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	Set<Type>  operator+(const Set<Type> &_X) //相并
	{
		Set<Type> tmp(*this);
		tmp.data.insert(tmp.data.end(),_X.data.begin(),_X.data.end());
		sort(tmp.data.begin(),tmp.data.end());
		unique(tmp.data.begin(),tmp.data.end());
		return tmp;
	}
	Set<Type> operator*(const Set<Type> &_X) // 相交
	{
	}

	int SubSet(const Set<Type> &_X);

}

*/
#endif