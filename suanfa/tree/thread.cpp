
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
#include <cmath>
#include <thread>
#include <semaphore.h>
#include <mutex>
#include <atomic>
#include <stack>
#include <cstdlib>
#include <queue>
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
	static void PreOrder1(BtNode *p)
	{
		if(NULL != p)
		{
			std::cout << p->data << " ";
			PreOrder1(p->lchild);
			PreOrder1(p->rchild);
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
	bool IsDone() {	return NULL == Ptr;};
	T & operator*() { return Ptr->data;};
	const T & operator*() const { return Ptr->data;};
	virtual void First() = 0;
	virtual void operator++() = 0;
};
std::mutex mu;
std::atomic<bool> ready(false);
template <class T>
class Pastiterator:public Treeiterator<T>
{
protected:
	static void my_o(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		if(p->lchild != NULL)
			my_o(p->lchild,t);
		if(p->rchild != NULL)
			my_o(p->rchild,t);
		while(!ready);
		mu.lock();
		*t = p;
		ready = false;
		mu.unlock();
	}
	static void my_operator(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		my_o(p,t);
		while(!ready);
		mu.lock();
		*t = NULL;
		ready = false;
		mu.unlock();
	}
public:
	Pastiterator(BinaryTree<T> &tree):Treeiterator<T>(tree){
		ready = false;
	};
	~Pastiterator(){};
	void First()
	{
		if(NULL != this->tree.GetRoot())
		{
			std::thread y(my_operator,this->tree.GetRoot(),&this->Ptr);
			y.detach();
			ready = true;
		}
		while(ready);
	}
	void operator++()
	{
		mu.lock();
		ready = true;
		mu.unlock();
		while(ready);
	}
};
template <class T>
class Initerator:public Pastiterator<T>
{
protected:
	static void my_o(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		if(p->lchild != NULL)
			my_o(p->lchild,t);
		while(!ready);
		mu.lock();
		*t = p;
		ready = false;
		mu.unlock();
		if(p->rchild != NULL)
			my_o(p->rchild,t);
	}
	static void my_operator(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		my_o(p,t);
		while(!ready);
		mu.lock();
		*t = NULL;
		ready = false;
		mu.unlock();
		mu.~mutex();
	}
public:
	Initerator(BinaryTree<T> &b):Pastiterator<T>(b){
		ready = false;
	};
	~Initerator(){};
	void First()
	{
		if(NULL != this->tree.GetRoot())
		{
			std::thread y(my_operator,this->tree.GetRoot(),&this->Ptr);
			y.detach();
			ready = true;
		}
		while(ready);
	}
};
template <class T>
class Preiterator:public Initerator<T>
{
protected:
	static void my_o(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		while(!ready);
		mu.lock();
		*t = p;
		ready = false;
		mu.unlock();
		if(p->lchild != NULL)
			my_o(p->lchild,t);
		if(p->rchild != NULL)
			my_o(p->rchild,t);
	}
	static void my_operator(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		my_o(p,t);
		while(!ready);
		mu.lock();
		*t = NULL;
		ready = false;
		mu.unlock();
		mu.~mutex();
	}
public:
	Preiterator(BinaryTree<T> &b):Initerator<T>(b){
		this->Ptr = NULL;
	};
	~Preiterator(){
	}
	void First()
	{
		if(NULL != this->tree.GetRoot())
		{
			std::thread y(my_operator,this->tree.GetRoot(),&this->Ptr);
			y.detach();
			ready = true;
		}
		while(ready);
	}
};

template <class T>
class Leveliterator:public Preiterator<T>
{
private:
	static void my_operator(typename BinaryTree<T>::PBtNode p,typename BinaryTree<T>::PBtNode *t)
	{
		std::queue<typename BinaryTree<T>::PBtNode > s;
		s.push(p);
		while(!s.empty())
		{
			p = s.front();s.pop();
			while(!ready);
			mu.lock();
			*t = p;
			ready = false;
			mu.unlock();
			if(p->lchild != NULL)
			{
				s.push(p->lchild);
			}
			if(p->rchild != NULL)
			{
				s.push(p->rchild);
			}
		}
		while(!ready);
		mu.lock();
		*t = NULL;
		ready = false;
		mu.unlock();
	}
public:
	Leveliterator(BinaryTree<T> &b = NULL):Preiterator<T>(b){
		ready = false;
	};
	~Leveliterator(){};
	void First()
	{
		if(NULL != this->tree.GetRoot())
		{
			std::thread y(my_operator,this->tree.GetRoot(),&this->Ptr);
			y.detach();
			ready = true;
		}
		while(ready);
	}
};
int main(int argc,char *argv[])
{
	const char *str ="ABC##DE##F##G#H##";
	BinaryTree<char> myt('#');
	myt.CreateBTNode(str);
	Pastiterator<char> pi(myt);
	pi.First();
	printf("后续遍历\n");
	while(!pi.IsDone())
	{
		std::cout << *pi << " ";
		++pi;
	}
	printf("\n中序遍历\n");
	Initerator<char> pp(myt);
	pp.First();
	while(!pp.IsDone())
	{
		std::cout << *pp << " ";
		++pp;
	}
	printf("\n先序便利\n");
	Preiterator<char> pd(myt);
	pd.First();
	while(!pd.IsDone())
	{
			std::cout << *pd << " ";
			++pd;
	}
	printf("\n层次遍历\n");
	Leveliterator<char> dd(myt);
	dd.First();
	while(!dd.IsDone())
	{
		std::cout << *dd << " ";
		++dd;
	}
	printf("\n");
  return 0;
}

