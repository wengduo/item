/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年02月19日 星期五 10时29分34秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#define END '#'
typedef char ElemType;

typedef struct _BtNode
{
  ElemType data;
  struct _BtNode *lchild;
  struct _BtNode *rchild;
}BtNode;

BtNode * MallocBtNode(ElemType x)
{
  BtNode *tmp = (BtNode *)malloc(sizeof(BtNode));
  assert(NULL != tmp);
  tmp->lchild = NULL;
  tmp->rchild = NULL;
  tmp->data = x;
  return tmp;
}

void ZPrint(BtNode *root)
{
  if(NULL != root)
  {
    ZPrint(root->lchild);
    std::cout << root->data << " ";
    ZPrint(root->rchild);
  }
}

void CreateTree(BtNode ** const s)
{
  ElemType x;
  std::cin >> x;
  if(END != x)
  {
    *s = MallocBtNode(x);
    *s->data = x;
    CreateTree(&(*s->lchild));
    CreateTree(&(*s->rchild));
  }
  else
  {
    *s = NULL;
  }
}

int main(int argc,char *argv[])
{
  ElemType ar[] = {'A','B','C','#','#','D','E','#','#','F','#','#','G','#','#','H'};
  BtNode *root = NULL;
  CreateTree(&root);
  ZPrint(root);
  return 0;
}

