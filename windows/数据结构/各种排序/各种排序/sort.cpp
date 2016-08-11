#include"sort.h"
int count = 0;


void kai_kong_jian(char *path, int n)
{
	int *arr = (int *)malloc(sizeof(int)* n);
	assert(arr != NULL);
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 50000 + rand() % 20000 + rand();
	}
	FILE *fw = fopen(path, "wb");
	assert(fw != NULL);
	fwrite(arr, sizeof(int), n, fw);
	fclose(fw);
	free(arr);
}
int *read_array(char *path, int n)
{
	int *arr = (int *)malloc(sizeof(int)* n);
	assert(arr != NULL);
	FILE *fr = fopen(path, "rb");
	fread(arr, sizeof(int), n, fr);
	fclose(fr);
	return arr;
}

void show_file(int *arr, int n)
{
	FILE *f = fopen("f:\\rs.txt", "w");

	for (int i = 0; i<n; i++)
	{
		fprintf(f, "%6d ", arr[i]);
	}
	fclose(f);
}

void swap(int *p1, int *p2)
{
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void show(int *arr, int n)
{
	for (int i = 0; i<n; i++)
	{
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

void exchange_sort(int *arr, int n)
{
	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			count++;
			if (arr[i] > arr[j])
			{
				swap(&arr[i], &arr[j]);
			}
		}
	}
}

void bubble_sort(int *arr, int n)
{
	bool flag = true;

	for (int i = 0; i<n - 1; i++)
	{
		for (int j = 0; j<n - 1 - i; j++)
		{
			count++;
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
		{
			break;
		}
		flag = true;
	}

}

void select_sort(int *arr, int n)
{

	int min = arr[0];
	int min_index = 0;
	for (int j = 0; j<n - 1; j++)
	{
		min = arr[j];
		min_index = j;

		for (int i = j + 1; i<n; i++)
		{                           
			count++;				
			if (arr[i] < min)
			{
				min = arr[i];
				min_index = i;
			}
		}
		if (j != min_index)
		{
			swap(&arr[j], &arr[min_index]);
		}
	}
}

void insert_sort(int *arr, int n)
{
	int tmp;
	int i;
	int j;
	int k;
	for (i = 1; i<n; i++)
	{
		tmp = arr[i];
		for (j = 0; j <= i - 1; j++)
		{
			count++;
			if (arr[j] > tmp)
			{
				break;
			}
		}
		for (k = i - 1; k >= j; k--)
		{
			count++;
			arr[k + 1] = arr[k];
		}
		if (i != j)
		{
			arr[j] = tmp;
		}

	}
}


void insert_sort_ex(int *arr, int n)
{
	int i;
	int j;
	int tmp;
	for (i = 1; i<n; i++)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			count++;
			if (arr[j] > tmp)
			{
				arr[j + 1] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + 1] = tmp;
	}
}


void shell_insert_2(int *arr, int n, int gap)
{
	int i;
	int j;
	int tmp;
	for (i = gap; i<n; i++)
	{
		tmp = arr[i];
		for (j = i - gap; j >= 0; j -= gap)
		{
			count++;
			if (arr[j] > tmp)
			{
				arr[j + gap] = arr[j];
			}
			else
			{
				break;
			}
		}
		arr[j + gap] = tmp;
	}
}


void shell_insert_1(int *arr, int n, int gap)
{
	int i;
	int j;
	int k;
	int tmp;
	for (k = 0; k<gap; k++)
	{
		for (i = gap + k; i<n; i += gap)
		{
			tmp = arr[i];
			for (j = i - gap; j >= 0; j -= gap)
			{
				count++;
				if (arr[j] > tmp)
				{
					arr[j + gap] = arr[j];
				}
				else
				{
					break;
				}
			}
			arr[j + gap] = tmp;
		}
	}
}


void shell_sort(int *arr, int n)
{
	shell_insert_2(arr, n, 5);
	shell_insert_2(arr, n, 3);
	shell_insert_2(arr, n, 1);
}


int partition1(int *arr, int low, int high)//优化后的快排
{
	int tmp = arr[low];
	while (low < high)
	{
		while (arr[high] >= tmp && low < high)
		{
			count++;
			high--;
		}
		arr[low] = arr[high];
		if (low < high)
		{
			low++;
		}
		while (arr[low] <= tmp && low < high)
		{
			count++;
			low++;
		}
		arr[high] = arr[low];
		if (low < high)
		{
			high--;
		}
	}
	arr[low] = tmp;
	return low;
}


int partition2(int *arr, int low, int high)
{
	int tmp = arr[low];
	int flag = 1;
	while (low < high)
	{
		if (flag == 1)
		{
			if (tmp > arr[high])
			{
				arr[low] = arr[high];
				flag = 0;
			}
			else
			{
				high--;
			}
		}
		if (flag == 0)
		{
			if (tmp < arr[low])
			{
				arr[high] = arr[low];
				flag = 1;
			}
			else
			{
				low++;
			}
		}
		count++;
	}
	arr[low] = tmp;
	return low;
}

void quick(int *arr, int low, int high)
{
	if (low < high)
	{
		int mid = partition1(arr, low, high);
		quick(arr, low, mid - 1);
		quick(arr, mid + 1, high);
	}
}
void digui_quick_sort(int *arr, int n)
{
	quick(arr, 0, n - 1);
}




void xuhuan_quick_sort_shen(int *arr, int low, int high)
{
	int *brr = (int *)malloc( sizeof(int) * (high+1) * (high+1));
	assert(brr != NULL && "空间不够\n");
	int top = 0;
	brr[top++] = low;
	brr[top++] = high;
	int L = 0;
	int H = 0;
	while (top != 0)
	{
		H = brr[--top];
		L = brr[--top];
		int mid = partition1(arr, L, H);
		if (L < mid - 1)
		{
			brr[top++] = L;
			brr[top++] = mid - 1;
		}
		if (H > mid + 1)
		{
			brr[top++] = mid + 1;
			brr[top++] = H;
		}
	}
	free(brr);
}
void xuhuan_quick_sort1(int *arr, int n)
{
	xuhuan_quick_sort_shen(arr, 0, n - 1);
}



void xuhuan_quick_sort_lian(int *arr, int low, int high)
{
	NODE p;
	list_init(&p);
	list_push(&p, high);
	list_push(&p, low);
	while (!list_kong(&p))
	{
		list_pop(&p,&low);
		int p1 = low;
		list_pop(&p, &high);
		int p2 = high;
		int tmp = arr[low];
		while (low < high)
		{
			while (arr[high] >= tmp && low < high)
			{
				count++;
				high--;
			}
			arr[low] = arr[high];
			if (low < high)
			{
				low++;
			}
			while (arr[low] <= tmp && low < high)
			{
				count++;
				low++;
			}
			arr[high] = arr[low];
			if (low < high)
			{
				high--;
			}
		}
		arr[low] = tmp;
		if (p1 < p2)
		{
			list_push(&p, p2);
			list_push(&p, low + 1);
			list_push(&p, low - 1);
			list_push(&p, p1);
		}
	}
	list_destory(&p);
}
void xuhuan_quick_sort2(int *arr, int n)
{
	xuhuan_quick_sort_lian(arr, 0, n - 1);
}



void heap_sort1(int *arr, int n,int start)
{
	int tmp = arr[start];
	int end = n;
	int i;
	for (i = 2 * start + 1; i <= end; i = i * 2 + 1)
	{
		count++;
		if (arr[i] < arr[i+1] && i+1 <= end)
		{
			i++;
		}
		if (arr[i] > tmp)
		{
			arr[start] = arr[i];
			start = i;
		}
		
	}
	arr[start] = tmp;
}

void heap_sort(int *arr, int n)
{
	int end = n - 1;
	for (int start = n / 2 - 1; start >= 0; start--)
	{
		heap_sort1(arr, end, start);
	}
	for (int i = end; i > 0; i--)
	{
		swap(&arr[0], &arr[end]);
		end--;
		heap_sort1(arr, end, 0);
	}
}


//归并排序
void gui_bing1(int *arr,int n,int gap)
{
	int H1 = 0;
	int L1 = H1 + gap - 1;
	int H2 = L1 + 1;
	int L2 = H2 + gap - 1 > n - 1 ? n - 1 : H2 + gap - 1;
	int *brr = (int *)malloc(sizeof(int)*n);
	int k = 0;
	while (H1 <= n - 1)
	{
		while (H1 <= L1 && H2 <= L2)
		{
			if (arr[H1] <= arr[H2])
			{
				brr[k++] = arr[H1++];
			}
			else
			{
				brr[k++] = arr[H2++];
			}
		}
		while (H1 <= L1)
		{
			brr[k++] = arr[H1++];
		}
		while (H2 <= L2)
		{
			brr[k++] = arr[H2++];
		}
		H1 = L2 + 1;
		L1 = H1 + gap - 1;
		H2 = L1 + 1;
		L2 = H2 + gap - 1 > n - 1 ? n - 1 : H2 + gap - 1;
	}
	while (H1 <= n - 1)
	{
		brr[k++] = arr[H1++];
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = brr[i];
	}
	free(brr);
}
void gui_bing(int *arr, int n)
{
	for (int i = 1; i < n; i *= 2)
	{
		gui_bing1(arr, n, i);
		//show_file(arr, n);
	}
}




void di_gui_bing1(int *arr, int n, int gap)
{
	if (gap > n)
	{
		return;
	}
	int H1 = 0;
	int L1 = H1 + gap - 1;
	int H2 = L1 + 1;
	int L2 = H2 + gap - 1 > n - 1 ? n - 1 : H2 + gap - 1;
	int *brr = (int *)malloc(sizeof(int)*n);
	int k = 0;
	while (H1 <= n - 1)
	{
		while (H1 <= L1 && H2 <= L2)
		{
			if (arr[H1] <= arr[H2])
			{
				brr[k++] = arr[H1++];
			}
			else
			{
				brr[k++] = arr[H2++];
			}
		}
		while (H1 <= L1)
		{
			brr[k++] = arr[H1++];
		}
		while (H2 <= L2)
		{
			brr[k++] = arr[H2++];
		}
		H1 = L2 + 1;
		L1 = H1 + gap - 1;
		H2 = L1 + 1;
		L2 = H2 + gap - 1 > n - 1 ? n - 1 : H2 + gap - 1;
	}
	while (H1 <= n - 1)
	{
		brr[k++] = arr[H1++];
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = brr[i];
	}
	show(arr, n);
	free(brr);
	di_gui_bing1(arr,n, 2 * gap);
}

void di_gui_bing(int *arr, int n)
{
	di_gui_bing1(arr, n, 1);
}


//外排序
void chu_pai(char *path, int n)
{
	FILE *fr = fopen(path, "rb");
	FILE *fw = fopen("f://1.txt", "wb");
	int *arr = (int *)malloc(sizeof(int)* n);
	assert(fr != NULL);
	assert(fw != NULL);
	assert(arr != NULL);
	int rs;
	while ((rs = fread(arr, sizeof(int), n, fr)) > 0)
	{
		insert_sort_ex(arr, rs);
		fwrite(arr, sizeof(int), rs, fw);
	}
	fclose(fr);
	fclose(fw);
	free(arr);
	remove(path);
	rename("f://1.txt", path);
}

void pai_xu(char *path, int gap, int n, int m)
{

	FILE *fr = fopen(path, "rb");
	FILE *fw = fopen("F://1.txt", "wb");
	int *arr = (int *)malloc(sizeof(int)* m);
	int *brr = (int *)malloc(sizeof(int)* m);
	int *crr = (int *)malloc(sizeof(int)* m);
	assert(fr != NULL);
	assert(fw != NULL);
	assert(arr != NULL);
	assert(brr != NULL);
	assert(crr != NULL);
	fread(arr, sizeof(int), m, fr);
	fseek(fr, gap * 4, SEEK_SET);
	fread(brr, sizeof(int), m, fr);
	int L1 = 0;
	int H1 = L1 + gap - 1;
	int L2 = H1 + 1;
	int H2 = L2 + gap - 1 > n - 1 ? n - 1 : L2 + gap - 1;
	int i;
	int j;
	int k;
	int y[1];
	while (L1 < n - 1)
	{
		i = 0;
		j = 0;
		k = 0;
		while (L1 <= H1 && L2 <= H2)
		{
			if (arr[i] <= brr[j])
			{
				crr[k++] = arr[i++];
				L1++;
			}
			else
			{
				crr[k++] = brr[j++];
				L2++;
			}

			if (i == m)
			{
				fseek(fr, L1 * 4, SEEK_SET);
				fread(arr, sizeof(int), 5, fr);
				i = 0;
			}
			if (j == m)
			{
				fseek(fr, L2 * 4, SEEK_SET);
				fread(brr, sizeof(int), 5, fr);
				j = 0;
			}
			if (k == m)
			{
				fwrite(crr, sizeof(int), 5, fw);
				k = 0;
			}
		}
		if (k > 0 && k < m)
		{
			fwrite(crr, sizeof(int), k, fw);
		}
		while (L1 <= H1)
		{
			fseek(fr, L1 * 4, SEEK_SET);
			fread(y, sizeof(int), 1, fr);
			fwrite(y, sizeof(int), 1, fw);
			L1++;
		}
		while (L2 <= H2)
		{
			fseek(fr, L2 * 4, SEEK_SET);
			fread(y, sizeof(int), 1, fr);
			fwrite(y, sizeof(int), 1, fw);
			L2++;
		}
		L1 = H2 + 1;
		H1 = L1 + gap - 1;
		L2 = H1 + 1;
		H2 = L2 + gap - 1 > n - 1 ? n - 1 : L2 + gap - 1;
		fseek(fr, L1 * 4, SEEK_SET);
		fread(arr, sizeof(int), m, fr);
		fseek(fr, L2 * 4, SEEK_SET);
		fread(brr, sizeof(int), m, fr);
	}
	while (L1 <= n - 1)
	{
		fseek(fr, L1 * 4, SEEK_SET);
		fwrite(fr, sizeof(int), 1, fw);
		L1++;
	}
	fclose(fr);
	fclose(fw);
	free(arr);
	free(brr);
	free(crr);
	remove(path);
	rename("f://1.txt", path);
}

void pai_xu1(char *path, int n, int m)
{
	for (int i = 10; i < n; i *= 2)
	{
		pai_xu(path, i, n, m);
	}
}

void wai_pai(char *path, int n)
{
	//creat_shu(path, n);
	chu_pai(path, 10);
	pai_xu1(path, n, 5);
}