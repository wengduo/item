#include<iostream.h>
#include<iomanip.h>
#include<malloc.h>
#include<stdlib.h>
template<class Type>
int Partition(Type *ar,int left,int right)
{
	int i = left,j = right;
	Type tmp = ar[i];
	while(i<j)
	{
		while(i<j && ar[j] >= tmp) --j;
		if(i<j) ar[i] = ar[j];
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) ar[j] = ar[i];
	}
	ar[i] = tmp;
	return i;
}

template<class Type>
const Type & SelectK(Type *ar,int left,int right, int k)
{// 56,34,90,23,18,100,89,10,45,78,65 // 2  5  7
	if(left == right && k == 1) return ar[left];
	int i = Partition(ar,left,right);
	int j = i-left + 1;
	//if(k == j) return ar[i];
	if(k <= j) return SelectK(ar,left,i,k);
	else return SelectK(ar,i+1,right,k-j);
}
template<class Type>
const Type & SelectKMin(Type *ar,int n, int k)
{
	if(ar == NULL || n < 1 || k <1 || k > n) 
		exit(1);

	return SelectK(ar,0,n-1,k);
}

void main()
{
	int ar[]={56,34,90,23,18,100,89,10,45,78,65};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int k=1;k<=n;++k)
	{
		int x = SelectKMin(ar,n,k);
		cout<<k<<"==> "<<x<<endl;
	}

}
 /*
#define HEAPSIZE 100
template<class Type>
class MinHeap
{
private:
	Type *heap; // 0// 1 2 3 4 
	int cursize;
	int maxsize;
	
	static void FilterDown(Type *ar,const int start,const int end)
	{
		int i = start, j = 2*i;
		ar[0] = ar[i];
		while(j <= end)
		{
			if(j < end && ar[j] > ar[j+1]) ++j;
			if(ar[0] <= ar[j]) break;
			ar[i] = ar[j];
			i = j;
			j = 2*i;
		}
		ar[i] = ar[0];
	}
	static void FilterUp(Type *ar,const int start,
		                            const int end)
	{
		int j = start,i = j/2;
		ar[0] = ar[j];
		while(i >= end)
		{
			if(ar[i] <= ar[0]) break;
			ar[j] = ar[i];
			j = i;
			i = j/2;
		}
		ar[j] = ar[0];
	}
public:
	MinHeap(int sz = HEAPSIZE)
	{
		cursize = 0;
		maxsize = sz > HEAPSIZE? sz:HEAPSIZE;
		heap = (Type*)malloc(sizeof(Type)*(maxsize+1));
	}
	~MinHeap()
	{
		free(heap);
		heap = NULL;
		cursize = maxsize = 0;
	}

	MinHeap(Type *ar,int n)
	{
		cursize = n;
		maxsize = n>HEAPSIZE? n:HEAPSIZE;
		heap = (Type*)malloc(sizeof(Type)*(maxsize+1));
		for(int i = 0;i<n;++i)
		{
			heap[i+1] = ar[i];
		}
		int pos = cursize/2;
		while(pos > 0)
		{
			FilterDown(heap,pos,cursize);
			--pos;
		}
	}
	int size() const { return cursize;}
	bool empty() const { return size() == 0;}
	bool full() const { return size() == maxsize;}

	bool Remove(Type &x)
	{
		if(empty()) return false;
		x = heap[1];
		heap[1] = heap[cursize--];
		FilterDown(heap,1,cursize);
		return true;
	}

	bool Insert(const Type &x)
	{
		if(full())
			return false;
		heap[++cursize] = x;
		FilterUp(heap,cursize,1);
		return true;
	}
};
void main()
{
	int ar[]={56,34,90,23,18,100,89,10,45,78,65};
	int n = sizeof(ar)/sizeof(ar[0]);
	MinHeap<int> mh;
	for(int i = 0;i<n;++i)
	{
		mh.Insert(ar[i]);
	}

	int x;
	while(mh.Remove(x))
	{
		cout<<x<<" ";
	}
	cout<<endl;
}
//////////////////////////////////


template<class Type>
void Print(Type *ar,int n)
{
	for(int i = 0;i<n;++i)
	{
		cout<<ar[i]<<"  ";
	}
	cout<<endl;
}

template<class Type>
int Partition(Type *ar,int left,int right)
{
	int i = left,j = right;
	Type tmp = ar[i];
	while(i<j)
	{
		while(i<j && ar[j] >= tmp) --j;
		if(i<j) ar[i] = ar[j];
		while(i<j && ar[i] <= tmp) ++i;
		if(i<j) ar[j] = ar[i];
	}
	ar[i] = tmp;
	return i;
}
template<class Type>
int RandPartition(Type *ar,int left,int right)
{
	srand(time(NULL));
	int pos = rand() %( right - left + 1) + left;
	Swap(ar[pos],ar[left]);
	return Partition(ar,left,right);
}
template<class Type>
void QuickPass(Type *ar,int left,int right)
{
	if(left < right)
	{
		int mid = Partition(ar,left,right);
		QuickPass(ar,left,mid-1);
		QuickPass(ar,mid+1,right);
	}
}

template<class Type>
void QuickSort(Type *ar,int n)
{
	QuickPass(ar,0,n-1);
}
void main()
{
	int ar[]={12,78,90,23,34,56,45};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	QuickSort(ar,n);
	Print(ar,n);
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
{// 0 1 2 3 4 5 6  // n 7 s=1
	for(int i = 0;i+2*s <= n;i+=2*s)// i+2*s-1<=n-1
	{
		Merge(sd,si,i,i+s-1,i+2*s-1);
	}
	if(n-1 >= i+s)
	{
		Merge(sd,si,i,i+s-1,n-1);
	}
	else///
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
void main()
{
	int ar[]={12,78,90,23,34,56,45};
	int n = sizeof(ar)/sizeof(ar[0]);
	Print(ar,n);
	MergeSort(ar,n);
	Print(ar,n);
}

template<class Type>
void MergePass(Type *br,Type *ar,int left,int right)
{
	if(left < right)
	{
		int m = ((right - left)>>1) + left;
		// int m = ((right - left+1)>>1) + left;
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

#define SIZE 8
typedef int Array[SIZE][SIZE];

void Print(Array a)
{
	for(int i = 0;i<SIZE;++i)
	{
		for(int j = 0;j<SIZE;++j)
		{
			cout<<setw(3)<<a[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
int titel = 1;

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
	if(dr < tr+s && dc >=tc+s)
	{
		CheseChain(a,tr,tc+s,dr,dc,s);
	}
	else
	{
		a[tr+s-1][tc+s] = t;
		CheseChain(a,tr,tc+s,tr+s-1,tc+s,s);
	}
	if(dr>=tr+s && dc>=tc+s)
	{
		CheseChain(a,tr+s,tc+s,dr,dc,s);
	}
	else
	{
		a[tr+s][tc+s] = t;
		CheseChain(a,tr+s,tc+s,tr+s,tc+s,s);
	}
	if(dr >=tr+s && dc <tc+s)
	{
		CheseChain(a,tr+s,tc,dr,dc,s);
	}
	else
	{
		a[tr+s][tc+s-1] = t;
		CheseChain(a,tr+s,tc,tr+s,tc+s-1,s);
	}

}
void main()
{
	Array a={0};
	int dr,dc;
	cin>>dr>>dc;
	a[dr][dc]=-1;
	Print(a);
	CheseChain(a,0,0,dr,dc,SIZE);
	Print(a);
}

template<class Type>
int FindValue(Type *ar,int n,const Type &x)
{
	if(ar == NULL || n < 1) return -1;
	int left = 0,right =n-1;
	while(left <= right)
	{
		int mid = ((right-left)>>1)+ left;
		if(ar[mid] == x) 
		{
			while(ar[mid-1] == x) 
				mid-=1;
			return mid;
		}
		if(x < ar[mid])
		{
			right = mid-1;
		}else
		{
			left = mid+1;
		}
	}
	return -1;
}
template<class Type>
int Search(Type *ar,int left,int right,const Type &x)
{
	if(left <= right)
	{
		int mid = ((right-left)>>1)+left;
		if(ar[mid] == x)
		{
			while(ar[mid-1] == x) mid-=1;
			return mid;
		}
		if(x < ar[mid] ) return Search(ar,left,mid-1,x);
		else return Search(ar,mid+1,right,x);
	}
	else
	{
		return -1;
	}
}
template<class Type>
int SearchValue(Type *ar,int n,const Type &x)
{
	if(ar == NULL || n < 1) return -1;
	else return Serach(ar,0,n-1,x);
}
void main()
{
	int ar[]={12,23,34,45,45,45,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	int pos = FindValue(ar,n);
	pos = SearchValue(ar,n);
}


int q(int n,int m)
{
	if(n == 1 || m==1) return 1;
	if(m> n) return q(n,n);
	if(m == n) return q(n,n-1)+1;
	else return q(n,m-1)+q(n-m,m);
}
void main()
{
	int n,m;
	cin>>n>>m;
	cout<<q(n,m)<<endl;
}

void Print(int *ar,int *br,int i,int n)
{
	if(i >= n)
	{
		for(int j = 0;j<n;++j)
		{
			cout<<br[j]<<" ";
		}
		for(j = 0;j<n;++j)
		{
			if(br[j] == 1)
			{
				cout<<ar[j]<<" ";
			}
		}
		cout<<endl;
	}else
	{
		Print(ar,br,i+1,n); // left
		//right
		br[i] = 1;
		Print(ar,br,i+1,n);
		br[i] = 0;
	}
}
void main()
{
	int ar[3]={1,2,3};
	int br[3]={0,0,0};

	Print(ar,br,0,3);
}

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
			cout<<ar[i]<<" ";
		}
		cout<<endl;
	}else
	{
		for(int j = k;j<=m;++j)
		{
			Swap(ar[j],ar[k]);
			Perm(ar,k+1,m);
			Swap(ar[j],ar[k]);
		}
	}
}
void main()
{
	int R[]={1,2,3};
	int n = sizeof(R)/sizeof(R[0]);
	Perm(R,0,n-1);

}
*/
