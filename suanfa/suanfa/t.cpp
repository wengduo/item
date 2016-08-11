/*************************************************************************
    > File Name: t.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年08月02日 星期二 21时03分08秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>


const int LinkMax=27;
const int Keymax=25;
enum{BRCH=0,ELEM}NodeType;
typedef struct A{}Recordptr;
typedef struct
{
	char ch[Keymax];
	int cursize;
	
}KeyType;
typedef struct TrieNode
{
	NodeType utype;
	union
	{
		struct 
		{
		  int num;
			TrieNode *Link[LinkMax];
		}brck;
		struct
		{
			KeyType key;
			Recordptr* recptr;
		}elem;
	};
}TrieNode;
static int Insert(TrieNode* &ptr,KeyType x,int &index,Recordptr *rec)
{
	if(NULL==ptr)
	{
		ptr= MakeElem(x,rec);
		return 1;
	}

	if(ptr->utype==ELEM)
	{
		ptr=CreatBrch(ptr,index);
		return Insert(ptr,x,index,rec);
	}
	else if(ptr->utype==BRCH)
	{
		int pos=0;
		if(index<x.cursize)
		{
			pos =x.ch[index]-'a'+1;
		}
		if(ptr->brck.Link[pos]!=NULL)
		{
			//ptr->brck.num-=1;
		}

		return Insert(ptr->brck.Link[pos],x,++index,rec);

	}
}

int Find(KeyType &x)
{
	int i=0;
	current=root;
	int len=x.cursize;
	for(;i<=len;++i)
	{
		int pos=0;
		if(i  < x.cursize )
		{
			pos=x.ch[i]-'a'+1;
		}
		if(current->utype==BRCH)
		{
			current=current->brck.Link[pos];
		}
		if(current->utype==ELEM)
		{
			if(strcmp(x.ch,current->elem.key.ch)==0)
			{
				return 1;
			}
		}	
	}

	current=NULL;
	return 0;
}

int main(int argc,char *argv[])
{
	
	return 0;
}
