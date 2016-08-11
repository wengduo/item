
/*************************************************************************
    > File Name: avl.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年04月18日 星期一 19时18分56秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>

template<class Type>
class AVLTree 
{
	protected:
		struct AVLNode
		{
			Type data;
			int balance;
			AVLNode *parent;
			AVLNode *leftchild;
			AVLNode *rightchild;
		};
	private:
		AVLNode *root;
		static AVLNode *Nil;
		Type RefValue;

		static void Init_Nil()
		{
			Nil = _Buynode(NULL);
			Nil->leftchild = NULL;
			Nil->rightchild = NULL;
			Nil->parent = NULL;
		}

		static AVLNode * _Buynode(AVLNode *pa)
		{
			AVLNode *s = (AVLNode *)malloc(sizeof(AVLNode));
			if(NULL == s) exit(1);
			memset(s,0,sizeof(AVLNode));
			s->balance = 0;
			s->leftchild = NULL;
			s->rightchild = NULL;
			s->parent = pa;
			return s;
		}

		static void _Freenode(AVLNode *p)
		{
			free(p);
		}

		static AVLNode * _BuyRoot(AVLNode *pa)
		{
			AVLNode *s = _Buynode();
			s->parent = pa;
			s->leftchild = s->rightchild = NULL;
			return s;
		}

		static AVLNode * First(AVLNode *ptr)
		{
			while(ptr != NULL && ptr->leftchild != NULL)
			{
				ptr = ptr->leftchild;
			}
			return ptr;
		}

		static AVLNode *Next(AVLNode *ptr)
		{
			if(ptr == NULL) return NULL;
			if(ptr->rightchild != NULL)
			{
				return First(ptr->rightchild);
			}
			else
			{
				AVLNode *pa = ptr->parent;
				while(pa != NULL && pa->leftchild != ptr)
				{
					ptr = pa;
					pa = pa->parent;
				}
				return pa;
			}
		}
	
		static AVLNode * AVL_Next(AVLNode *ptr)
		{
			ptr = ptr->rightchild;
			while(ptr->leftchild != NULL)
				ptr = ptr->leftchild;
			return ptr;
		}

		static void RotateLeft(AVLNode *&ptr)
		{
			AVLNode *newroot = ptr->rightchild;
			newroot->parent = ptr->parent;
			ptr->rightchild = newroot->leftchild;
			if(newroot->leftchild != NULL)
				newroot->leftchild->parent = ptr;
			newroot->leftchild = ptr;
			ptr->parent = newroot;
			ptr = newroot;
		}

		static void RotateRight(AVLNode *&ptr)
		{
			AVLNode *newroot = ptr->leftchild;
			newroot->parent = ptr->parent;//
			ptr->leftchild = newroot->rightchild;
			if(newroot->rightchild != NULL)
				newroot->rightchild->parent = ptr;//
			newroot->rightchild = ptr;
			ptr->parent = newroot;
			ptr = newroot;
		}


		bool LeftBalance(AVLNode *&ptr)
		{
			AVLNode *&leftsub = ptr->leftchild, *rightsub = NULL;
			switch(leftsub->balance)
			{
				case 0: 
					ptr->balance = -1;
					leftsub->balance = 1;
					RotateRight(ptr);
					break;
				case -1:
					ptr->balance = leftsub->balance = 0;
					RotateRight(ptr);
					break;
				case 1:
					rightsub = leftsub->rightchild;
					switch(rightsub->balance)
					{
						case 1:
							ptr->balance = 0;
							leftsub->balance = -1;
							break;
						case -1:
							ptr->balance = 1;
							leftsub->balance = 0;
							break;
						case 0:
							ptr->balance = leftsub->balance = 0;
							break;
					}
					rightsub->balance = 0;
					RotateLeft(leftsub);
					RotateRight(ptr);
					return false;
			}
			return true;
		}

		static bool RightBalance(AVLNode *&ptr)
		{
			AVLNode *&rightsub = ptr->rightchild, *leftsub = NULL;
			switch(rightsub->balance)
			{
				case 0: 
					ptr->balance = 1;
					rightsub->balance = -1;
					RotateLeft(ptr);
					break;
				case 1:
					ptr->balance = rightsub->balance = 0;
					RotateLeft(ptr);
					break;
				case -1:
					leftsub = rightsub->leftchild;
					switch(leftsub->balance)
					{
						case 1: 
							ptr->balance = 0;
							rightsub->balance = -1;
							break;
						case -1:
							ptr->balance = 0;
							rightsub->balance = 1;
							break;
						case 0:
							ptr->balance = rightsub->balance = 0;
							break;
					}
					leftsub->balance =0;
					RotateRight(rightsub);
					RotateLeft(ptr);
					return false;
			}
			return true;
		}

		bool Insert(AVLNode *&root,const Type &x,AVLNode *pa)
		{
			bool res = false;
			AVLNode *ptr = root;
			while(ptr != NULL)
			{
				pa = ptr;
				if(ptr->data < x)
					ptr = ptr->rightchild;
				else if(ptr->data > x)
					ptr = ptr->leftchild;
				else
					return res;
			}
			res = true;
			AVLNode *tmp = _Buynode(pa);
			tmp->data = x;
			if(root == NULL)
			{
				root = tmp;
				root->parent = Nil;
				Nil->leftchild = root;
				return res;
			}
			else
			{
				AVLNode *&pt = pa->data > x ? pa->leftchild:pa->rightchild;
				pt = tmp;
				tmp->parent = pa;
				ptr = tmp;
			}
			AVLNode *gparent = NULL;
			while(pa != Nil)
			{
				gparent = pa->parent;
				if(pa->leftchild == ptr)
				{
					if(pa->balance == 0)
					{
						pa->balance = -1;
					}
					else if(pa->balance == 1)
					{
						pa->balance = 0;
						break;
					}
					else
					{
						AVLNode *&pt = gparent->leftchild == pa ? gparent->leftchild : gparent->rightchild;
						LeftBalance(pt);
						if(gparent == Nil)
							root = pt;
						break;
					}
				}
				else
				{
					if(pa->balance == 0)
					{
						pa->balance = 1;
					}
					else if(pa->balance == -1)
					{
						pa->balance = 0;
						break;
					}
					else
					{
						AVLNode *&pt = gparent->leftchild == pa ? gparent->leftchild : gparent->rightchild;
						RightBalance(pt);
						if(gparent == Nil)
							root = pt;
						break;
					}
				}
				ptr = pa;
				pa = pa->parent;
			}
			return res;
		}

		void Delete_Ajust(AVLNode *&root,AVLNode *pa,AVLNode *ptr)
		{
			AVLNode *gparent = NULL;
			while(pa != Nil)
			{
				gparent = pa->parent;
				AVLNode *&pt = gparent->leftchild == pa ? gparent->leftchild:gparent->rightchild;
				if(pa->leftchild == ptr)
				{
					if(pa->balance == 0)
					{
						pa->balance = 1;
						break;
					}
					else if(pa->balance == -1)
					{
						pa->balance = 0;
					}
					else
					{
						bool shorter = RightBalance(pt);
						if(gparent == Nil)
							root = pt;
						if(shorter)
							break;
					}
				}
				else
				{
					if(pa->balance == 0)
					{
						pa->balance = -1;
						break;
					}
					else if(pa->balance == 1)
					{
						pa->balance = 0;
					}
					else
					{
						bool shorter = LeftBalance(pt);
						if(gparent == Nil)
							root = pt;
						if(shorter)
							break;
					}
				}
				ptr = pt;
				pa = pt->parent;
			}
		}

		bool AVL_Delete(AVLNode *&root,Type key,AVLNode *pa)
		{
			bool res = false;
			if(NULL == root) return res;
			AVLNode *ptr = root;
			while(ptr != NULL)
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
			if(ptr == NULL) return res;
			if(ptr->leftchild != NULL && ptr->rightchild != NULL)
			{
				AVLNode *p = NULL;
				p = AVL_Next(ptr);
				ptr->data = p->data;
				ptr = p;
				pa = p->parent;
			}
			AVLNode *&pt = pa->leftchild == ptr ? pa->leftchild : pa->rightchild;
			if(ptr->leftchild != NULL)
			{
				pt = ptr->leftchild;
				ptr->leftchild->parent = pa;
				if(pa == Nil)
					root = ptr->leftchild;
				else
					Delete_Ajust(root,pa,ptr->leftchild);
			}
			else if(ptr->rightchild != NULL)
			{
				pt = ptr->rightchild;
				ptr->rightchild->parent = pa;
				if(pa == Nil)
				{
					root = ptr->rightchild;
				}
				else
				{
					Delete_Ajust(root,pa,ptr->rightchild);
				}
			}
			else
			{
				pt = NULL;
				if(pa == Nil)
				{
					root = NULL;
					return res;
				}
				else
				{
					AVLNode *tmp = NULL;
					if(pa->leftchild == NULL && pa->rightchild == NULL)
					{
						tmp = pa;
						pa->balance = 0;
						pa = pa->parent;
					}
					Delete_Ajust(root,pa,tmp);
				}
			}
			free(ptr);
			return res;
		}

	public:
		AVLTree(const Type &x):root(NULL),RefValue(x) 
		{
			Init_Nil();
		}
		~AVLTree() {}

		bool Insert(const Type &key)
		{
			bool res = false;
			if(key != RefValue)
			{
				res = Insert(root,key,NULL);
			}
			return res;
		}

		bool Delete(Type key)
		{
			bool res = false;
			if(root != NULL)
			{
				res = AVL_Delete(root,key,NULL);
			}
			return res;
		}
		void fun1(AVLNode *ptr) const
		{
			if(ptr != NULL)
			{
				fun1(ptr->leftchild);
				std::cout << ptr->data <<":" << ptr->balance << "  ";
				fun1(ptr->rightchild);
			}
		}

		void InOrder() const
		{
			fun1(root);
//			for(AVLNode *p = First(root); p != NULL; p = Next(p))
//			{
//				std::cout << p->data <<":" << p->balance << "  ";
//			}
			std::cout << std::endl;
		}
		void cc(AVLNode *p) const
		{
			if(p == NULL) return;
			std::queue<AVLNode *> st;
			st.push(p);
			while(!st.empty())
			{
				p = st.front();st.pop();
				std::cout << p->data << ":" << p->balance << " ";
				if(p->leftchild != NULL)
					st.push(p->leftchild);
				if(p->rightchild != NULL)
					st.push(p->rightchild);
			}
			printf("\n");
		}

		void cengci() const
		{
			cc(root);
		}
};

template <class Type>
typename AVLTree<Type>::AVLNode *AVLTree<Type>::Nil = NULL;
int main()
{
	char ar[]={"rlwkoty"};//qwertyuiopasdfghjklzxcvbnm"};
	//int ar[]={6,3,1,2,7,5,4};
	//int n1 = sizeof(ar)/sizeof(ar[0]) - 1;
	int n1 = strlen(ar) - 1;
	AVLTree<char> myt(-1);
	int m = 0;
	bool tag;
	int k;
	while(n1 >= m)
	{
	//	k = rand()%1000;
		//std::cin >> m;
		if(m == '#') break;
		tag = myt.Insert(ar[m]);
		m++;
		//printf("_____%d_______\n",tag);
		myt.InOrder();
		printf("******************\n");
		myt.cengci();
		printf("******************\n");
	}
	char n;
	while(1)
	{
		std::cin >> n;
		if(n == '#') break;
		tag = myt.Delete(n);
		printf("______%d_______\n",tag);
		myt.InOrder();
		printf("******************\n");
		myt.cengci();
	}
	return 0;
}
