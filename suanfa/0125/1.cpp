/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月25日 星期一 14时47分41秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
class Test 
{
  int *ptr;
public:
  Test(int x=0):ptr(new int(x)) {}
  ~Test() {delete ptr;}
  int GetValue() { return *ptr;}
  int GetValue() const { return *ptr;}

  int & GetRef() { return *ptr;} 
  int & GetRef() const { return *ptr;}

  int * GetPtr() { return ptr;}
  int * GetPtr() const { return ptr;}

  int *& GetRPtr() { return ptr;}
  int *const & GetRPtr() const { return ptr;}

  // int ** GetPPtr() { return &ptr;}
  // int ** GetPPtr() const { return &ptr;}

};

/* class Test  */
// {
  // int value;
// public:
  // Test(int x=0):value(x) {}
  // ~Test() {}
  // int GetValue() { return value;}
  // int GetValue() const { return value;}

  // int & GetRef() { return value;} 
  // int & GetRef() const { return value;}

  // int * GetPtr() { return &value;}
  // const int * GetPtr() const { return &value;} 
// };

int main()
{
  Test t1(10);
  const Test t2(20);
  int *a1        = t1.GetRPtr();//0
  int *&b1       = t1.GetPtr();//
  const int *&c1 = t1.GetPtr();
  int **p1       = &t1.GetRPtr();
  
  int *a2        = t2.GetRPtr();
  int *&b2       = t2.GetRPtr();
  const int *&c2 = t2.GetRPtr();
  int **p2       = &t2.GetRPtr();
  return 0;
}
