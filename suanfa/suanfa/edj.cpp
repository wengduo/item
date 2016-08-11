
/*************************************************************************
    > File Name: edj.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月06日 星期三 22时43分46秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#define SIZE 10
#define FLOATMAX 3.4e38f
typedef struct _PaintA
{
	int index;
	int x;
	int y;
	friend bool operator<(const _PaintA &a,const _PaintA &b)
	{
		if(a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
}PaintA;

double my_distance(const PaintA a,const PaintA b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double smaller(double p,double q)
{
	return (p>q) ? q:p;
}

PaintA *my_rand(int n)
{
	PaintA *p = new PaintA[n];
	for(int i = 0;i < n;++i)
	{
		p[i].x = rand()%171 + rand()%23 + 17;
		p[i].y = rand()%231 + rand()%17 + 31;
	}
	return p;
}

PaintA *ar =	NULL;	
double Closest_distance(int left, int right,PaintA &a,PaintA &b)
{
    double d = FLOATMAX;
    double distance_tmp;
 
    if(left == right)
		{
      return FLOATMAX;
		}
    if(right - left == 1)
		{
      double minf = my_distance(ar[left],ar[right]);
			a = ar[left];
			b = ar[right];
			return minf;
		}
		if(right - left == 2)
		{
			float d1 = my_distance(ar[left],ar[left+1]);
			float d2 = my_distance(ar[left+1],ar[right]);
			float d3 = my_distance(ar[left],ar[right]);
			if(d1 < d2 && d1 < d3)
			{
				a = ar[left];
				b = ar[left+1];
				return d1;
			}
			else if(d2 < d3 && d2 < d1)
			{
				a = ar[left+1];
				b = ar[right];
				return d2;
			}
			else
			{
				a = ar[left];
				b = ar[right];
				return d3;
			}
		}
    int mid = ((right-left)>>1) + left;
    d = Closest_distance(left,mid,a,b);
		PaintA a2,b2;
		int d2 = Closest_distance(mid,right,a2,b2);
		if(d > d2)
		{
			d = d2;
			a = a2;
			b = b2;
		}
 
    for(int i=mid-1; i>=left && ar[mid].x - ar[i].x < d; i--)
		{
      for(int j = mid+1; j<=right && ar[j].x - ar[mid].x < d && fabs(ar[i].y - ar[j].y) < d; j++)
			{
        distance_tmp = my_distance(ar[i],ar[j]);
        if(distance_tmp < d)
				{
          d = distance_tmp;
					a = ar[i];
					b = ar[j];
				}
      }
    } 
    return d;
}
int main(int argc,char *argv[])
{
	int n;
	std::cin >> n;
	ar = my_rand(n);
	std::sort(ar,ar+n);
	for(int i = 0;i < n;++i)
	{
		std::cout << ar[i].x << "," << ar[i].y << std::endl;
	}
	PaintA a,b;
	double k = Closest_distance(0,n-1,a,b);
	std::cout << "a" << a.x << "," << a.y << std::endl;;
	std::cout << "b" << b.x << "," << b.y << std::endl;;
	printf("%lf\n",k);
	return 0;
}

