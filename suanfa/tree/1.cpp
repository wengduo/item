
/*************************************************************************
    > File Name: 5.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月10日 星期四 20时34分20秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

class Tree 
{
private:
	typedef char Type;
	struct TreeNode{
		TreeNode *lchild;
		int ltags;
		TreeNode *rchild;
		int rtags;
		Type data;
	};
protected:
public:

}; 

int main(int argc,char *argv[])
{

  return 0;
}
















	Btnode *FValue(Btnode *ptr,ElemPty x)
	{
		if(ptr == NULL) return NULL;
		if(ptr->data > x)
		{
			return FValue(ptr->lchild,x);
		}
		else if(ptr->data < x)
		{
			return FValue(ptr->rchild,x)
		}
		else
		{
			return ptr;
		}
	}

	Btnode *search(Btnode *ptr,ElemPty x)
	{	
		while(NULL != ptr)
		{
			if(ptr->data > x)
			{
				ptr = ptr->lchild; 
			}
			else if(ptr->data < x)
			{
				ptr = ptr->rchild;
			}
			else
			{
				return ptr;
			}
		}
		return NULL;
	}


		if(pa->lchild == ptr)
		{
			if(ptr->lchild != NULL)
			{
				pa->lchild = ptr->lchild;
			}
			else if(ptr->rchild != NULL)
			{
				pa->lchild = ptr->rchild;
			}
			else
			{
				pa->lchild = NULL;
			}
			pa->lchild->parent = pa;
		}
		else
		{
			if(ptr->lchild != NULL)
			{
				pa->rchild = ptr->lchild;
			}
			else if(ptr->rchild != NULL)
			{
				pa->rchild = ptr->rchild;
			}
			else
			{
				pa->rchild = NULL;
			}
			pa->rchild->parent = pa;
		}
		child = ptr->lchild ? ptr->lchild : ptr->rchild;
		free(ptr);










	if(pa == NULL) 
	{
		root = ptr->lchild ? ptr->lchild : ptr->rchild;
		root->parent = NULL;
		free(ptr);
		return;
	}




	pptr = ptr->rchild;
	while(pptr->lchild != NULL)
	{
		pptr = pptr->lchild;
	}
	ptr->data = pptr->data;
	ptr = pptr;

	last()
	{
		while(ptr->rchild != NULL)
		{
			ptr = ptr->rchild;
		}
		return ptr;
	}
	prev()
	{
		if(ptr->lchild != NULL)
		{
			
		}
	}









