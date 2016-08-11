
/*************************************************************************
    > File Name: dj.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月06日 星期三 17时23分40秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cmath>
#define INTMAX 0x7fffffff
template<class Type>
int min(Type *ar,int left,int right)
{
	int tmp = ar[left];
	for(int i = left;i <= right;++i)
	{
		if(ar[i] < tmp)
		{
			tmp = ar[i];
		}
	}
	return tmp;
}

template<class Type>
int max(Type *ar,int left,int right)
{
	int tmp = ar[left];
	for(int i = left;i <= right;++i)
	{
		if(ar[i] > tmp)
		{
			tmp = ar[i];
		}
	}
	return tmp;
}

int min(int s1,int s2,int s3)
{
	if(s1 < s2 && s1 < s3)
	{
		return s1;
	}
	else if(s2 < s3 && s2 < s1)
	{
		return s2;
	}
	else
	{
		return s3;
	}
}

template<class Type>
int Partition(Type *ar,int left,int right)
{
	int i = left,j = right;
	Type tmp = ar[i];
	while(i<j)
	{
		while(i < j && ar[j] >= tmp) --j;
		ar[i] = ar[j];
		if(i < j) ++i;
		while(i < j && ar[i] <= tmp) ++i;
		ar[j] = ar[i];
		if(i < j) --j;
	}
	ar[i] = tmp;
	return i;
}

template<class Type>
const Type & SelectK(Type *ar,int left,int right, int k)
{
	if(left == right && k == 1) return ar[left];
	int i = Partition(ar,left,right);
	int j = k - 1;
	if(j == i) return ar[i];
	if(j < i) return SelectK(ar,left,i-1,k);
	else return SelectK(ar,i+1,right,k);
}

template<class Type>
int dianju(Type *ar,int left,int right)
{
	if(right - left <= 0) return INTMAX;
	else if(right - left == 1)
	{
		return ar[right] - ar[left];
	}
	else
	{
		int m = ((right - left)>>1) + left;
		SelectK(ar,left,right,m);
		int h1 = dianju(ar,left,m);
		int h2 = dianju(ar,m+1,right);
		int s1 = max(ar,left,m);
		int s2 = min(ar,m+1,right);
		return min(h1,h2,fabs(s1-s2));
	}
}

int main(int argc,char *argv[])
{
	int ar[]={56,34,90,23,18,100,87,10,45,78,65};
	int n = sizeof(ar)/sizeof(ar[0]);
	int dj = dianju(ar,0,n-1);
	printf("%d\n",dj);
  return 0;
}

