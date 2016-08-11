/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月04日 星期五 10时01分08秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <stack>
#include <cmath>
#include <queue>

template <class T>
const T & Max(const T &a,const T &b)
{
  return a>b?a:b;
}

#define END '#'
typedef char Type;
typedef struct _BtNode
{
  Type data;
  struct _BtNode *lchild;
  struct _BtNode *rchild;
}BtNode;

class Node
{
public:
  int num;
  BtNode *value;
  Node(BtNode *p = NULL):num(0),value(p){};
};

BtNode *BuyNode()
{
  return (BtNode *)malloc(sizeof(BtNode));
}

BtNode *CreateBTNode(const char *&str)
{
  BtNode *root = NULL;
  if(*str != END)
  {
    root = BuyNode();
    root->data = *str;
    root->lchild = CreateBTNode(++str);
    root->rchild = CreateBTNode(++str);
  }
  return root;
}

void PreOrder(BtNode *p)
{
  if(p != NULL)
  {
    std::cout << p->data << " ";
    PreOrder(p->lchild);
    PreOrder(p->rchild);
  }
}

void PreOrder1(BtNode *p)
{
  if(p == NULL) return;
  std::stack<Node> s;
  s.push(Node(p));
  while(!s.empty())
  {
    Node node = s.top();s.pop();
    if(++node.num == 1)
    {
      std::cout << node.value->data << " ";
      if(node.value->rchild != NULL)
      {
        s.push(Node(node.value->rchild));
      }
      if(node.num == 1 && node.value->lchild != NULL)
      {
        s.push(Node(node.value->lchild));
      }
    }
  }
}

void PreOrder2(BtNode *p)
{
  std::stack<BtNode *> s;
  s.push(p);
  while(!s.empty())
  {
    p = s.top();s.pop();
    std::cout << p->data << " ";
    if(p->rchild != NULL)
    {
      s.push(p->rchild);
    }
    if(p->lchild != NULL)
    {
      s.push(p->lchild);
    }
  }
}

void InOrder(BtNode *p)
{
  if(p != NULL)
  {
    InOrder(p->lchild);
    std::cout << p->data << " ";
    InOrder(p->rchild); 
  }
}

void InOrder1(BtNode *p)
{
  if(p == NULL) return;
  std::stack<Node> s;
  s.push(Node(p));
  while(!s.empty())
  {
    Node node = s.top();s.pop();
    if(++node.num == 2)
    {
      std::cout << node.value->data << " ";
      if(node.value->rchild != NULL)
      {
        s.push(Node(node.value->rchild));
      }
    }
    else
    {
      s.push(node);
      if(node.num == 1 && node.value->lchild != NULL)
      {
        s.push(Node(node.value->lchild));
      }
    }
  }
}

void InOrder2(BtNode *p)
{
  if(p == NULL) return;
  std::stack<BtNode *> s;
  while(!s.empty() || p != NULL)
  {
    while(p != NULL)
    {
      s.push(p);
      p = p->lchild;
    }
    p = s.top();s.pop();
    std::cout << p->data << " ";
    p = p->rchild;
  }
}

void PostOrder(BtNode *p)
{
  if(p != NULL)
  {
    PostOrder(p->lchild);
    PostOrder(p->rchild); 
    std::cout << p->data << " ";
  }
}

void PostOrder1(BtNode *p)
{
  std::stack<BtNode *> s;
  BtNode *flag = NULL;
  while(!s.empty() || p != NULL)
  {
    while(p != NULL)
    {
      s.push(p);
      p = p->lchild;
    }
    p = s.top();s.pop();
    if(p->rchild == NULL || p->rchild == flag)
    {
      std::cout << p->data << " ";
      flag = p;
      p = NULL;
    }
    else
    {
      s.push(p);
      p = p->rchild;
    }
  }
}

void PostOrder2(BtNode *p)
{
  if(p == NULL) return;
  std::stack<Node> s;
  s.push(Node(p));
  while(!s.empty())
  {
    Node node = s.top();s.pop();
    if(++node.num == 3)
    {
      std::cout << node.value->data << " ";
    }
    else
    {
      s.push(node);
      if(node.num == 1 && node.value->lchild != NULL)
      {
        s.push(Node(node.value->lchild));
      }
      else if(node.num == 2 && node.value->rchild != NULL)
      {
        s.push(Node(node.value->rchild));
      }
    }
  }
}

void PostOrder3(BtNode *p)
{
  if(p == NULL) return;
  std::stack<BtNode *> s1;
  std::stack<BtNode *> s2;
  s1.push(p);
  while(!s1.empty())
  {
    p = s1.top();s1.pop();
    s2.push(p);
    if(p->lchild != NULL)
    {
      s1.push(p->lchild);
    }
    if(p->rchild != NULL)
    {
      s1.push(p->rchild);
    }
  }
  while(!s2.empty())
  {
    p = s2.top();s2.pop();
    std::cout << p->data << " ";
  }
}

void LevelOrder(BtNode *p)
{
	if(p == NULL) return;
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
		if(p->rchild != NULL)
		{
			s.push(p->rchild);
		}
	}
}

void GetKleverData(BtNode *p,int k)
{
	if(p == NULL || k <= 0) return;
	if(p != NULL && k == 1) 
	{
		std::cout << p->data << " ";
		return;
	}
	GetKleverData(p->lchild,k-1);
	GetKleverData(p->rchild,k-1);
}

int Depth(BtNode *p)
{
  if(p == NULL) return 0;
  else return Max(Depth(p->lchild),Depth(p->rchild))+1;
}

void LevelOrder1(BtNode *p)
{
	if(NULL == p) return;
	int k = Depth(p);
	for(int i = 0;i <= k;++i)
	{
		GetKleverData(p,i);
	}
}

int Size(BtNode *p)
{
  if(p == NULL) return 0;
  return Size(p->lchild)+Size(p->rchild)+1;
}

int GetKlever(BtNode *p,int k)
{
	if(p == NULL || k <= 0) return 0;
	if(p != NULL && k == 1) return 1;
	return GetKlever(p->lchild,k-1)+GetKlever(p->rchild,k-1);
}

void IsCompleteTree(BtNode *p)
{
	if(Size(p) == pow(2,Depth(p))-1)
		printf("该树为满二叉树\n");
	else
		printf("该树不是满二叉树\n");
}

void IsComplete(BtNode *p)
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

void Destory(BtNode *p)
{
	if(p != NULL)
	{
		Destory(p->lchild);
		Destory(p->rchild);
		free(p);
	}
}

void longestPathUtil(BtNode *p, int& left_len, int& right_len, int& max_len)  
{  
	if(p == NULL)  
	{  
	  left_len = 0;  
	  right_len = 0;  
	  max_len = 0;  
	  return;  
	}  
	 
	int left_len1, right_len1, left_len2, right_len2;  
	longestPathUtil(p->lchild, left_len1, right_len1, max_len);  
	longestPathUtil(p->rchild, left_len2, right_len2, max_len);  
							  
	left_len = 1+Max(left_len1, right_len1);  
	right_len = 1+Max(left_len2, right_len2);  
	max_len = Max(left_len+right_len-1, max_len);   
}  

void longestPath(BtNode *p)  
{  
	int left_len, right_len, max_len;  
	longestPathUtil(p, left_len, right_len, max_len);  
	printf("%d\n",max_len);  
}  

int main(int argc,char *argv[])
{
  const char *str ="ABC##DE##F##G#H##";
	//const char *str ="AB###";
  BtNode *root = CreateBTNode(str);
  PreOrder(root);
  printf("\n");
  PreOrder1(root);
  printf("\n");
  PreOrder2(root);
  printf("\n");
  InOrder(root);
  printf("\n");
  InOrder1(root);
  printf("\n");
  InOrder2(root);
  printf("\n");
  PostOrder(root);
  printf("\n");
  PostOrder1(root);
  printf("\n");
  PostOrder2(root);
  printf("\n");
  PostOrder3(root);
  printf("\n");
	LevelOrder(root);
	printf("\n");
	LevelOrder1(root);
	printf("\n");
  printf("%d\n",Depth(root));
  printf("%d\n",Size(root));
	GetKleverData(root,5);
	printf("%d\n",GetKlever(root,5));
	IsCompleteTree(root);
	IsComplete(root);
	longestPath(root);
	Destory(root);
	printf("摧毁成功\n");
  return 0;
}

