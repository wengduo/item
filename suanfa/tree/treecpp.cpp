
/*************************************************************************
    > File Name: 2t cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月07日 星期一 20时27分05秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <iterator>

template <class T>
const T & Max(const T &a,const T &b)
{
	return a>b?a:b;
}

template <class T>
class BinaryTree
{
private:
	struct BtNode
	{
		T data;
		BtNode *lchild;
		BtNode *rchild;
	};

	static BtNode *_BuyNode()
	{
		BtNode *tmp = (BtNode *)malloc(sizeof(BtNode));
		assert(NULL != tmp);
		return tmp;
	}

	BtNode *Created(const char *&str)
	{
		BtNode *p = NULL;
		if(*str != RValue)
		{
			p = _BuyNode();
			p->data = *str;
			p->lchild = Created(++str);
			p->rchild = Created(++str);
		}
		return p;
	}

	static void PreOrder1(BtNode *p)
	{
		if(NULL != p)
		{
			std::cout << p->data << " ";
			PreOrder1(p->lchild);
			PreOrder1(p->rchild);
		}
	}

	static void InOrder1(BtNode *p)
	{
		if(NULL != p)
		{
			InOrder1(p->lchild);
			std::cout << p->data << " ";
			InOrder1(p->rchild);
		}
	}

	static void PostOrder1(BtNode *p)
	{
		if(NULL != p)
		{
			PostOrder1(p->lchild);
			PostOrder1(p->rchild);
			std::cout << p->data << " ";
		}
	}

	static void Destory1(BtNode *p)
	{
		if(NULL != p)
		{
			Destory1(p->lchild);
			Destory1(p->rchild);
			free(p);
		}
	}

	static int Depth1(BtNode *p)
	{
		if(NULL != p)
		{
			return Max(Depth1(p->lchild),Depth1(p->rchild))+1;
		}
		return 0;
	}

	static int Size1(BtNode *p)
	{
		if(NULL != p)
		{
			return Size1(p->lchild)+Size1(p->rchild)+1;	
		}
		return 0;
	}

	static void LevelOrder1(BtNode *p)
	{
		std::queue<BtNode *> s;
		s.push(p);
		while(!s.empty())
		{
			p = s.front();s.pop();
			std::cout << p->data << " ";
			if(p->lchild != NULL)
			{
				s.push(p->lchild);
			}
			if(NULL != p->rchild)
			{
				s.push(p->rchild);
			}
		}
	}

	static void IsCompleteTree1(BtNode *p)
	{
		if(Size1(p) == pow(2,Depth1(p))-1)
			printf("该树为满二叉树\n");
		else
			printf("该树不是满二叉树\n");
	}

	static void IsComplete1(BtNode *p)
	{
		std::queue<BtNode *> s;
		s.push(p);
		while((p = s.front()) != NULL)
		{
			s.pop();
			s.push(p->lchild);
			s.push(p->rchild);
		}
		while(!s.empty())
		{
			p = s.front();
			s.pop();
			if(NULL != p)
			{
				printf("此树为非完全二叉树\n");
				return;
			}
		}
		printf("此树为完全二叉树\n");
		return;
	}

	static BtNode *Copy(BtNode *p)
	{
		BtNode *s = NULL;
		if(NULL != p)
		{
			s = _BuyNode();
			s->data = p->data;
			s->lchild = Copy(p->lchild);
			s->rchild = Copy(p->rchild);
		}
		return s;
	}
	static BtNode *Find(BtNode *p,const T &x)
	{
		if(p == NULL || p->data == x) return p;
		else
		{
			BtNode *s = Find(p->lchild,x);
			if(NULL != s)
			{
				s = Find(p->rchild,x);
			}
			return s;
		}
	}
	
	static BtNode *FindParent1(BtNode *p,const BtNode *child)
	{
		if(p == NULL || p->lchild == child || p->rchild == child)
		{
			return p;
		}
		else
		{
			BtNode *s = FindParent1(p->lchild,child);
			if(NULL != s)
			{
				s = FindParent1(p->rchild,child);
			}
			return s;
		}
	}
private:
	BtNode *root;
	T RValue;
public:
	typedef BtNode *PBtNode;
	BinaryTree(const T &ch = NULL):root(NULL),RValue(ch){};
	BinaryTree(const BinaryTree<T> &tree):RValue(tree.RValue)
	{
		root = Copy(tree.root);
	}

	BinaryTree<T> & operator=(const BinaryTree<T> &b)
	{
		root = Copy(b.root);
		return *this;
	}

	~BinaryTree()
	{
		Destory();
	}

	BtNode * GetRoot() const
	{
		return root;
	}

  void CreateBTNode(const char *&str)
	{
		if(NULL != str)
		{
			root = Created(str);
		}
		else
		{
			printf("参数有误\n");
		}
	}

	PBtNode *FindValue(const T &x) const
	{
		PBtNode *p = NULL;
		if(x != RValue)
		{
			Find(root,x);
		}
		return p;
	}

	PBtNode *FindParenti(const BtNode *child) const
	{
		if(child == NULL) return NULL;
		else
		{
			return FindParent1(root,child);
		}
	}

	void PreOrder() const
	{
		if(NULL != root)
		{
			PreOrder1(root);
		}
		std::cout << std::endl;
	}

	void InOrder() const
	{
		if(NULL != root)
		{
			InOrder1(root);
		}
		std::cout << std::endl;
	}

	void PostOrder() const
	{
		if(NULL != root)
		{
			PostOrder1(root);
		}
		std::cout << std::endl;
	}

	void LevelOrder() const
	{
		if(NULL != root)
		{
			LevelOrder1(root);
		}
		std::cout << std::endl;
	}

	int Size() const
	{
		if(NULL != root)
		{
			return Size1(root);
		}
		return -1;
	}

	int Depth() const
	{
		if(NULL != root)
		{
			return Depth1(root);
		}
		return -1;
	}

	void Destory()
	{
		if(NULL != root)
		{
			Destory1(root);
			printf("摧毁成功\n");
			root = NULL;
		}
		else
		{
			printf("摧毁失败\n");
		}
	}

	void IsCompleteTree() const
	{
		if(NULL != root)
		{
			IsCompleteTree1(root);
		}
	}

	void IsComplete() const
	{
		if(NULL != root)
		{
			IsComplete1(root);
		}
	}
};

template <class T>
class Treeiterator
{
public:
	BinaryTree<T> &tree;
	typename BinaryTree<T>::PBtNode Ptr;
public:
	Treeiterator(BinaryTree<T> &tree = NULL):tree(tree),Ptr(NULL){};
	virtual ~Treeiterator() {};
	bool IsDone() const { return NULL == Ptr;};
	T & operator*() { return Ptr->data;};
	const T & operator*() const { return Ptr->data;};
	virtual void First() = 0;
	virtual void operator++() = 0;
};

template <typename T>
struct StkNode
{
	typename BinaryTree<T>::PBtNode pnode;
	int popnum;
	StkNode(typename BinaryTree<T>::PBtNode p = NULL):pnode(p),popnum(0){};
};

template <class T>
class Pastiterator:public Treeiterator<T>
{
protected:
	std::stack<StkNode<T> > s; 
public:
	Pastiterator(BinaryTree<T> &tree):Treeiterator<T>(tree){};
	~Pastiterator(){};
	void First()
	{
		this->Ptr = NULL;
		if(NULL != this->tree.GetRoot())
		{
			s.push(StkNode<T>(this->tree.GetRoot()));
			operator++();
		}
	}
	void operator++()
	{
		if(s.empty())
		{
			this->Ptr = NULL;
			return;
		}
		StkNode<T> node;
		while(1)
		{
			node = s.top();s.pop();
			if(++node.popnum == 3)
			{
				this->Ptr = node.pnode;
				return;
			}
			s.push(node);
			if(node.popnum == 1 && node.pnode->lchild != NULL)
			{
				s.push(StkNode<T>(node.pnode->lchild));
			}
			else if(node.popnum == 2 && node.pnode->rchild != NULL)
			{
				s.push(StkNode<T>(node.pnode->rchild));
			}
		}
	}
};
template <class T>
class Initerator:public Pastiterator<T>
{
public:
	Initerator(BinaryTree<T> &b):Pastiterator<T>(b){};
	~Initerator(){};
	void operator++()
	{
		if(this->s.empty())
		{
			this->Ptr = NULL;
			return;
		}
		StkNode<T> node;
		while(1)
		{
			node = this->s.top();this->s.pop();
			if(++node.popnum == 2)
			{
				this->Ptr = node.pnode;
				if(node.pnode->rchild != NULL)
				{
					this->s.push(StkNode<T>(node.pnode->rchild));
				}
				return;
			}
			this->s.push(node);
			if(node.popnum == 1 && node.pnode->lchild != NULL)
			{
				this->s.push(StkNode<T>(node.pnode->lchild));
			}
		}
		
	}
};
template <class T>
class Preiterator:public Treeiterator<T>
{
protected:
	std::stack<typename BinaryTree<T>::PBtNode> s;
public:
	Preiterator(BinaryTree<T> &b):Treeiterator<T>(b){};
	~Preiterator(){};
	void First()
	{
		this->Ptr = NULL;
		if(NULL != this->tree.GetRoot())
		{
			s.push(this->tree.GetRoot());
			operator++();
		}
	}
	void operator++()
	{
		if(this->s.empty())
		{
			this->Ptr = NULL;
			return;
		}
		typename BinaryTree<T>::PBtNode node;
		while(1)
		{
			node = s.top();s.pop();
			this->Ptr = node;
			if(node->rchild != NULL)
			{
				s.push(node->rchild);
			}
			if(node->lchild != NULL)
			{
				s.push(node->lchild);
			}
			return;
		}
	}
};

template <class T>
class Leveliterator:public Treeiterator<T>
{
protected:
	std::queue<typename BinaryTree<T>::PBtNode> s;
public:
	Leveliterator(BinaryTree<T> &b = NULL):Treeiterator<T>(b){};
	~Leveliterator(){};
	void First()
	{
		this->Ptr = NULL;
		if(NULL != this->tree.GetRoot())
		{
			s.push(this->tree.GetRoot());
			operator++();
		}
	}
	void operator++()
	{
		if(s.empty())
		{
			this->Ptr = NULL;
			return;
		}
		typename BinaryTree<T>::PBtNode node;
		while(1)
		{
			node = s.front();s.pop();
			this->Ptr = node;
			if(NULL != node->lchild)
			{
				s.push(node->lchild);
			}
			if(NULL != node->rchild)
			{
				s.push(node->rchild);
			}
			return;
		}
	}
};
template <class T>
void PrintTree(Treeiterator<T> &bt)
{
	bt.First();
	while(!bt.IsDone())
	{
		std::cout << *bt << " ";
		++bt;
	}
	printf("\n");
}
int main(int argc,char *argv[])
{
	const char *str ="ABC##DE##F##G#H##";
	BinaryTree<char> myt('#');
	myt.CreateBTNode(str);
//	myt.PreOrder();
//	myt.InOrder();
//	myt.PostOrder();
//	myt.LevelOrder();
//	printf("depth:%d\n",myt.Depth());
//	printf("size:%d\n",myt.Size());
//	myt.IsCompleteTree();
//	myt.IsComplete();
//	BinaryTree<char> mm(myt);
//	BinaryTree<char> cc('#');
//	cc = myt;
//	cc.PreOrder();
//	mm.PreOrder();
	Pastiterator<char> pi(myt);
	Initerator<char> pd(myt);
	Preiterator<char> pe(myt);
	Leveliterator<char> dd(myt);
	PrintTree(pi);
	PrintTree(pd);
	PrintTree(pe);
	PrintTree(dd);
  return 0;
}

