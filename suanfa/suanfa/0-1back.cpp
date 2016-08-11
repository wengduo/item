
#include<IOSTREAM.H>
#include<IOMANIP.H>
#include<MALLOC.H>
#include<STRING.H>
int ** Get2Array(int n,int m)
{
	int **s = (int**)malloc(sizeof(int*)*n);
	for(int i =0;i<n;++i)
	{
		s[i] = (int*)malloc(sizeof(int)*m);
		memset(s[i],0,sizeof(int)*m);
	}
	return s;
}
void Del2Array(int **s,int n)
{
	for(int i = 0;i<n;++i)
	{
		free(s[i]);
	}
	free(s);
}
void Print2Array(int **s,int n,int m)
{
	for(int i = 0;i<n;++i)
	{
		for(int j = 0;j<m;++j)
		{
			cout<<setw(4)<<s[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
int Max(int a,int b)
{
	return a>b? a:b;
}
const int SIZE = 5;
void Knapsack(int W[],int V[],int n,int c,int **m)
{
	for(int i = 1;i<=c;++i)
	{
		if(i<W[n])
		{
			m[n][i]= 0;
		}else
		{
			m[n][i]=V[n];
		}
	}
	for(i = n-1;i>=1;--i)
	{
		for(int j = 1;j<=c;++j)
		{
			if(j<W[i])
				m[i][j]= m[i+1][j];
			else
				m[i][j] = Max(m[i+1][j],m[i+1][j-W[i]]+V[i]);
		}
	}
}
void TrackBack(int **m,int n,int c,int W[],bool X[])
{
	for(int i = 1;i<n;++i)
	{
		if(m[i][c] != m[i+1][c])
		{
			X[i] = true;
			c -= W[i];
		}
	}
	if(m[i][c] != 0)
	{
		X[i] = true;
	}
}
void main()
{
	int W[SIZE+1]={0,2,2,6,5,4};
	int V[SIZE+1]={0,6,3,5,4,6};
	bool X[SIZE+1]={0};
	int c = 10;
	int **m = Get2Array(SIZE+1,c+1);
	Print2Array(m,SIZE+1,c+1);
	Knapsack(W,V,SIZE,c,m);
	Print2Array(m,SIZE+1,c+1);
	TrackBack(m,SIZE,c,W,X);
	for(int i = 1;i<=SIZE;++i)
	{
		if(X[i])
		{
			cout<<i<<" ";
		}
	}
	cout<<endl;
}

/*
int Knapsack(int W[],int V[],int i,int n,int j,int **m)
{
if(i == n)
{
if(j>=W[i]) m[i][j] = V[n];
else m[i][j]= 0;
return m[i][j];
}else if(m[i][j] > 0) return m[i][j];
else
{
if(j<W[i]) 
{
m[i][j] = Knapsack(W,V,i+1,n,j,m);
return m[i][j];
}
else
{
int max1 = Knapsack(W,V,i+1,n,j,m);
int max2 = Knapsack(W,V,i+1,n,j-W[i],m)+V[i];
m[i][j]= max1 > max2 ? max1:max2;
return m[i][j];
}
}
}
*/