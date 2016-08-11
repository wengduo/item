
/*************************************************************************
    > File Name: 6.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月11日 星期五 17时45分48秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#define End '#' 
typedef char Type;
typedef enum{Link = 0,Thread = 1}Tag;
struct BtNode{
	BtNode *lchild;
	Tag ltags;
	BtNode *rchild;
	Tag rtags;
	Type data;
};
BtNode *pre = NULL;
BtNode *_BuyNOde()
{
	BtNode *tmp = (BtNode *)malloc(sizeof(BtNode));
	return tmp;
}
BtNode *CreatedTree(const char *&str)
{
	BtNode *root = NULL;
	if(*str != End)
	{
		root = _BuyNOde();
		root->data = *str;
		root->ltags = Link;
		root->rtags = Link;
		root->lchild = CreatedTree(++str);
		root->rchild = CreatedTree(++str);
	}
	return root;
}

void ThreadPreOrder1(BtNode *p)
{
	if(NULL != p)
	{
		if(NULL == p->lchild)
		{
			p->ltags = Thread;
			p->lchild = pre;
		}
		if(NULL != pre && NULL == pre->rchild)
		{
			pre->rtags = Thread;
			pre->rchild = p;
		}
		pre = p;
		if(Link == p->ltags)
			ThreadPreOrder1(p->lchild);
		if(Link == p->rtags)
		ThreadPreOrder1(p->rchild);
	}
	
}

void ThreadInOrder1(BtNode *p)
{
	if(NULL != p)
	{
		ThreadInOrder1(p->lchild);
		if(NULL == p->lchild)
		{
			p->ltags = Thread;
			p->lchild = pre;
		}
		if(NULL != pre && NULL == pre->rchild)
		{
			pre->rtags = Thread;
			pre->rchild = p;
		}
		pre = p;
		ThreadInOrder1(p->rchild);
	}
}
BtNode *ThreadInOrder(BtNode *root)
{
	if(NULL == root) return NULL;
	BtNode *ptr = _BuyNOde();
	ptr->lchild = root;
	ptr->ltags = Link;
	pre = ptr;
	ThreadInOrder1(root);
	ptr->rchild = pre;
	pre->rtags = Thread;
	pre->rchild = ptr;
	return ptr;
}

BtNode *ThreadPreOrder(BtNode *root)
{
	if(NULL == root) return NULL;
	BtNode *ptr = _BuyNOde();
	ptr->lchild = root;
	ptr->ltags = Link;
	ptr->rtags = Thread;
	pre = ptr;
	ThreadPreOrder1(root);
	ptr->rchild = pre;
	pre->rtags = Thread;
	pre->rchild = ptr;
	return ptr;
}

void ThreadPostOrder1(BtNode *p)
{
	if(NULL != p)
	{
		ThreadPreOrder1(p->lchild);
		ThreadPreOrder1(p->rchild);
		if(NULL == p->lchild)
		{
			p->ltags = Thread;
			p->lchild = pre;
		}
		if(NULL != pre && NULL == pre->rchild)
		{
			pre->rtags = Thread;
			pre->rchild = p;
		}
		pre = p;
	}
}

BtNode *ThreadPostOrder(BtNode *root)
{
	if(NULL == root) return NULL;
	BtNode *ptr = _BuyNOde();
	ptr->lchild = root;
	ptr->ltags = Link;
	ptr->rtags = Thread;
	ptr->rchild = NULL;
	pre = ptr;
	ThreadPostOrder1(root);
	ptr->rchild = pre;
	pre->rtags = Thread;
	pre->rchild = ptr;
	return ptr;
}

void pre_order_threadtree(BtNode *ptr)
{
	if(ptr == NULL) return;
	BtNode *p = ptr->lchild;
	while(ptr != p)
	{
		std::cout << p->data << " ";
		if(Link == p->ltags)
			p = p->lchild;
		else
			p = p->rchild;
	}
}

void in_order_threadtree(BtNode *ptr)
{
	if(ptr == NULL) return;
	BtNode *p = ptr->lchild;
	while(ptr != p)
	{
		while(p->ltags == Link)
		{
			p = p->lchild;
		}
		std::cout << p->data << " ";
		while(p->rtags == Thread && p->rchild != ptr)
		{
			p = p->rchild;
			std::cout << p->data << " ";
		}
		p = p->rchild;
	}
}

BtNode *parent(BtNode *ptr,BtNode *par)
{
	BtNode *ps = ptr;
	if(ps->lchild == par)
		return ps;
	else
	{
		ps = ps->lchild;
		while(ps->lchild != par && ps->rchild != par)
		{
			if(Link == ps->rtags)
				ps = ps->rchild;
			else
				ps = ps->lchild;
		}
		return ps;
	}
}

void post_order_threadtree(BtNode *ptr)
{
	if(ptr == NULL) return;
	BtNode *par;
	BtNode *p = ptr->lchild;
	while(1)
	{
		while(Link == p->ltags)
			p = p->lchild;
		if(Link == p->rtags)
			p = p->rchild;
		else
			break;
	}
	while(ptr != p)
	{
		std::cout << p->data << " ";
		par = parent(ptr,p);
		if(par == ptr)
			p = ptr;
		else if(p == par->rchild || Thread == par->rtags)
			p = par;
		else
		{
			while(par->rtags == Link)
		  {
				par = par->rchild;
				while(par->ltags == Link)
				{
					par = par->lchild;
				}
			}
			p = par;
		}
	}
}

int main(int argc,char *argv[])
{
	const char *str = "ABC##DE##F##G#H##";
	BtNode *root = CreatedTree(str);
	//BtNode *PostOrder = ThreadPostOrder(root);
	//post_order_threadtree(PostOrder);
	//BtNode *PreOrder = ThreadPreOrder(root);
	//pre_order_threadtree(PreOrder);
	BtNode *InOrder = ThreadInOrder(root);
	in_order_threadtree(InOrder);
  return 0;
}

