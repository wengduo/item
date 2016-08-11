/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>



void my_strrev(char *arr,int m)
{
	char *p = arr;
	while (*p != 0)
	{
		p++;
	}
	p--;
	int i = 0;
	while ( i<m/2)
	{
		int tmp;
		tmp=*arr;
		*arr++ = *p;
		*p-- = tmp;
		i++;
	}
}

void my_strupr(char *arr)
{
	while (*arr != 0)
	{
		if (*arr >= 'a'&&*arr <= 'z')
		{
			*arr = *arr - 32;
		}
		arr++;
	}
}*/

/*size_t  my_strcmp(char *arr, char*brr)
{
	while ((*arr != 0) || (*brr != 0))
	{
		if (*arr > *brr)
		{
			return 1;
			break;
		}
		else if(*arr<*brr)
		{
			return -1;
			break;
		}
		arr++;
		brr++;
	}
	if (*arr > *brr)
	{
		return 1;
	}
	else if (*arr<*brr)
	{
		return -1;
	}
	return 0;
}

void my_strset(char *arr, char *h)
{
	while (*arr != 0)
	{
		*arr = *h;
		arr++;
	}
}
void my_strncat(char *p, char *m, int k)
{
	while (*p != 0)
	{
		p++;
	}
	int i = 0;
	while (i < k)
	{
		*p++ = *m++;
		i++;
	}
	*p = 0;
}

int my_strchr(char *p, char h)
{
	char *scart = p;
	while (*p != 0)
	{
		if (*p == h)
		{
			return (p - scart);
		}
		p++;
	}
	return 0;

}
int main()
{
	char string[20] = "dsvsda gvaet r";
	char string1[] = "dsvsdagvaet";
	int h = strlen(string);
	int m = strlen(string1);
	char n = '&';
	const char *l = "my";
	char s = 'v';
	//char *p = string;
	//_strrev(string);
	//my_strrev(string,h);
	//my_strupr(string);
	//printf("%d ",my_strcmp(string, string1));
	//printf("%d ", strcmp(string, string1));
	//_strset_s(string, '*');

	//my_strset(string, &n);
	strncpy(string,"me", 2);//C c++ 安全编码规范
	//strncat_s(string, string1, 2);
	//printf("%d", my_strchr(string, s));
	//my_strncat(string, string1, 2);
	printf("%s", string);

	return 0;
}

int *MIN_index(int *p, int m)
{
	
	int min = *p;
	int *index=p;
	int i = 0;
	while (i < m)
	{
		if (min > *p)
		{
			min = *p;
			index = p;
		}
		p++;
		i++;
	}
	return index;
}

int main()
{
	int arr[] = { 3, 2, 1, 4, 5, 6, 7, 8, 9 };
	int h = sizeof(arr) / sizeof(arr[0]);
	printf("0x%p\n", MIN_index(arr, h));
	return 0;
}
void del_space(char *p)
{
	char *s = p;
	while (*s!= 0)
	{
		if ((*s == ' ')||(*s=='	'))
		{
			
			s++;
		}
		else
		{
			*p = *s;
			p++;
			s++;
		}

	}
	*p = 0;
	
}
int main()
{
	char str[] = "dsc	sadc dsd c scc ";
	del_space(str);
	printf("%s",str );
	return 0;
}
size_t my_strncpy(char *p, char *s,int k)
{
	int n = 0;
	while (((*p != 0) || (*s != 0)) && (n<k-1))
		{
			if (*p > *s)
			{
				return 1;
			}
			else if (*p < *s)
			{
				return -1;
			}
			p++;
			s++;
			n++;
		}
		if (*p>*s)
		{
			return 1;
		}
		else if (*p < *s)
		{
			return -1;
		}
		return 0;
}
int main()
{
	char str1[] = "cvwxwcywcvwycvwcvycvhv";
	char str2[] = "cvwxwcywcvwy";
	int n = 13;
	printf("%d\n", my_strncpy(str1,str2,n));



	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct task
{
	int end;
	int punish;
};


void sortend(struct task *p, int n)
{
	int  i = 0;
	int  j = 0;
	int  temp;

	for (i = 0; i<n - 1; i++)
	{
		for (j = 0; j<n - 1 - i; j++)
		{
			if ((p + j)->end >= (p + j + 1)->end)
			{
				temp = (p + j)->end;
				(p + j)->end = (p + j + 1)->end;
				(p + j + 1)->end = temp;
			}
		}
	}
}





int func(struct task *p, int n)
{
	int i = 0;
	int j = 0;

	int index = 0;

	sortend(p, n);

	for (j = 0; j<n - 1; j++)
	{
		if ((p + j)->end == (p + j + 1)->end)
		{
			if ((p + j)->punish <= (p + j + 1)->punish)
			{
				index += (p + j)->punish;
			}
			else
			{
				index += (p + j + 1)->punish;
			}
		}

	}

	return index;
}

int main()
{
	int  n = 0;
	int  i = 0;
	int  index;
	struct task array[10];

	printf("请输入一共有多少任务：\n");
	scanf("%d", &n);
	printf("请分别输入任务的结束时间和处罚：\n");
	for (i = 0; i<n; i++)
	{
		printf("请输入第%d个任务的结束时间和处罚：\n", i + 1);
		scanf("%d %d", &array[i].end, &array[i].punish);
	}
	index = func(array, n);
	printf("经过合理的安排之后，最合理的任何时间表得到的最少处罚为:%d\n", index);

	return 0;
}*/
