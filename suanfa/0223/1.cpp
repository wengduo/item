/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年02月23日 星期二 13时54分56秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <stack>
#define END '#'
typedef int Status;  
typedef char ElemType;  // 二叉树结点元素类å=acp#onPopupPost()
typedef struct BiTNode{ // 二叉树结点结构  
  char data;            // 结点数据  
  struct BiTNode *lchild;        // 左孩子  
  struct BiTNode *rchild;        // 右孩子  
}BiTNode,*BiTree;  
#define Maxsize 100    
typedef struct _SqStack{
  BiTNode *value;  
  struct _SqStack *next;  
}SqStack;

SqStack * _BuySqStack()
{
  SqStack *tmp = (SqStack *)malloc(sizeof(SqStack));
  return tmp;
}
void InitSqStack(SqStack **phead)
{
  *phead = _BuySqStack();
  assert(NULL != *phead);

  (*phead)->next = NULL;
  (*phead)->value = NULL;
}

void PushSqStack(SqStack *phead,BiTNode *p)
{
  if(NULL != phead && NULL != p)
  {
    SqStack *tmp = _BuySqStack();
    assert(NULL != tmp);

    tmp->value = p;
    tmp->next = phead->next;
    phead->next = tmp;
  }
}

SqStack * PopSqStack(SqStack *phead)
{
  if(phead->next != NULL)
  {
    SqStack *tmp = phead->next;
    phead->next = phead->next->next;
    return tmp;
  }
  return NULL;
}

void DestorySqStack(SqStack **phead)
{
  free(*phead);
  *phead = NULL;
}

void LoopPreOrder(BiTNode *p)
{
  if(p != NULL)
  {
    std::stack<BiTNode *> s;
    s.push(p);
    while(!s.empty())
    {
      p = s.top();
      printf("%c",p->data);
      s.pop();
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
}

void LoopInOrder1(BiTNode *p) 
{
  if(p == NULL) return;
  std::stack<BiTNode *> s;
  while(p || !s.empty())
  {
    if(p)
    {
      s.push(p);
      p = p->lchild;
    }
    else
    {
      p = s.top();
      printf("%c",p->data);
      s.pop();
      p = p->rchild;
    }
  }
}

void LoopInOrder(BiTNode *p)
{
  SqStack *s = NULL;
  InitSqStack(&s);
  BiTNode *tmp1 = p;
  while(tmp1 || s->next)
  {
    if(tmp1)
    {
      PushSqStack(s,tmp1);
      tmp1 = tmp1->lchild;
    }
    else
    {
      SqStack *tmp = PopSqStack(s);
      printf("%c",tmp->value->data);
      tmp1 = tmp->value;
      tmp1 = tmp1->rchild;
      free(tmp);
    }
  }
}

void LoopPostOrder2(BiTNode *p)
{
  std::stack<std::pair<BiTNode *, bool> > s;
  s.push(std::make_pair(root, false));
  bool visited;
  while(!s.empty())
  {
    p = s.top().first;
    visited = s.top().second;
    s.pop();
    if(root == NULL)
      continue;
    if(visited)
    {
      printf("%c",p->data);
    }
    else
    {
      s.push(std::make_pair(p, true));
      s.push(std::make_pair(p->rchild, false));
      s.push(std::make_pair(p->lchild, false));
    }
  }
}

void LoopPostOrder1(BiTNode *p)
{
  BiTNode *flag = NULL;
  if(p == NULL) return;
  std::stack<BiTNode *> s;
  while(p || !s.empty())
  {
    while(p)
    {
      s.push(p);
      p = p->lchild;
    }
    p = s.top();s.pop();
    if(p->rchild == NULL || flag == p->rchild)
    {
      printf("%c",p->data);
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


void LoopPostOrder(BiTNode *b)
{
  BiTNode *st[Maxsize];
  BiTNode *p;
  int flag;
  int top=-1;
  if(b!=NULL)
  {
    do
    {
      while(b!=NULL)
      {
        top++;
        st[top]=b;
        b=b->lchild;
      }
      p=NULL;
      flag=1;
      while(top!=-1&&flag)
      {
        b=st[top];
        if(b->rchild==p)
        {
          printf("%c",b->data);
          top--;
          p=b;
        }
        else
        {
          b=b->rchild;
          flag=0;
        }
      }
    }while(top!=-1);
    printf("\n");
  }
}

void CreateBiTree(BiTNode ** const p)
{
  ElemType x;
  std::cin >> x;
  if(x != END)
  {
    *p = (BiTNode *)malloc(sizeof(BiTNode));
    (*p)->data = x;
    CreateBiTree(&(*p)->lchild);
    CreateBiTree(&(*p)->rchild);
  }
  else
  {
    *p = NULL;
  }
}

void PreOrder(BiTNode *p)
{
  if(NULL != p)
  {
    std::cout << p->data;
    PreOrder(p->lchild);
    PreOrder(p->rchild);
  }
}

void InOrder(BiTNode *p)
{
  if(NULL != p)
  {
    InOrder(p->lchild);
    std::cout << p->data;
    InOrder(p->rchild);
  }
}

void PostOrder(BiTNode *p)
{
  if(NULL != p)
  {
    PostOrder(p->lchild);
    PostOrder(p->rchild);
    std::cout << p->data;
  }
}

/* int size(BiTNode *p) */
// {
  // if(NULL == p) return 0;
  // else return Max
// }

// BiTNode * FindValue(BiTNode *p,ElemType x)
// {
  // if(NULL == p)
// }

int main(int argc,char *argv[])
{
  BiTree root = NULL;
  CreateBiTree(&root);
  printf("递归先序\n");
  PreOrder(root);
  printf("\n递归中序\n");
  InOrder(root);
  printf("\n递归后序\n");
  PostOrder(root);
  printf("\n非递归先序\n");
  LoopPreOrder(root);
  printf("\n非递归中序\n");
  LoopInOrder1(root);
  printf("\n");
  LoopInOrder(root);
  printf("\n非递归后序\n"); 
  LoopPostOrder2(root);
  printf("\n");
  LoopPostOrder1(root);
  printf("\n");
  LoopPostOrder(root);
  return 0;
}

