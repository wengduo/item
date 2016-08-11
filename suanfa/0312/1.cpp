/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年03月03日 星期四 18时42分02秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <stack>
struct BtNode
{
  int num;
  BtNoded *value;
};
void NicePastOrder(BtNode *p)
{
  if(p == NULL) return;
  std::stack<BtNode *> st;
  st.push(p);
  while(st.empty())
  {

    
  }
}
int main(int argc,char *argv[])
{

  return 0;
}

