
/*************************************************************************
    > File Name: findvalue.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 23时05分21秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

template<class Type>
int FindValue(Type *ar,int n,const Type &x)
{
	if(ar == NULL || n < 1) return -1;
	int left = 0,right =n-1;
	while(left <= right)
	{
		int mid = ((right-left)>>1)+ left;
		if(ar[mid] == x) 
		{
			while(ar[mid-1] == x) 
				mid-=1;
			return mid;
		}
		if(x < ar[mid])
		{
			right = mid-1;
		}
		else
		{
			left = mid+1;
		}
	}
	return -1;
}

template <class Type>
int Serach(Type *ar,int left,int right,const Type &x)
{
	if(left <= right)
	{
		int mid = ((right-left)>>1)+left;
		if(ar[mid] == x)
		{
			while(ar[mid-1] == x) mid -= 1;
			return mid;
		}
		if(x < ar[mid] ) return Serach(ar,left,mid-1,x);
		else return Serach(ar,mid+1,right,x);
	}
	else
	{
		return -1;
	}
}

template<class Type>
int SearchValue(Type *ar,int n,const Type &x)
{
	if(ar == NULL || n < 1) return -1;
	else 
		return Serach<Type>(ar,0,n-1,x);
}

int main()
{
	int ar[]={12,23,34,45,45,45,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	//int pos = FindValue(ar,n,45);
	int pos = SearchValue(ar,n,45);
	printf("%d\n",pos);
	return 0;
}
