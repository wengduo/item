/*************************************************************************
    > File Name: rbtree.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月07日 星期六 00时22分08秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <queue>
#include <time.h>
template <class Type>
class RBTree
{
	private:
		typedef enum{RED=0,BLACK=1}utype;
		struct RBNode
		{
			Type data;
			utype color;
			RBNode *parent;
			RBNode *leftchild;
			RBNode *rightchild;
		};
		static RBNode * _Buynode(Type x,RBNode *Nil,RBNode *pa)
		{
			RBNode *s = (RBNode *)malloc(sizeof(RBNode));
			if(NULL == s) exit(1);
			memset(s,0,sizeof(RBNode));
			s->color = RED;
			s->leftchild = Nil;
			s->rightchild = Nil;
			s->parent = pa;
			s->data = x;
			return s;
		}
		static void _Freenode(RBNode *p)
		{
			free(p);
		}
		static void RotateLeft(RBNode *&ptr)
		{
			RBNode *newroot = ptr->rightchild;
			newroot->parent = ptr->parent;
			ptr->rightchild = newroot->leftchild;
			if(newroot->leftchild != NULL)
				newroot->leftchild->parent = ptr;
			newroot->leftchild = ptr;
			ptr->parent = newroot;
			ptr = newroot;
		}

		static void RotateRight(RBNode *&ptr)
		{
			RBNode *newroot = ptr->leftchild;
			newroot->parent = ptr->parent;
			ptr->leftchild = newroot->rightchild;
			if(newroot->rightchild != NULL)
				newroot->rightchild->parent = ptr;
			newroot->rightchild = ptr;
			ptr->parent = newroot;
			ptr = newroot;
		}

		void Init_header()
		{
			header = (RBNode*)malloc(sizeof(RBNode));
			memset(header,0,sizeof(RBNode));
			header->color = BLACK;
			header->leftchild = header->rightchild = header->parent = NULL;
		}	

		static void Init_Nil()
		{
			if(Nil == NULL)
			{
				Nil = (RBNode*)malloc(sizeof(RBNode));
				memset(Nil,0,sizeof(RBNode));
				Nil->color = BLACK;
				Nil->data = -1;
				Nil->leftchild = Nil->rightchild = Nil->parent = NULL;
			}
			count++;
		}	

		static void Inorder(RBNode *ptr)
		{
			if(ptr != Nil)
			{
				Inorder(ptr->leftchild);
				std::cout << ptr->data << ":" << ptr->color << " ";
				if(ptr->color == RED && ptr->parent->color == RED)
				{
					printf("error\n");
					exit(0);
				}
				Inorder(ptr->rightchild);
			}
		}

		static void CC(RBNode *ptr)
		{
			std::queue<RBNode *> st;
			st.push(ptr);
			RBNode *s = NULL;
			while(!st.empty())
			{
				s = st.front();st.pop();
				std::cout << s->data << ":" << s->color <<":" << s->parent->data << " ";
				if(s->leftchild != Nil)
					st.push(s->leftchild);
				if(s->rightchild != Nil)
					st.push(s->rightchild);
			}
		}
		static void Rb_Insert(RBNode *ptr,RBNode *&root)
		{
			RBNode *ptrParent = NULL;
			RBNode *gparent = NULL;
			while(((ptrParent = ptr->parent) != Nil) && ptrParent->color == RED)  
			{
				gparent = ptrParent->parent;
				if(gparent->leftchild == ptrParent)
				{
					RBNode *ptrPaBro = gparent->rightchild;
					if(ptrPaBro->color == RED)
					{
						if(ptrPaBro != Nil)
							ptrPaBro->color = BLACK;
						ptrParent->color = BLACK;
						gparent->color = RED;
						ptr = gparent;
					}
					else
					{
						if(ptrParent->rightchild == ptr)
						{
							RotateLeft(gparent->leftchild);
							ptr = ptr->leftchild;
							ptrParent = ptr->parent;
							gparent = ptrParent->parent;
						}
						ptr->parent->color = BLACK;
						ptr->parent->parent->color = RED;
						RBNode *&pt = gparent->parent->leftchild == gparent ? gparent->parent->leftchild : gparent->parent->rightchild;
						RotateRight(pt);
						if(pt->parent == Nil)
							root = pt;
					}
				}
				else
				{
					RBNode *ptrPaBro = gparent->leftchild;
					if(ptrPaBro->color == RED)
					{
						if(ptrPaBro != Nil)
							ptrPaBro->color = BLACK;
						ptrParent->color = BLACK;
						gparent->color = RED;
						ptr = gparent;
					}
					else
					{
						if(ptrParent->leftchild == ptr)
						{
							RotateRight(gparent->rightchild);
							ptr = ptr->rightchild;
							ptrParent = ptr->parent;
							gparent = ptrParent->parent;
						}
						ptr->parent->color = BLACK;
						ptr->parent->parent->color = RED;
						RBNode *&pt = gparent->parent->leftchild == gparent ? gparent->parent->leftchild : gparent->parent->rightchild;
						RotateLeft(pt);
						if(pt->parent == Nil)
							root = pt;
					}
				}
			}
			root->color = BLACK;
		}

		static RBNode * RB_Next1(RBNode *ptr)
		{
			ptr = ptr->leftchild;
			while(ptr->rightchild != Nil)
				ptr = ptr->rightchild;
			return ptr;
		}

		static RBNode * RB_Next(RBNode *ptr)
		{
			ptr = ptr->rightchild;
			while(ptr->leftchild != Nil)
				ptr = ptr->leftchild;
			return ptr;
		}


		static void RB_Remove(RBNode *ptrParent,RBNode *ptr,RBNode *&root)
		{
			if(ptr->color == RED)
			{
				ptr->color = BLACK;
				return;
			}
			RBNode *gparent = NULL;
			while(ptrParent != Nil && ptr->color == BLACK)
			{
				gparent = ptrParent->parent;
				RBNode *&pt = gparent->leftchild == ptrParent ? gparent->leftchild : gparent->rightchild;
				if(ptrParent->leftchild == ptr)
				{
					RBNode *ptrPaBro = ptrParent->rightchild;
					if(ptrPaBro->color == RED)
					{
						ptrPaBro->color = BLACK;
						ptrParent->color = RED;
						RotateLeft(pt);
						if(gparent == Nil)
							root = pt;
						break;
					}
					if(ptrPaBro == Nil || (ptrPaBro->leftchild->color == BLACK && ptrPaBro->rightchild->color == BLACK))
					{
						if(ptrPaBro != Nil)
							ptrPaBro->color = RED;
						if(ptrParent->color == RED)
						{
							ptrParent->color = BLACK;
							break;
						}
						else
						{
							ptr = ptrParent;
							ptrParent = ptr->parent;
						}
					}
					else
					{
						if(ptrPaBro->rightchild->color == BLACK)
						{
							if(ptrPaBro->leftchild != Nil)
								ptrPaBro->leftchild->color = BLACK;
							ptrPaBro->color = RED;
							RotateRight(ptrParent->rightchild);
							ptrPaBro = ptrParent->rightchild;
						}
						ptrPaBro->color = ptrParent->color;
						ptrParent->color = BLACK;
						ptrPaBro->rightchild->color = BLACK;
						RotateLeft(pt);
						if(gparent == Nil)
							root = pt;
						break;
					}
				}
				else
				{
					RBNode *ptrPaBro = ptrParent->leftchild;
					if(ptrPaBro->color == RED)
					{
						ptrPaBro->color = BLACK;
						ptrParent->color = RED;
						RotateRight(pt);
						if(gparent == Nil)
						{
							root = pt;
						}
						break;
					}
					if(ptrPaBro == Nil || (ptrPaBro->leftchild->color == BLACK && ptrPaBro->rightchild->color == BLACK))
					{
						if(ptrPaBro != Nil)
							ptrPaBro->color = RED;
						if(ptrParent->color == RED)
						{
							ptrParent->color = BLACK;
							break;
						}
						else
						{
							ptr = ptrParent;
							ptrParent = ptr->parent;
						}
					}
					else
					{
						if(ptrPaBro->leftchild->color == BLACK)
						{
							if(ptrPaBro->rightchild != Nil)
								ptrPaBro->rightchild->color = BLACK;
							ptrPaBro->color = RED;
							RotateLeft(ptrParent->leftchild);
							ptrPaBro = ptrParent->leftchild;
						}
						ptrPaBro->color = ptrParent->color;
						ptrParent->color = BLACK;
						ptrPaBro->leftchild->color = BLACK;
						RotateRight(pt);
						if(gparent == Nil)
							root = pt;
						break;
					}
				}
			}
			root->color = BLACK;
		}

	public:
		RBTree():root(NULL),header(NULL)
	{
		Init_header();
		Init_Nil();
		root = Nil;
	}
		~RBTree()
		{
			if(--count == 0 && Nil != NULL)
			{
				_Freenode(Nil);
				Nil = NULL;
			}
		}

		bool Insert(Type key)
		{
			RBNode *pNode = root;  
			RBNode *pPreNode = Nil;  
			while(pNode != Nil) 
			{  
				pPreNode = pNode;  
				if(key < pNode->data)  
				{  
					pNode = pNode->leftchild;  
				}  
				else if (key > pNode->data)  
				{  
					pNode = pNode->rightchild;  
				}  
				else
				{  
					return 0;  
				}  
			}  
			RBNode *pNewNode = _Buynode(key,Nil,pPreNode); 
			if(pPreNode == Nil)
			{  
				pNewNode->color = BLACK; 
				root = pNewNode;
				root->parent = Nil;
				Nil->leftchild = root;
				return 1;
			} 
			pNewNode->parent = pPreNode;
			RBNode *&pptr = key < pPreNode->data ? pPreNode->leftchild : pPreNode->rightchild; 
			pptr = pNewNode;
			Rb_Insert(pptr,root);
			return 1;  
		}

		bool Remove(Type key)
		{
			bool res = false;
			if(root == NULL) return res;
			else
			{
				RBNode *pa = Nil;
				RBNode *ptr = root;
				while(ptr != Nil)
				{	
					pa = ptr;
					if(key < ptr->data)
						ptr = ptr->leftchild;
					else if(key > ptr->data)
						ptr = ptr->rightchild;
					else
					{
						pa = pa->parent;
						break;
					}
				}
				if(ptr == Nil) return res;
				if(ptr->leftchild != Nil && ptr->rightchild != Nil)
				{
					RBNode *p = NULL;
					if(ptr->color == RED && ptr->data != 1)
						p = RB_Next1(ptr);
					else
						p = RB_Next(ptr);
					ptr->data = p->data;
					ptr = p;
					pa = p->parent;
				}
				RBNode *&pt = pa->leftchild == ptr ? pa->leftchild : pa->rightchild;
				if(ptr->leftchild != Nil)
				{
					pt = ptr->leftchild;
					ptr->leftchild->parent = pa;
					if(pa == Nil)
						root = ptr->leftchild;
					if(ptr->color == BLACK)
						RB_Remove(pa,ptr->leftchild,root);
				}
				else if(ptr->rightchild != Nil)
				{
					pt = ptr->rightchild;
					ptr->rightchild->parent = pa;
					if(pa == Nil)
						root = ptr->rightchild;
					if(ptr->color == BLACK)
						RB_Remove(pa,ptr->rightchild,root);
				}
				else
				{
					if(pa == Nil)
					{
						root = NULL;
						Nil->leftchild = NULL;
					}
					else
					{
						pt = Nil;
						if(ptr->color == BLACK)
							RB_Remove(pa,Nil,root);
					}
				}
				free(ptr);
				res = true;
			}
			return res;
		}
		void show()
		{
			if(root != NULL)
			{
				Inorder(root);
			}
		}
		void c()
		{
			if(root != NULL)
			{
				CC(root);
			}
		}
	private:
		RBNode *root;
		RBNode *header;
		static RBNode *Nil;
		static int count;
};

template <class Type>
typename RBTree<Type>::RBNode *RBTree<Type>::Nil = NULL;

template <class Type>
int RBTree<Type>::count = 0;

int main(int argc,char *argv[])
{
	RBTree<int> root;	
	int ar[] = {12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};
	//int n = sizeof(ar)/sizeof(ar[0]);
	int n = 10000;
	int i = 0;
	int k;
	while(i < n )
	{
		k = rand()%10000;
		//root.Insert(ar[i]);
	//	std::cin >> k;
	//	if(k == -1) break;
		root.Insert(i);
		//std::cout << k << ": ";
		//root.show();
		//printf("\n");
		//root.c();
		printf("\n");
		i++;
	}
	root.show();
	i = 0;
	int m;
	printf("\nllllllllllllllllllllll\n");
	while(i < n)
	{
		//std::cin >> m;
		//if(i == -1) break;
		//m = rand()%10000000;
		root.Remove(i);
		printf("\nllllllllllllllllllllll\n");
		std::cout << i << ": ";
		root.c();
		i++;
	}
	return 0;
}
