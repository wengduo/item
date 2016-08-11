
/*************************************************************************
    > File Name: zui.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月14日 星期四 16时45分24秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#define LSIZE 10
#define RSIZE 9
int ps[LSIZE][RSIZE] = {0};
template <class T>
T Max(const T a,const T b)
{
	return a>b?a:b;
}

int kxl(const char *p,int pk,const char *s,int sk)
{
	if(pk < 0 || sk < 0) return 0;
	else
	{
		if(p[pk] == s[sk])
		{
			 ps[sk][pk] = kxl(p,pk-1,s,sk-1) + 1;
			 return ps[sk][pk];
			//return kxl(p,--pk,s,--sk) + 1;
		}
		else
		{
			ps[sk][pk] =  Max(kxl(p,pk-1,s,sk),kxl(p,pk,s,sk-1));
			return ps[sk][pk];
			//return Max(kxl(p,pk-1,s,sk),kxl(p,pk,s,sk-1));
		}
	}
}

int zcggzxl(const char *p,const char *s)
{
	if(NULL == p || NULL == s) return -1;
	else
	{
		int pk = strlen(p);
		int sk = strlen(s);
		return kxl(p,pk-1,s,sk-1);
	}
}

void Print()
{
	for(int i = 0;i < LSIZE;++i)
	{
		for(int j = 0;j < RSIZE;++j)
		{
			printf("%3d ",ps[i][j]);
		}
		printf("\n");
	}
}

int main(int argc,char *argv[])
{
	const char *p1 = "adacvacbh";
	const char *p2 = "ddhvfagbh";
	Print();
	printf("************************\n");
	int k = zcggzxl(p1,p2);
	Print();
	printf("************************\n");
	printf("%d\n",k);
  return 0;
}

