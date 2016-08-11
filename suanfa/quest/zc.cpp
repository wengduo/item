/*************************************************************************
    > File Name: zc.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年08月06日 星期六 14时28分36秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

void print(int *ar,int len)
{
	int i = 0;
	while(i < len)
	{
		printf("%d ",ar[i++]);
	}
	printf("\n");
}




/*
int count = 1;
template <int MAX>
class A
{
public:
	bool place(int k)
	{
		for(int i = 0;i < k;++i)
		{
			if(hh[i] == hh[k] || (abs(hh[k] - hh[i]) == abs(k - i)))
				return false;
		}
		return true;
	}
	void display(int i)
	{
		if(i == MAX)
		{
			printf("answer:%d\n",count++);
			for(int j = 0;j < MAX;++j)
			{
				for(int k = 0;k < MAX;++k)
				{
					if(hh[k] == j)
						printf("0 ");
					else
						printf("1 ");
				}
				printf("\n");
			}
			printf("\n");
		}
		else
		{
			for(int j = 0;j < MAX;++j)
			{
				hh[i] = j;
				if(place(i))
				{
					display(i+1);
				}
			}
		}
	}
private:
		int hh[MAX];
};

int main(int argc, char *argv[])
{
	int n = 0;
	A<16> p;
	p.display(n);
	return 0;
}


int min(int a,int b)
{
	return a > b ? b : a;
}

int max(int a,int b)
{
	return a > b ? a : b;
}

int max_pr(int ar[],int n)
{
	if(n == 0) return 0;
	std::vector<int> pf(n,0);
	std::vector<int> pp(n,0);
	int minn = ar[0];
	for(int i = 1;i < n;++i)
	{
		
		minn = min(ar[i],minn);
		pf[i] = max(pf[i-1],ar[i]-minn);
	}
	for(auto &e:pf)
		printf("%d ",e);// 0 12 12 70 70 75
	printf("\n");
	int maxx = ar[n-1];
	for(int j = n-2;j >= 0;j--)
	{
		maxx = max(ar[j],maxx);
		pp[j] = max(pp[j+1],maxx-ar[j]);
	}
	for(auto &e:pp)
		printf("%d ",e);
	printf("\n");
	int max_p = 0;
	for(int i = 0;i < n;++i)
	{
		max_p = max(max_p,pf[i]+pp[i]);
	}
	return max_p;
}

int main(int argc, char *argv[])
{
	int ar[] = {10,22,5,75,65,80};
	int len = sizeof(ar)/sizeof(ar[0]);
	printf("%d\n",max_pr(ar,len));
	return 0;
}


//0-1背包
class A
{
private:
	void loop(int i)
	{
		if(i == 4)
		{
			if(lp > mp && lw <= mw)
			{
				mp = lp;
				for(int j = 0;j < 4;++j)
					llp[j] = llp1[j];
			}
		}
		else
		{
			if(lw < mw)
			{
				llp1[i] = 1;
				lw += cw[i];
				lp += cp[i];
				loop(i+1);
				llp1[i] = 0;
				lp -= cp[i];
				lw -= cw[i];
			}
			loop(i+1);
		}
	}
public:
	A(int m,int *p,int *w)
	{
		mw = m;
		lp = 0;
		mp = 0;
		lw = 0;
		for(int i = 0;i < 4;++i)
		{
			cp[i] = p[i];
			cw[i] = w[i];
			llp[i] = 0;
			llp1[i] = 0;
		}
	}
	void print()
	{
		for(int i = 0;i < 4;++i)
			printf("%d ",cw[i]);
		printf("\n");	
		for(int i = 0;i < 4;++i)
			printf("%d ",cp[i]);
		int k = 0;
		loop(k);
		printf("mp:%d\n",mp);
		for(int i = 0;i < 4;++i)
			printf("%d ",llp[i]);
	}
private:
	int mw;
	int cp[4];
	int cw[4];
	int lw;
	int mp;		
	int lp;
	int llp1[4];
	int llp[4];
};

int main(int argc, char *argv[])
{
	int mw = 12;
	int cp[] = {4,4,6,2};
	int cw[] = {2,5,7,3};
	A a(mw,cp,cw);
	a.print();
	return 0;
}
//最长增长序列
int fun(int *ar,int len)
{
	int *lis = new int[len];
	for(int i = 0;i < len;++i)
	{
		lis[i] = 1;
		for(int j = 0;j < i;++j)
		{
			if(ar[i] > ar[j] && lis[j] + 1 > lis[i])
				lis[i] = lis[j] + 1;
		}
		print(lis,len);
	}
	int tmp = 0;
	int k = 0;
	while(k < len)
	{
		printf("%d ",lis[k]);
		if(lis[k] > tmp)
			tmp = lis[k];
		k++;
	}
	return tmp;
}


int main(int argc, char *argv[])
{
	//int ar[] = {1,3,5,2,4,6,7,8};
	int ar[] = {1,-1,2,-3,4,-5,6,-7};
	printf("%d\n",fun(ar,sizeof(ar)/sizeof(ar[0])));
	return 0;
}

//超过一半的数
int fun(int *ptr,int len)
{
	int i = 1;
	int tmp = ptr[0];
	int ctime = 1;
	while(i < len)
	{
		if(ctime == 0)
		{
			tmp = ptr[i];
			ctime = 1;
		}
		else
		{
			if(tmp == ptr[i])
				ctime++;
			else
				ctime--;
		}
		i++;
	}
	if(ctime > 0)
		return tmp;
	else
		return -1;
}

int main(int argc,char *argv[])
{
	int ar[] = {2,2,3,4,5,6,2,2,2,2,2};
	printf("%d\n",fun(ar,sizeof(ar)/sizeof(ar[0])));
	return 0;
}*/
