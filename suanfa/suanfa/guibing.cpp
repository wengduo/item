
/*************************************************************************
    > File Name: guibing.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 23时25分41秒
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
void Copy(Type *sd,Type *si,int left,int right)
{
	for(int i = left; i<=right; ++i)
	{
		sd[i] = si[i];
	}
}
template<class Type>
void Merge(Type *sd,Type *si,int left,int m,int right)
{
	int i = left,j = m+1;
	int k = left;
	while(i<=m && j<=right)
	{
		sd[k++] = si[i]<si[j]? si[i++]:si[j++];
	}
	while(i<=m)
	{
		sd[k++] = si[i++];
	}
	while(j<=right)
	{
		sd[k++] = si[j++];
	}
}

template<class Type>
void MergePass(Type *sd,Type *si,int s,int n)
{
	int i;
	for(i = 0;i+2*s <= n;i+=2*s)
	{
		Merge(sd,si,i,i+s-1,i+2*s-1);
	}
	if(n-1 >= i+s)
	{
		Merge(sd,si,i,i+s-1,n-1);
	}
	else
	{
		for(int j = i;j<n;++j)
		{
			sd[j] = si[j];
		}
	}
}

template<class Type>
void MergeSort(Type *ar,int n)
{
	Type *br = new Type[n];
	int s = 1;
	while(s < n)
	{
		MergePass(br,ar,s,n);
		s+=s;
		MergePass(ar,br,s,n);
		s+=s;
	}
	delete []br;
}

int main()
{
	int ar[]={12,78,90,23,34,56,45};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	MergeSort(ar,n);
	Print(ar,n);
	return 0;
}

/*
template<class Type>
void MergePass(Type *br,Type *ar,int left,int right)
{
	if(left < right)
	{
		int m = ((right - left)>>1) + left;
		MergePass(br,ar,left,m);
		MergePass(br,ar,m+1,right);
		Merge(br,ar,left,m,right);
		Copy(ar,br,left,right);
	}
}

template<class Type>
void MergeSort(Type *ar,int n)
{
	Type *br = new Type[n];
	MergePass(br,ar,0,n-1);
	delete []br;
}
void main()
{
	int ar[]={34,56,78,90,12,23,100,18,45,56,70};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	MergeSort(ar,n);
	Print(ar,n);
}

*/



