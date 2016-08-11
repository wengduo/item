/*************************************************************************
    > File Name: heap.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月04日 星期一 21时09分50秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#define HEAPSIZE 100
template<class Type>
class MinHeap
{
private:
	Type *heap; 
	int cursize;
	int maxsize;
	
	static void FilterDown(Type *ar,const int start,const int end)
	{
		int i = start, j = 2*i;
		ar[0] = ar[i];
		while(j <= end)
		{
			if(j < end && ar[j] > ar[j+1]) ++j;
			if(ar[0] <= ar[j]) break;
			ar[i] = ar[j];
			i = j;
			j = 2*i;
		}
		ar[i] = ar[0];
	}
	static void FilterUp(Type *ar,const int start,const int end)
	{
		int j = start,i = j/2;
		ar[0] = ar[j];
		while(i >= end)
		{
			if(ar[i] <= ar[0]) break;
			ar[j] = ar[i];
			j = i;
			i = j/2;
		}
		ar[j] = ar[0];
	}
public:
	MinHeap(int sz = HEAPSIZE)
	{
		cursize = 0;
		maxsize = sz > HEAPSIZE ? sz:HEAPSIZE;
		heap = (Type*)malloc(sizeof(Type)*(maxsize+1));
	}
	~MinHeap()
	{
		free(heap);
		heap = NULL;
		cursize = maxsize = 0;
	}

	MinHeap(Type *ar,int n)
	{
		cursize = n;
		maxsize = n > HEAPSIZE ? n : HEAPSIZE;
		heap = (Type*)malloc(sizeof(Type)*(maxsize+1));
		for(int i = 0;i<n;++i)
		{
			heap[i+1] = ar[i];
		}
		int pos = cursize/2;
		while(pos > 0)
		{
			FilterDown(heap,pos,cursize);
			--pos;
		}
	}
	int size() const { return cursize;}
	bool empty() const { return size() == 0;}
	bool full() const { return size() == maxsize;}

	bool Remove(Type &x)
	{
		if(empty()) return false;
		x = heap[1];
		heap[1] = heap[cursize--];
		FilterDown(heap,1,cursize);
		return true;
	}

	bool Insert(const Type &x)
	{
		if(full())
			return false;
		heap[++cursize] = x;
		FilterUp(heap,cursize,1);
		return true;
	}
};
int main()
{
	int ar[]={56,34,90,23,18,100,89,10,45,78,65};
	int n = sizeof(ar)/sizeof(ar[0]);
	MinHeap<int> mh;
	for(int i = 0;i<n;++i)
	{
		mh.Insert(ar[i]);
	}

	int x;
	while(mh.Remove(x))
	{
		std::cout << x <<" ";
	}
	std::cout << std::endl;
	return 0;
}
