
#include <vector>
#include <iostream>
#include <cstdio>
#include <iterator>
using namespace std;

template<class DistType>
struct MinSpanNode
{
	int head,tail;
	DistType cost;
public:
	operator DistType() const 
	{
		return cost;
	}
};
template<class DistType>
class MinSpanTree
{
private:
	vector<MinSpanNode<DistType> > edgevalue;
	int minarcnum;
public:
	MinSpanTree(int sz=0):minarcnum(sz)
	{
		edgevalue.resize(minarcnum);
	}
	MinSpanNode<DistType> & operator[](int index) 
	{
		if(index < 0 || index > minarcnum)
		{
			cout<<"out_of_range"<<endl;
			exit(1);
		}
		return edgevalue[index];
	}
	const MinSpanNode<DistType>  & operator[](int index) const 
	{
		if(index < 0 || index > minarcnum)
		{
			cout<<"out_of_range"<<endl;
			exit(1);
		}
		return edgevalue[index];
	}
	void Print_MinTree() const
	{
		typename vector<MinSpanNode<DistType>>::const_iterator p = edgevalue.begin();
		for(; p != edgevalue.end(); ++p)
		{
			std::cout << p->head << " : " << p->tail << "-> " << p->cost << std::endl;
		}
		std::cout << std::endl;
	}
};
