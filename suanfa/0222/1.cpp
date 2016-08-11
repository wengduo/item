/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年02月22日 星期一 10时59分10秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#define OVERFLOW 0
struct Node
{
  char data;
  struct Node * lchild;
  struct Node * rchild;
};

typedef struct Node BiTNode;
typedef BiTNode * BiTree;

void CreateBiTree(BiTree &T)
{
  char ch;
  scanf("%c", &ch);      
    if (ch=='#') T=NULL;    
  else{
    if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) 
    {
      exit(OVERFLOW);
    }
    T->data = ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
  }
  return;
}
       
void PreOrderTraverse(BiTree T)
{
  if (T) 
  {
    std::cout<<T->data;
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
  }
  return;
}

void InOrderTraverse(BiTree T)
{
  if (T) 
  {
    InOrderTraverse(T->lchild);
    std::cout<<T->data;
    InOrderTraverse(T->rchild);
  }
  return;
}

void PostOrderTraverse(BiTree T)
{
  if (T) 
  {
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    std::cout<<T->data;
   }
   return;
}

int main()
{
  BiTree T=NULL;
                             
  std::cout << "请按先序顺序输入二叉树中的结点（其中，'#'表示空树）：" <<std::endl;
  CreateBiTree(T);
  std::cout << std::endl;
                                      
  std::cout << "先序遍历该二叉树得到的序列为：" <<std::endl;
  PreOrderTraverse(T);
  std::cout << std::endl <<std::endl;
  std::cout << "中序遍历该二叉树得到的序列为：" <<std::endl;
  InOrderTraverse(T);
  std::cout << std::endl <<std::endl;
  std::cout << "后序遍历该二叉树得到的序列为：" <<std::endl;
  PostOrderTraverse(T);
  std::cout << std::endl <<std::endl;

  return 0;
}









BiTNode * FindValue(BiTree *p,ElemType x)
{
  BiTNode *s = NULL;
  if(p != NULL && *p->data != x)
  {
    s = FindValue(p->lchild,x);
    if(s == NULL)
      s = FindValue(p->rchild,x);
  }
  return s;
}






BiTree * FindParent1(BiTree *ptr,BiTree *child)
{
  if(ptr != NULL)
  {
    if(ptr->lchild == child || ptr->rchild == child)
    {
      return ptr;
    }
    BiTree *s = NULL;
    s = FindParent1(ptr->lchild,child);
    if(s == NULL)
      s = FindParent1(ptr->rchild,child);
  }
  return NULL;
}

BiTree * FindParent(BiTree *ptr,BiTree *child)
{
  if(ptr != child && ptr != NULL && child != NULL)
  {
    return FindParent1(ptr,child);
  }
  return NULL;
}























/*
if(**pstr != END)
{
  s = _Buynode();
  s->data = **pstr;
  s->leftchild = CreateBiTree5(&++*pstr);
  s->rightchild = CreateBiTree5(&++*pstr);
}
*/


int FindIs(ElemType *is,int n,ElemType x)
{
  for(int i = 0;i < n;++i)
  {
    if(is[i] == x)
      return i;
  }
  return -1;
}

BiTNode * CreateBiTree2(ElemType *ps,ElemType *is,int n)
{
  BiTNode *s = NULL;
  if(ps != NULL && is != NULL && n > 0)
  {
    s = _Buynode();
    s->data = ps[0];
    int pos = FindIs(is,n,ps[0]);
    s->leftchild = CreateBiTree(ps+1,is,pos);
    s->rightchild = CreateBiTree(ps+pos+1,is+pos+1,n-pos-1);
  }
  return s;
}
































int Findls(ElemType *is,int n,ElemType x)
{
  for(int i = 0;i < n;++i)
  {
    if(is[i] == x)
      return i;
  }
  return -1;
}


BiTNode * CreateBiTree3(ElemType *is,ElemType *ls,int n)
{
  BiTNode *s = NULL;
  if(ls != NULL && is != NULL && n > 0)
  {
    s = _Buynode();
    s->data = ls[n-1];
    int pos = FindIs(is,n,ls[n-1]);
    if(pos == -1) exit(0);
    s->leftchild = CreateBiTree(ls+1,is,pos);
    s->rightchild = CreateBiTree(ls+pos+1,is+pos+1,n-pos-1);
  }
  return s;
}






