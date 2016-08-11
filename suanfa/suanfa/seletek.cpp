
/*************************************************************************
    > File Name: seletek.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月04日 星期一 20时40分46秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

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
{// 56,34,90,23,18,100,89,10,45,78,65 // 2  5  7
	//if(left == right && k == 1) return ar[left];
	int i = Partition(ar,left,right);
	//int j = i-left + 1;
	int j = k - 1;
	if(j == i) return ar[i];
	if(j < i) return SelectK(ar,left,i-1,k);
	else return SelectK(ar,i+1,right,k);
	//if(k <= j) return SelectK(ar,left,i,k);
	//else return SelectK(ar,i+1,right,k-j);
}
template<class Type>
const Type & SelectKMin(Type *ar,int n, int k)
{
	if(ar == NULL || n < 1 || k <1 || k > n) 
		exit(1);

	return SelectK(ar,0,n-1,k);
}

int main()
{
	int ar[]={56,34,90,23,18,100,89,10,45,78,65};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int k=1;k<=n;++k)
	{
		int x = SelectKMin(ar,n,k);
		std::cout << k <<"==> "<< x << std::endl;
	}
	return 0;
}

