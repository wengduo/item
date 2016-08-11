#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include <windows.h>



void swap(int *p1, int *p2)
{
	int tmp;
	tmp = *p1;
	*p1= *p2;
	*p2 = tmp;
}

bool rand_data(int n=1000002)
{
	int *p = (int *)malloc(sizeof(int)*n);
	assert(p != NULL);
	int *tmp = p;

	srand(time(NULL));

	for (int i=0;i<n;i++)
	{
		*p = rand();
		p++;
	}

	FILE *fw = fopen("c:\\sort_100w.dat","wb");
	assert(fw != NULL);

	fwrite(tmp,sizeof(int),n-2,fw);
	fclose(fw);
	free(tmp);

	return true;
}


int *read_data()
{
	int n = 1000000;
	FILE *fr = fopen("c:\\sort_100w.dat","rb");
	assert(fr != NULL);

	int *p = (int *)malloc(sizeof(int)*n);
	assert(p != NULL);
	fread(p,sizeof(int),n,fr);

	return p;
}

void show(int *arr,int len)
{
	for (int i=0;i<len;i++)
	{
		printf("%d\n",arr[i]);
	}
}


void exchange_sort(int *arr,int len)
{
	for (int i=0;i<len;i++)
	{
		for (int j=i+1;j<len;j++)
		{
			if (arr[i] > arr[j])
			{
				swap(&arr[i],&arr[j]);
			}
		}
	}
}

void bubble_sort(int *arr,int len)
{

	bool flag = true;

	for (int i=0;i<len;i++)
	{
		flag = true;

		for (int j=0;j<len-1-i;j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap(&arr[j],&arr[j+1]);
				flag = false;
			}
		}

		if (flag == true)
		{
			break;
		}
	}
}


void select_sort(int *arr, int len)
{
	int min = 0;

	for (int i=0;i<len;i++)
	{
		min = i;
		for(int j=i+1;j<len;j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}
		if (i != min)
		{
			swap(&arr[i], &arr[min]);
		}
	}
}



void insert_sort(int *arr, int len)
{
	int i = 0;
	int j = 0;
	int tmp = arr[0];
	int k = 0;

	for (i=1;i<len;i++)    
	{
		tmp = arr[i];
		for(j=i-1;j>=0;j--)
		{
			if (arr[j] > tmp)
			{
				arr[j+1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j+1] = tmp;
	}
}


void shell_insert(int *arr, int length, int gap)
{
	int i = 0;
	int j = 0;
	int tmp = arr[0];

	for (i=gap; i<length; i++)
	{
		tmp = arr[i];//
		for (j=i-gap;j>=0 ;j-=gap)
		{
			if (tmp < arr[j])
			{
				arr[j+gap] = arr[j];
			}
			else
			{
				break;
			}

		}
		arr[j+gap] = tmp;
	}
}

void shell_sort(int *arr, int length)
{
	for (int i = 19;i>=1; i=i/3+1)
	{
		shell_insert(arr,length,i);
		if (i == 1)
		{
			break;
		}
	}
}


int partition(int *arr,int low,int high)
{
	int tmp = arr[low];//提取基准数据

	while(low < high)
	{
		//从右向左跑
		while(low < high && arr[high] >= tmp)
		{
			high--;
		}
		swap(&arr[low],&arr[high]);

		//从左向右跑
		while(low < high && arr[low] <= tmp)//???
		{
			low++;
		}
		swap(&arr[low],&arr[high]);
	}
	arr[low] = tmp; //???

	return low;
}

void quick_sort(int *arr,int low, int high)
{
	if (low < high)
	{
		int base = partition(arr,low,high);

		quick_sort(arr,low,base-1);
		quick_sort(arr,base+1,high);
	}
}

void q_sort(int *arr,int len)
{
	quick_sort(arr,0, len-1);
}






void re_quick_sort(int *arr, int length)
{
	int *stack = (int *)malloc(sizeof(int) * length *length);
	assert(stack != NULL);
	int top = 0;

	int base = 0;

	int low = 0;
	int high = length-1;

	stack[top++] = low;
	stack[top++] = high;


	while(top > 0)
	{
		high = stack[--top];
		low  = stack[--top];
		base = partition(arr,low,high);
		if (low < base-1)
		{
			stack[top++] = low;
			stack[top++] = base-1;
		}
		if (base+1 < high)
		{
			stack[top++] = base+1;
			stack[top++] = high;
		}
	}

	free(stack);
}


void heap_adjust(int *arr,int start, int end)
{
	//tmp 根的值
	int tmp = arr[start];
	//i 左孩子下标
	for (int i=2*start+1; i<=end; i=i*2+1)
	{
		if (i+1<=end && arr[i]<arr[i+1])
		{
			i++;
		}
		//i停留在左右孩子中较大位置的下标

		if(tmp < arr[i])
		{
			arr[start] = arr[i];
			start = i;
		}
	}
	//
	arr[start] = tmp;
}


void heap_sort(int *arr,int length)
{
	//1.调整成大根堆
	for(int i=(length-1-1)/2;i>=0;i--)
	{
		heap_adjust(arr,i,length-1);//????   (N）log2N
	}
	int len = length-1;


	while(len > 0)
	{
		swap(&arr[0],&arr[len]);
		len--;
		heap_adjust(arr,0,len);//  root 1
		
	}
}


void merge(int *arr, int len, int gap)
{
	int L1 = 0;
	int H1 = L1+gap-1;
	int L2 = H1+1;
	int H2 = (L2+gap-1<len-1) ? (L2+gap-1) : (len-1);

	int *brr = (int *)malloc(sizeof(int) * len);
	assert(brr != NULL);

	int i = 0;

	while(L2 <= len-1)
	{
		while(L1<=H1 && L2<=H2)
		{
			arr[L1]<arr[L2] ? brr[i++] = arr[L1++] : brr[i++] = arr[L2++];
		}
		while(L1<=H1)
		{
			brr[i++] = arr[L1++];
		}
		while(L2<=H2)
		{
			brr[i++] = arr[L2++];
		}

		L1 = L1+gap;
		L2 = L2+gap;
		H1 = L2-1;
		H2 = (L2+gap-1 < len-1) ? (L2+gap-1) : (len-1);
	}

	while(L1<=len-1)
	{
		brr[i++] = arr[L1++];
	}

	for (int j=0;j<len;j++)
	{
		arr[j] = brr[j];
	}
	free(brr);   //O(2N)
}


void merge_sort(int *arr,int len)
{
	for (int i=1;i<len;i*=2)  //O(N*log2N)
	{
		merge(arr,len,i);
	}
}

void mergex(int *arr, int start, int mid, int end)
{
	int *brr = (int *)malloc(sizeof(int) * (end-start+1));
	assert(brr != NULL);

	int L1 = start;
	int H1 = mid;
	int L2 = mid+1;
	int H2 = end;
	int i = 0;

	while(L1<=H1 && L2<=H2)
	{
		if (arr[L1] < arr[L2])
		{
			brr[i++] = arr[L1++];
		}
		else
		{
			brr[i++] = arr[L2++];
		}
	}
	while(L1<=H1)
	{
		brr[i++] = arr[L1++];
	}
	while(L2<=H2)
	{
		brr[i++] = arr[L2++];
	}


	for(int j=start,i=0;j<=end;j++,i++)
	{
		arr[j] = brr[i];
	}
	free(brr);
}


void re_merge_sort(int *arr,int start, int end)
{
	int mid;

	if (start < end)
	{	
		mid = (start+end)/2;

		re_merge_sort(arr,start,mid);
		re_merge_sort(arr,mid+1,end);
		mergex(arr,start,mid,end);// 2 4 8 16 N
	}
}

void m_sort(int *arr, int len)
{
	re_merge_sort(arr,0, len-1);
}

#define MAX_SORT_SIZE 1000000

int main()
{
	int *arr = read_data();

	clock_t time1 = clock();
	
	int brr[10] = {3,5,8,2,3,5,6,7,8};
	//shell_sort(arr,1000000);
	//heap_sort(arr,1000000);
	m_sort(arr, 10000);











	clock_t time2 = clock();
	printf("%d\n",time2-time1);
	free(arr);
	return 0;
}