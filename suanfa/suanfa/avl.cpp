
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
		Type RefValue;

		static AVLNode * _Buynode()
		{
			AVLNode *s = (AVLNode *)malloc(sizeof(AVLNode));
			if(NULL == s) exit(1);
			memset(s,0,sizeof(AVLNode));
			s->balance = 0;
			s->leftchild = NULL;
			s->rightchild = NULL;
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
			}else
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


		void LeftBalance(AVLNode *&ptr,bool &shorter)
		{
			AVLNode *&leftsub = ptr->leftchild, *rightsub = NULL;
			int k;
			switch(leftsub->balance)
			{
				case 0: 
					std::cout << "left already balance" << std::endl;
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
					break;
			}
		}

		static void RightBalance(AVLNode *&ptr,bool &shorter)
		{
			AVLNode *&rightsub = ptr->rightchild, *leftsub = NULL;
			switch(rightsub->balance)
			{
				case 0: 
					std::cout << "Right already balance " << std::endl;
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
					break;
			}
		}

		bool Insert(AVLNode *&ptr,const Type &x,AVLNode *pa,bool &shorter)
		{
			bool res = false;
			if(ptr == NULL)
			{
				ptr = _BuyRoot(pa);
				ptr->data = x;
				shorter = true;
				res = true;
			}
			else if(x < ptr->data)
			{
				res = Insert(ptr->leftchild,x,ptr,shorter);
				if(res == false) return res;
				if(shorter)
				{
					switch(ptr->balance)
					{
						case 0: 
							ptr->balance = -1; break;
						case 1: 
							ptr->balance = 0;shorter = false; break;
						case -1:
							LeftBalance(ptr,shorter);
							shorter = false;
							break;
					}
				}
			}
			else if(x > ptr->data)
			{
				res = Insert(ptr->rightchild,x,ptr,shorter);
				if(res == false) return res;
				if(shorter)
				{
					switch(ptr->balance)
					{
						case 0: 
							ptr->balance = 1; break;
						case -1: 
							ptr->balance = 0; shorter = false; break;
						case 1: 
							RightBalance(ptr,shorter);
							shorter = false;
							break;
					}
				}
			}
			return res;
		}
		
		void DLeftBalance(AVLNode *&ptr,bool &shorter)
		{
			AVLNode *&leftsub = ptr->leftchild, *rightsub = NULL;
			switch(leftsub->balance)
			{
				case 0: 
					if(height(ptr->leftchild)-height(ptr->rightchild) == 2)
					{
						RotateRight(ptr);
						ptr->balance = 1;
					}
					break;
				case -1:
					ptr->balance = leftsub->balance = 0;
					RotateRight(ptr);
					shorter = true;
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
					break;
			}
		}

	  void DRightBalance(AVLNode *&ptr,bool &shorter)
		{
			AVLNode *&rightsub = ptr->rightchild, *leftsub = NULL;
			switch(rightsub->balance)
			{
				case 0: 
					if(height(ptr->rightchild)-height(ptr->leftchild) == 2)
					{
						RotateLeft(ptr);
						ptr->balance = -1;
					}
					break;
				case 1:
					ptr->balance = rightsub->balance = 0;
					RotateLeft(ptr);
					shorter = true;
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
					break;
			}
		}
		int Max(int a,int b)
		{
			return a>b ? a:b;
		}

		int height(AVLNode *ptr)
		{
			if(NULL == ptr) return 0;
			return Max(height(ptr->leftchild),height(ptr->rightchild)) + 1;
		}

		static AVLNode *findvalue(AVLNode *p,int value)
		{
			AVLNode *tmp = NULL;
			while(p != NULL)
			{
				if(p->data == value)
				{
					tmp = p;
					break;
				}
				else if(value < p->data)
					p = p->leftchild;
				else
					p = p->rightchild;
			}
			return tmp;
		}

		bool Avl_Serach_Delete(AVLNode *&ptr,Type key,bool &shorter)
		{
			bool res = false;
			if(NULL == ptr) return res;
			if(key == ptr->data)
			{
				if(ptr->leftchild != NULL && ptr->rightchild != NULL)
				{
					if(ptr->balance == -1)
					{
						AVLNode *p = ptr->leftchild;
						while(p->rightchild != NULL) 
						{
							p = p->rightchild;
						}
						ptr->data = p->data;
						res = Avl_Serach_Delete(ptr->leftchild,p->data,shorter);
						if(!res) return res;
						if(shorter)
						{
							switch(ptr->balance)
							{
								case 1:
									DLeftBalance(ptr,shorter);
									shorter = false;
									break;
								case 0:
									ptr->balance = 1;
									shorter = false;
									break;
								case -1:
									ptr->balance = 0;
							}
						}
						if(ptr != NULL)
						{
							printf("ptr0:%d:%d\n",ptr->balance,ptr->data);
							ptr->balance = height(ptr->rightchild)-height(ptr->leftchild);
							printf("ptr1:%d:%d\n",ptr->balance,ptr->data);
						}					
					}
					else
					{
						AVLNode *p = ptr->rightchild;
						while(p->leftchild != NULL) 
						{
							p = p->leftchild;
						}
						ptr->data = p->data;
						res = Avl_Serach_Delete(ptr->rightchild,p->data,shorter);
						if(!res) return res;
						if(shorter)
						{
							switch(ptr->balance)
							{
								case 1:
									ptr->balance = 0;
									break;
								case 0:
									ptr->balance = -1;
									shorter = false;
									break;
								case -1:
									DRightBalance(ptr,shorter);
									shorter = false;
									break;
							}
						}
						if(ptr != NULL)
						{
							ptr->balance = height(ptr->rightchild)-height(ptr->leftchild);
						}
					}
				}
				else
				{
					AVLNode *p = ptr;
					if(ptr->leftchild != NULL)
					{
						ptr = ptr->leftchild;
						ptr->parent = p->parent;
					}
					else if(ptr->rightchild != NULL)
					{
						ptr = ptr->rightchild;
						ptr->parent = p->parent;
					}
					shorter = true;
					res = true;
					if(ptr == p) ptr = NULL;
					free(p);
				}
			}
			else if(key < ptr->data)
			{
				res = Avl_Serach_Delete(ptr->leftchild,key,shorter);
				if(!res) return res;
				if(shorter)
				{
					switch(ptr->balance)
					{
						case 1:
							shorter = false;
							DRightBalance(ptr,shorter);
							break;
						case 0:
							ptr->balance = 1;
							shorter = false;
							break;
						case -1:
							ptr->balance = 0;
					}
				}
				if(ptr != NULL)
				{
					printf("ptr0:%d:%d\n",ptr->balance,ptr->data);
					ptr->balance = height(ptr->rightchild)-height(ptr->leftchild);
					printf("ptr1:%d:%d\n",ptr->balance,ptr->data);
				}
			}
			else
			{
				res = Avl_Serach_Delete(ptr->rightchild,key,shorter);
				if(!res) return res;
				if(shorter)
				{
					switch(ptr->balance)
					{
						case 1:
							ptr->balance = 0;
							break;
						case 0:
							ptr->balance = -1;
							shorter = false;
							break;
						case -1:
							shorter = false;
							DLeftBalance(ptr,shorter);
							break;
					}
				}
				if(ptr != NULL)
				{
					printf("ptr0:%d:%d\n",ptr->balance,ptr->data);
					ptr->balance = height(ptr->rightchild)-height(ptr->leftchild);
					printf("ptr1:%d:%d\n",ptr->balance,ptr->data);
				}
			}
			return res;
		}

	public:
		AVLTree(const Type &x):root(NULL),RefValue(x) {}
		~AVLTree() {}

		bool Insert(const Type &key)
		{
			bool res = false;
			bool shorter = true;
			if(key != RefValue)
			{
				res = Insert(root,key,NULL,shorter);
			}
			return res;
		}

		bool Avl_Delete(Type key)
		{
			bool res = false;
			if(root != NULL)
			{
				bool shorter = false;
				res = Avl_Serach_Delete(root,key,shorter);
			}
			return res;
		}
		void InOrder() const
		{
			for(AVLNode *p = First(root); p != NULL; p = Next(p))
			{
				std::cout << p->data <<":" << p->balance << "  ";
			}
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

int main()
{
	char ar[]={"rlwkoty"};//qwertyuiopasdfghjklzxcvbnm"};
	//int ar[]={6,3,1,2,7,5,4};
	//int n1 = sizeof(ar)/sizeof(ar[0]) - 1;
	int n1 = strlen(ar) - 1;
	AVLTree<char> myt(-1);
	int m = 0;
	bool tag;
	while(n1 >= 0)
	{
		//m = rand()%1000;
		//std::cin >> m;
		//if(m == -1) break;
		tag = myt.Insert(ar[m]);
		n1--;
		m++;
		printf("_____%d_______\n",tag);
		myt.InOrder();
		printf("******************\n");
		myt.cengci();
	}
	char n;
	while(1)
	{
		std::cin >> n;
		if(n == -1) break;
		tag = myt.Avl_Delete(n);
		printf("______%d_______\n",tag);
		myt.InOrder();
		printf("******************\n");
		myt.cengci();
	}
	return 0;
}
