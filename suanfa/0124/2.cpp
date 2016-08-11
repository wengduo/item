/*************************************************************************
    > File Name: 2.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月24日 星期日 20时45分08秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

int main(int argc,char *argv[])
{
  int a = 10;
  int const *p = &a;
  //int *p1 = p;
  int const *p2 = p;
  const int *p3 = p;
  //int *const p4 = p;
  const int *const p5 = p;
  return 0;
}

