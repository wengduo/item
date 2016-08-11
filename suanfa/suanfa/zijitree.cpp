
/*************************************************************************
    > File Name: zijitree.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月02日 星期六 23时30分53秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
void Print(int *ar,int *br,int i,int n)
{
	if(i >= n)
	{
		int j;
		for(j = 0;j<n;++j)
		{
			std::cout << br[j] << " ";
		}
		for(j = 0;j < n; ++j)
		{
			if(br[j] == 1)
			{
				std::cout << ar[j] << " ";
			}
		}
		std::cout << std::endl;
	}
	else
	{
		Print(ar,br,i+1,n); // left
		//right
		br[i] = 1;
		Print(ar,br,i+1,n);
		br[i] = 0;
	}
}
int main()
{
	int ar[3]={1,2,3};
	int br[3]={0,0,0};

	Print(ar,br,0,3);
	return 0;
}
