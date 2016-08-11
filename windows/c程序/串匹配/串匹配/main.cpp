#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>


int *get_next(char *s,int *next)
{
	next[0] = -1;
	int i = 0;
	int j = -1;
	while (i < strlen(s))
	{
		if ((j == -1) || s[i] == s[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
	return next;
}

int index_kmp(char *p,char *s,int pos)
{
	int i = 0;
	int j = 0;
	int *next = (int *)malloc(sizeof(int)*strlen(s));
	assert(next != NULL);
	get_next(s,next);
	for (int k = 0; k < strlen(s); k++)
	{
		printf("%d ", next[k]);
	}
	while (i <= strlen(p))
	{
		if (j == -1|| p[i] == s[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
		if ((j+1) >= (strlen(s)+1))
		{
			printf("i:%d ", i);
			printf("j:%d ", j);
			return (i - j);
		}
	}
	printf("%d\n", strlen(s));
	return -1;
}
int main()
{
	char buff[] = "ababbbbabbaababaaababbb";
	char buff1[] = "abaaaba";
	//index_kmp(buff, buff1, 0);
	printf("%d\n",index_kmp(buff, buff1,0));
	return 0;
}