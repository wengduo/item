
/*************************************************************************
    > File Name: gupan.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 22时51分49秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#define SIZE 8
typedef int Array[SIZE][SIZE];

void Print(Array a)
{
	for(int i = 0;i<SIZE;++i)
	{
		for(int j = 0;j<SIZE;++j)
		{
			printf("%3d",a[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int titel = 0;
void CheseChain(Array a,int tr,int tc,int dr,int dc,int size)
{
	if(size <=1) return ;
	int s = size>>1;
	int t = titel++;
	if(dr < tr+s && dc < tc+s)
	{
		CheseChain(a,tr,tc,dr,dc,s);
	}
	else
	{
		a[tr+s-1][tc+s-1] =t;
		CheseChain(a,tr,tc,tr+s-1,tc+s-1,s);
	}
	if(dr < tr+s && dc >= tc+s)
	{
		CheseChain(a,tr,tc+s,dr,dc,s);
	}
	else
	{
		a[tr+s-1][tc+s] = t;
		CheseChain(a,tr,tc+s,tr+s-1,tc+s,s);
	}
	if(dr >= tr+s && dc >= tc+s)
	{
		CheseChain(a,tr+s,tc+s,dr,dc,s);
	}
	else
	{
		a[tr+s][tc+s] = t;
		CheseChain(a,tr+s,tc+s,tr+s,tc+s,s);
	}
	if(dr >= tr+s && dc < tc+s)
	{
		CheseChain(a,tr+s,tc,dr,dc,s);
	}
	else
	{
		a[tr+s][tc+s-1] = t;
		CheseChain(a,tr+s,tc,tr+s,tc+s-1,s);
	}

}

int main()
{
	Array a={0};
	int dr,dc;
	std::cin>>dr>>dc;
	a[dr][dc]=-1;
	Print(a);
	CheseChain(a,0,0,dr,dc,SIZE);
	Print(a);
	return 0;
}
