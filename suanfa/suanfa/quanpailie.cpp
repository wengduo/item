
/*************************************************************************
    > File Name: quanpailie.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 23时20分10秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

template<class Type>
void Swap(Type &a,Type &b)
{
	Type c= a;
	a = b;
	b = c;
}
template<class Type>
void Perm(Type *ar,int k,int m)
{
	if(k == m) 
	{
		for(int i = 0;i<=m;++i)
		{
			std::cout << ar[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for(int j = k;j<=m;++j)
		{
			Swap(ar[j],ar[k]);
			Perm(ar,k+1,m);
			Swap(ar[j],ar[k]);
		}
	}
}
int main()
{
	int R[]={1,2,3};
	int n = sizeof(R)/sizeof(R[0]);
	Perm(R,0,n-1);
	return 0;
}
