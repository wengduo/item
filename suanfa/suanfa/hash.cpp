/*************************************************************************
    > File Name: 1.c
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月07日 星期六 19时04分05秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#define SIZE 14

typedef int Type;

typedef struct {} Record;

typedef struct ElemType
{
	Type data;
	Record *recoptr;
}ElemType;

typedef struct _HashNode
{
	struct _HashNode *next;
	ElemType key;
}HashNode,*PHashNode;

typedef struct HashTable
{
	PHashNode hash_table[SIZE];
	int course;
}HashTable;

HashNode *_BuyNode()
{
	HashNode *tmp = (HashNode *)malloc(sizeof(HashNode));
	tmp->next = NULL;
	return tmp;
}

bool Is_Exist(HashNode *p,Type x)
{
	bool res = false;
	while(p != NULL)
	{
		if(p->key.data == x)
		{
			res = true;
			break;
		}
		p = p->next;
	}
	return res;
}

bool Serach_Value(HashTable *pt,Type x)
{
	int k = x%13;
	return Is_Exist(pt->hash_table[k],x);
}

bool Insert_Hash(HashTable *pt,Type x)
{
	bool res = false;
	int k = x%13;
	if(pt->hash_table[k] == NULL)
	{
		pt->hash_table[k] = _BuyNode();
		pt->hash_table[k]->key.data = x;
		pt->course++;
		res = true;
	}
	else
	{
		if(!Is_Exist(pt->hash_table[k],x))
		{
			HashNode *p = _BuyNode();
			p->key.data = x;
			p->next = pt->hash_table[k];
			pt->hash_table[k] = p;
			res = true;
		}
	}
	return res;
}

int main(int argc,char *argv[])
{
	HashTable root;
	int j = 0;
	while(j < SIZE)
	{
		root.hash_table[j++] = NULL;
	}
	root.course = 0;
	int ar[] = {12,23,34,45,56,67,78,89};
	int n = sizeof(ar)/sizeof(ar[0]);
	int i = 0;
	printf("%d\n",n);
	while(i < n)
	{
		printf("%d:%d\n",Insert_Hash(&root,ar[i]),ar[i]);
		i++;
	}
	Type m;
	while(1)
	{
		std::cin >> m;
		if(m == -1) break;
		std::cout << Serach_Value(&root,m) << std::endl;
	}
	return 0;
}
