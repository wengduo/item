
/*************************************************************************
    > File Name: tdtreecpp.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月19日 星期六 22时28分38秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

typedef enum{Link = 0,Thread = 1}Tag;
template <typename Type>
class TdTree{
protected:
	struct BtNode{
		BtNode *lchild;
		BtNode *rchild;
		Tag ltags;
		Tag rtags;
		Type data;
	};
private:
	Type Value;
	BtNode *root;
	static BtNode *_BuyNode(){
		return (BtNode *)malloc(sizeof(BtNode));
	}
	BtNode *Created(const char *&str){
		BtNode *s = NULL;
		if(*str != Value)
		{
			s = _BuyNode();
			s->ltags = Link;
			s->rtags = Link;
			s->data = *str;
			s->lchild = Created(++str);
			s->rchild = Created(++str);
		}
		return s;
	}
	void ThreadInOrder1(BtNode *p,BtNode *&pre)
	{
		if(NULL != p)
		{
			ThreadInOrder1(p->lchild,pre);
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
			ThreadInOrder1(p->rchild,pre);
		}
	}
	static BtNode *First(BtNode *p)
	{
		if(p == NULL) return NULL;
		while(NULL != p->lchild && p->ltags == Link)
		{
			p = p->lchild;
		}
		return p;
	}
	static BtNode *Last(BtNode *p)
	{
		if(p == NULL) return NULL;
		while(NULL != p->rchild && p->rtags == Link)
		{
			p = p->rchild;
		}
		return p;
	}
	static BtNode *Next(BtNode *p)
	{
		if(p->rtags == Thread)
		{
			p = p->rchild;
		}
		else
		{
			p = p->rchild;
			p = First(p);
		}
		return p;
	}
	static BtNode *Prev(BtNode *p)
	{
		if(p->ltags == Thread)
		{
			p = p->lchild;
		}
		else
		{
			p = p->lchild;
			p = Last(p);
		}
		return p;
	}
	static void InOrderN(BtNode *p)
	{
		for(p = First(p);p != NULL;p = Next(p))
		{
			std::cout << p->data << " ";
		}
	}
	static void InOrderP(BtNode *p)
	{
		for(p = Last(p);p != NULL;p = Prev(p))
		{
			std::cout << p->data << " ";
		}
	}
public:
	typedef BtNode *PBtNode;
	TdTree(const Type &b = NULL):root(NULL),Value(b){};
	BtNode *GetRoot()
	{
		return root;
	}
	void CreatedTree(const char *&str)
	{
		if(NULL != str)
		{
			root = Created(str);
			return;
		}
		printf("error\n");
	}
	void ThreadInOrder()
	{
		if(NULL != root)
		{
			BtNode *pre = NULL;
			ThreadInOrder1(root,pre);
			pre->rtags = Thread;
			pre->rchild = NULL;
		}
	}
	void InOrderNext()
	{
		if(NULL != root)
		{
			InOrderN(root);
			std::cout << std::endl;
		}
	}
	void InOrderPrev()
	{
		if(NULL != root)
		{
			InOrderP(root);
			std::cout << std::endl;
		}
	}
};
template <typename Type>
class Initerator{
private:
	TdTree<Type> &tree;
	typename TdTree<Type>::PBtNode Pre;
	static typename TdTree<Type>::PBtNode first1(typename TdTree<Type>::PBtNode p)
	{
		if(p == NULL) return NULL;
		while(NULL != p->lchild && p->ltags == Link)
		{
			p = p->lchild;
		}
		return p;
	}
	static typename TdTree<Type>::PBtNode last1(typename TdTree<Type>::PBtNode p)
	{
		if(p == NULL) return NULL;
		while(NULL != p->rchild && p->rtags == Link)
		{
			p = p->rchild;
		}
		return p;
	}
	static typename TdTree<Type>::PBtNode Next(typename TdTree<Type>::PBtNode p)
	{
		if(p->rtags == Thread)
		{
			p = p->rchild;
		}
		else
		{
			p = p->rchild;
			p = first1(p);
		}
		return p;
	}
	static typename TdTree<Type>::PBtNode Prev(typename TdTree<Type>::PBtNode p)
	{
		if(p->ltags == Thread)
		{
			p = p->lchild;
		}
		else
		{
			p = p->lchild;
			p = last1(p);
		}
		return p;
	}
public:
	Initerator(TdTree<Type> &tree = NULL):tree(tree),Pre(NULL){};
	~Initerator(){};
	bool IsDone()
	{
		return NULL == Pre;
	}
	void First()
	{
		Pre = tree.GetRoot();
		Pre = first1(Pre);
	}
	void Last()
	{
		Pre = tree.GetRoot();
		Pre = last1(Pre);
	}
	Type & operator*()
	{
		return Pre->data;
	}
	void operator++()
	{
		Pre = Next(Pre);	
	}
	void operator--()
	{
		Pre = Prev(Pre);	
	}
};
int main(int argc,char *argv[])
{
	const char *str = "ABC##DE##F##G#H##";
	TdTree<char> wd('#');
	wd.CreatedTree(str);
	wd.ThreadInOrder();
	wd.InOrderNext();
	wd.InOrderPrev();
	Initerator<char> ww(wd);
	ww.First();
	while(!ww.IsDone())
	{
		std::cout << *ww << " ";
		++ww;
	}
	printf("\n");
	ww.Last();
	while(!ww.IsDone())
	{
		std::cout << *ww << " ";
		--ww;
	}
  return 0;
}

