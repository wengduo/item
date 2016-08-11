
/*************************************************************************
    > File Name: quick.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 23时24分09秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;++i)
	{
		std::cout << ar[i] << "  ";
	}
	std::cout << std::endl;
}

template<class Type>
int Partition(Type *ar,int left,int right)
{
	int i = left,j = right;
	Type tmp = ar[i];
	while(i<j)
	{
		while(i<j && ar[j] >= tmp) --j;
		if(i<j) 
		{
			ar[i] = ar[j];
			i++;
		}
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j)	
		{
			ar[j] = ar[i]; j--;
		}
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
void QuickPass(Type *ar,int left,int right)
{
	if(left < right)
	{
		int mid = Partition(ar,left,right);
		QuickPass(ar,left,mid-1);
		QuickPass(ar,mid+1,right);
	}
}

template<class Type>
void QuickSort(Type *ar,int n)
{
	QuickPass(ar,0,n-1);
}
int main()
{
	int ar[]={12,78,90,23,34,56,45};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	QuickSort(ar,n);
	Print(ar,n);
	return 0;
}


