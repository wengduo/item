/*************************************************************************
    > File Name: 2.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月28日 星期四 17时36分27秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>


int find_rk(Node *p,int k)
{
  if(k > 0 && k < list_length(p))
  {
    Node *tmp = p;
    while(k--)
    {
      p = p->next;
    }
    while(p->next != NULL)
    {
      tmp = tmp->next;
      p = p->next;
    }
    return tmp->data;
  }
}







void reverse(List list,Node *s)
{
  Node *tmp = s->next;
  if(tmp == NULL)
  {
    return;
  }
  else
  {
    s->next = s->next->next;
    push_fornt(list,tmp->date);
    reverse(list,s);
  }
}

void reverse_list(List list)
{
  Node *p  = list.head->next;
  if(list.cursize >= 2)
  {
    reverse(list,p);
  }
}







void reverse_list(List list)
{
  Node *p = list.head->next;
  while(p != NULL)
  {
    Node *tmp = p ->next;
    if(tmp == NULL)
    {
      break;
    }
    else
    {
      p->next = p->next->next;
      push_back(list,tmp->date);
    }
  }
}



















NODE * find(NODE *p,ElemType x)
{
  if(p->date != x)
  {
    if(NULL != p->next)
    {
      p = p->next;
      return find(p,x);
    }
    else
    {
      return NULL;
    }
  }
  else
  {
    return p;
  }
}

NODE * findvalue(List *list,ElemType x)
{
  Node *p = list->head->next;
  if(NULL != p)
  {
    return find(p,x);
  }
  return NULL;
}






bool push_fornt(List *list,int p)
{
  if(NULL == list)
  {
    return false;
  }

  NODE *tmp = _BuyNode();
  tmp->date = p;

  tmp->next = list->head;
  list->head = tmp;
  list->cursize++;
  
  return true;
}
/* int count = 0; */
// int count1 = 0;
// int count2 = 0;

// int ret[2] = {1,1};
// int fac(int n){
  // count++;
  // if(n <= 2)
  // {
    // return ret[1];
  // }
  // else
  // {
    // ret[1] = ret[0] + ret[1];
    // ret[0] = ret[1] - ret[0];
    // return fac(--n);
  // }
// }
// int fac1(int n){
  // count1++;
  // if(n <= 2){
    // return 1;
  // } else{
    // return fac1(n-1)+fac1(n-2);
  // }
// }
// int fac3(int n){
  // int m = 1;
  // int m1 = 1;
  // if(n <= 2){
    // return 1;
  // } else {
    // for(int i = 2;i < n;++i){
      // m1 = m + m1;
      // m = m1 - m;
    // }
  // }
  // return m1;
/* } */
/* void Print_Array(int *br,int *const p){ */
  // if(NULL == br) return;
  // if(*p > 0)
  // {
    // Print_Array(br,&--*p);
    // std::cout << br[*p] << " ";
    // //std::cout << *br << " ";
    // //Print_Array(++br,--n);
  // }
/* } */
/* void Print_Array(int *br,int &n){  */
  // if(NULL == br) return;
  // if(n > 0)
  // {
    // Print_Array(br,n--);
    // std::cout << br[n] << " ";
    // //std::cout << *br << " ";
    // //Print_Array(++br,--n);
  // }
/* } */ 
int k = 0;
int findvalue(int *ar,int n,int x)
{
  if(NULL == ar || n < 0) return -1;
  if(*ar == x)
  {
    return k;
  } 
  else 
  {
    k++;
    return findvalue(++ar,--n,x);
  }
}

/* bool head_insert(NODE *phead,int val) */
// {
  // if(NULL == phead)
  // {
    // return false;
  // }
  // NODE *tmp = _BuyNode();
  // tmp->date = val;

  // tmp->next = phead;
  // phead = tmp;

  // return true;
/* } */
void Print(NODE *head)
{
  std::cout >> head->date >> " ";
  if(NULL != head->next)
  {
    Print(head->next);
  }
}

void Print_list(NODE *phead)
{
  if(NULL != phead && NULL != phead->next)
  {
    Print(phead->next);
  }
}


int main(int argc,char *argv[])
{
  /* printf("%d-%d\n",count,fac(20)); */
  // printf("%d-%d\n",count1,fac1(20));
  /* printf("%d-%d\n",count2,fac3(20)); */
  int ar[] = {11,21,31};
  int n = sizeof(ar)/sizeof(ar[0]);
  //int x;
  //std::cin >> x;
  //Print_Array(ar,&n);
  //printf("%d\n",findvalue(ar,n,x));
  return 0;
}

