#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<io.h>
#include<vld.h>
#include <sys/stat.h>
//#include <unistd.h>
/*struct _finddata_t
{
	unsigned attrib;
	time_t time_create;
	time_t time_access;
	time_t time_write;
	_fsize_t size;
	char name[_MAX_FNAME];
}finddata;*/
char buff3[10][60] = { 0 };   //存放目录
int i = 0;
void func(char **arr2, int *brr2, int h2, char *p2)
{
	FILE *fr = fopen(p2, "r");
	assert(fr != NULL);
	char buff[60];
	while (fgets(buff, 60, fr) != NULL)
	{
		char **s = (char **)malloc(sizeof(char *)* 60);
		if ((*(s + 0) = strtok(buff, "	 \n\t/*(")) != NULL)
		{
			int i = 1;
			while ((*(s + i) = strtok(NULL, "	 \n\t/*(")) != NULL)
			{
				i++;
			}
			for (int j = 0; j < i; j++)
			{
				for (int k = 0; k < h2; k++)
				{
					if (strcmp(*(arr2 + k), *(s + j)) == 0)
					{
						brr2[k]++;
					}
				}

			}
		}
		free(s);
	}
	fclose(fr);
}
char *my_serent(char *p, char *s)
{
	char *f = p;
	int h = strlen(p) - 1;
	int k = strlen(s);
	while (h--)
	{
		*p++;
	}
	while (*p++ = *s++);
	p = f;
	return p;
}
char *my_delete(char *p, char *s)
{
	char *f = p;
	int k = strlen(p)-strlen(s)+1;
	while (k--)
	{
		*p++;
	}
	*p = 0;
	p = f;
	return p;
}

char *my_find(char *p,char **arr1,int *brr1,int h1)
{
	char buff[5] = "\\*";
	char buff1[5] = "..";
	int handle;
	struct _finddata_t finddata;
	handle = _findfirst(p, &finddata);
	if (-1 == handle)
	{
		return 0;
	}	                                        
	while (!_findnext(handle, &finddata))
	{
		if (*finddata.name != *buff1)
		{
			char buff2[300];
			my_serent(p, finddata.name);
			if (fopen(p, "rb") == NULL)
			{
				strcpy(buff3[i++], finddata.name);
				strcat(p, buff);
				my_find(p,arr1,brr1,h1);
				strcat(buff3[--i], "**");
				my_delete(p, buff3[i]);
			}
			else
			{
				strcpy(buff2, finddata.name);
				if (strlen(buff2) != strlen(strtok(finddata.name, ".\n")))
				{
					if (strcmp(strtok(NULL, ".\n"), "cpp") == 0)
					{
						printf("%s\n", p);
						func(arr1, brr1, h1, p);
						my_delete(p, buff2);
					}
					else
					{
						my_delete(p, buff2);
					}
				}
				else
				{
					my_delete(p, buff2);
				}
			}
		}
	}
	_findclose(handle);
}

int main()
{
	char *arr[] = {
		"int",
		"if",
		"else",
		"case",
		"float",
		"double",
		"char",
		"for",
		"while",
		"switch",
		"do",
		"long",
		"short"
	};
	char to_search[300] = "f:\\c程序\\*";
	int h = sizeof(arr) / sizeof(arr[0]);
	int brr[13] = { 0 };
	char *p = my_find(to_search,arr,brr,h);
	for (int i = 0; i < h; i++)
	{
		printf("%d\n", brr[i]);
	}
	return 0;
}
/////////////////////////////////////////////////////////
//大数相加
/*void my_duiqi(char *p, char *s,char *f)
{
	char *tmp = p;
	char *tmp1 = s;
	_strrev(tmp);
	_strrev(tmp1);
	while (*p || *s)
	{
		if (*p == 0)
		{
			*p = '0';
			while(*s)
			{
				*p++='0';
				s++;
			}
			*p = '0';
			*s = '0';
		}
		if (*s == 0)
		{
			*s = '0';
			while (*p)
			{
				*s++ = '0';
				p++;
			}
			*p = '0';
			*s = '0';
		}
		p++;
		s++;
	}
	while (*tmp++)
	{
		*f++ = '0';
	}
}
char *my_add(char *p, char *s, char *f)
{
	char *tmp = f;
	my_duiqi(p, s,f);
	while (*p)
	{
		int i = *p++ - '0';
		int j = *s++ - '0';
		int k = *f - '0';
		int h = i + j + k;
		if (h > 9)
		{
			*f++= h - 10 + '0';
			*f = '1';
		}
		else
		{
			*f++ = h + '0';
		}
	}
	_strrev(tmp);
	return tmp;
}
int main()
{
	char buff1[20] = "9123456789";
	char buff2[20] = "12999991000";
	char buff3[100] = { 0 };
	char *p=my_add(buff1, buff2,buff3);
	printf("%s\n", p);
	return 0;
}
///////////////////////////////////////////////
*/