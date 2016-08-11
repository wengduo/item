/*
 * =====================================================================================
 *       Filename:  b+.cpp
 *        Version:  1.0
 *        Created:  2016年04月28日 19时22分36秒
 *       Compiler:  gcc
 *         Author:  wengduo (mn), 2292466904@qq.com
 * =====================================================================================
 */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>

#define M 5 
#define LEAFMAX  M      // 5
#define LEAFMIN  (M/2+1) // 3

#define BRCHMAX  (M-1)
#define BRCHMIN  (M/2)
typedef enum{LEAF = 0,BRCH = 1} NodeType;
typedef char KeyType;
typedef struct {}Record;
typedef struct BPNode
{
	int num;
	BPNode *parent;
	NodeType utype;// LEAF BRCH
	KeyType data[M+1];
	union
	{
		struct
		{
			Record *recptr[M+1];
			BPNode *prev,*next;
		};
		BPNode *sub[M+1];
	};
}BPNode;

typedef struct
{
	BPNode *root;
	BPNode *first;
}BPTree;

typedef struct
{
	BPNode *pnode;
	int    index;
	bool   tag;
}Result;

BPNode * _Buynode()
{
	BPNode * s = (BPNode *)malloc(sizeof(BPNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BPNode));
	return s;
}
void _Freenode(BPNode *p)
{
	free(p);
}
BPNode * _BuyLeaf()
{
	BPNode *s = _Buynode();
	s->utype = LEAF;
	return s;
}

void Init_BPTree(BPTree *ptree)
{
	ptree->first = ptree->root = NULL;
}

Result Find(BPNode *ptr,KeyType kx)
{
	Result res={NULL,-1,false};
	int i = ptr->num-1;
	while(i>= 0 && kx < ptr->data[i]) --i;
	res.pnode = ptr;
	res.index = i;
	if(i>=0 && kx == ptr->data[i])
	{
		res.tag = true;
	}else if(i< 0 && ptr->prev != NULL)
	{
		ptr = ptr->prev;
		res.pnode = ptr;
		res.index = ptr->num-1;
	}
	return res;
}

Result FindFirst(BPNode *ptr,KeyType kx)
{
	Result res={NULL,-1,false};
	while(ptr != NULL && 
		   ptr->next != NULL  &&
		    kx > ptr->data[ptr->num-1])
	{
		ptr = ptr->next;
	}
	if(ptr != NULL)
	{
		res = Find(ptr,kx);
	}
	return res;
	
}

Result FindRoot(BPNode *ptr,KeyType kx)
{
	Result res = {NULL,-1,false};
	while(ptr != NULL && ptr->utype != LEAF)
	{
		int i = ptr->num;
		ptr->data[0] = kx;
		while(kx < ptr->data[i]) --i;
		ptr = ptr->sub[i];
	}
	if(ptr != NULL)
	{
		res = Find(ptr,kx);
	}
	return res;
}

void Move_Leaf(BPNode *ptr,BPNode *s)
{
	for(int i = LEAFMIN-1;int j = 0;i < LEAFMAX;++i,++j)
	{
			
	}
}

void Splice_Leaf(BPTree *ptr,BPNode *p)
{
	BPNode *s = _BuyLeaf();
	Move_Leaf(p,s);

}
void Insert_Leaf_Item(BPNode *ptr,int pos,KeyType kx,Record *rec)
{
	for(int i = ptr->num-1; i>pos; --i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->recptr[i+1] = ptr->recptr[i];
	}
	ptr->data[pos+1] = kx;
	ptr->recptr[pos+1] = rec;
	ptr->num+=1;
}
bool Insert(BPTree *ptree,KeyType kx,Record *rec)
{
	if(ptree == NULL) return false;
	if(ptree->first == NULL || ptree->root == NULL)
	{
		BPNode *s  = _BuyLeaf();
		s->data[0] = kx;
		s->recptr[0] = rec;
		s->num = 1;
		s->parent = NULL;
		s->next = s->prev = NULL;
		ptree->first = ptree->root = s;
		return true;
	}
	Result res = FindRoot(ptree->root,kx);
	if(res.pnode == NULL || res.tag ) return false;
	BPNode *ptr = res.pnode;
	int     pos = res.index;
	Insert_Leaf_Item(ptr,pos,kx,rec);
	if(ptr->num > LEAFMAX)
	{
		Splice_Leaf(ptree,ptr);
	}
	return true;
}

void Inorder(BPTree *ptr)
{
	if(ptr == NULL) return;
	BPNode *p = ptr->first;
	while(p != NULL)
	{
		for(int i = 0;i < ptr->first->num;++i)
		{
			std::cout << p->data[i];
		}
		p = p->next;
		std::cout << std::endl; 
	}
}
int main()
{
	BPTree myt;
	KeyType ar[]={"qwertyuiopasdfghjklzxcvbnm"};
	int n = sizeof(ar)/sizeof(ar[0])-1;
	Record *rec = (Record*)0x00008888;

	Init_BPTree(&myt);
	for(int i = 0;i<n;++i)
	{
		std::cout << Insert(&myt,ar[i],rec) << " : ";
		Inorder(&myt);
	}
		
	return 0;
}

