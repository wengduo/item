
/*************************************************************************
    > File Name: sort.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月27日 星期日 18时10分15秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>
typedef int Type;
typedef struct _BstNode
{
	Type data;
	struct _BstNode *parent;
	struct _BstNode *lchild;
	struct _BstNode *rchild;
}BstNode;
BstNode *_BuyNode()
{
	BstNode *tmp = (BstNode *)malloc(sizeof(BstNode));
	tmp->lchild = NULL;
	tmp->rchild = NULL;
	return tmp;
}

void _FreeNode(BstNode *ptr)
{
	free(ptr);
}

bool Insert(Type &str,BstNode *&ptr,BstNode *pa)
{
	bool flag = false;
	if(ptr == NULL)
	{
		ptr = _BuyNode();
		ptr->data = str;
		ptr->parent = pa;
		ptr->lchild = NULL;
		ptr->rchild = NULL;
		flag = true;
	}
	if(str > ptr->data)
	{
		flag = Insert(str,ptr->rchild,ptr);
	}
	else if(str < ptr->data)
	{
		flag = Insert(str,ptr->lchild,ptr);
	}
	return flag;
}

bool InsertBstNode(Type &str,BstNode *&root)
{
	bool flag = false;
	flag = Insert(str,root,NULL);	
	return flag;
}

void InOrderTree(BstNode *p)
{
	if(NULL != p)
	{
		InOrderTree(p->lchild);
		std::cout << p->data << " ";
		InOrderTree(p->rchild);
	}
}

BstNode *FindValue(BstNode *p,Type &x)
{
	BstNode *s = NULL;
	if(p == NULL) return s;
	if(p->data > x)
	{
		s = FindValue(p->lchild,x);
	}
	else if(p->data < x)
	{
		s = FindValue(p->rchild,x);
	}
	else
	{
		s = p;
	}
	return s;
}

BstNode *Next(BstNode *p)
{
	while(p->lchild != NULL)
	{
		p = p->lchild;
	}
	return p;
}

bool Delete(BstNode *&p,BstNode *s)
{
	BstNode *ptr = s;
	if(s->lchild != NULL && s->rchild != NULL)
	{
		s = Next(s->rchild);
		ptr->data = s->data;
		ptr = s->parent;
	}
	BstNode *child = s->lchild != NULL ? s->lchild :s->rchild;
	if(child != NULL)
	{
		child->parent = s->parent;
	}
	if(s->parent != NULL)
	{
		ptr = s->parent->lchild == s ? s->parent->lchild : s->parent->rchild;
		ptr = child;
	}
	else
	{
		p = child;
	}
	_FreeNode(s);
	return true;
}

bool DeleteTree(BstNode *&p,Type &x)
{
	bool flag = false;
	if(NULL == p) return flag;
	else
	{
		BstNode *s = FindValue(p,x);
		if(s == NULL) return flag;
		return Delete(p,s);	
	}
}																														//		10
																														//	8    16
																													//  5   12   19
																													//    7
int main(int argc,char *argv[])
{
	int a[] = {10,8,16,5,7,12,19};
	BstNode *root = NULL;
	int h = sizeof(a)/sizeof(a[0]);
	for(int i = 0;i < h;++i)
	{
		if(!InsertBstNode(a[i],root))
		{
			break;
		}
	}
	int x;
	while(1)
	{
		InOrderTree(root);
		std::cout << std::endl;
		std::cin >> x;
		if(x == -1) break;
		printf("%d\n",DeleteTree(root,x));
	}
  return 0;
}

