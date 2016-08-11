/*************************************************************************
    > File Name: 2.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月26日 星期二 11时10分05秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
class Test 
{
private:
  int value;
protected:
public:
  Test(int x = 0):value(x) {}
  ~Test(){};
  int GetValue() { return value;}
  int GetValue() const { return value;}

  int & GetRef() { return value;}
  const int & GetRef() const { return value;}

  int * GetPtr() { return &value;}
  const int * GetPtr() const { return &value;}  
};
int main(int argc,char *argv[]) 
{
  Test t1(10);
  const Test t2(20);
  int *a1 = t1.GetPtr();
  int *&b1 = t1.GetPtr();
  const int *&c1 = t1.GetPtr();
  int **p1 = &t1.GetPtr();

  int *a2 = t2.GetPtr();
  int *&b2 = t2.GetPtr();
  const int *&c2 = t2.GetPtr();
  const int **p2 = &t2.GetPtr();
  return 0;
} 
/* int main(int argc,char *argv[])  */
// {
  // Test t1(10);
  // const Test t2(20);
  // int a1 = t1.GetRef();
  // int &b1 = t1.GetRef();
  // const int &c1 = t1.GetRef();
  // int *p1 = &t1.GetRef();

  // int a2 = t2.GetRef();
  // //int &b2 = t2.GetRef();//要用常引用接收
  // const int &c2 = t2.GetRef();
  // const int *p2 = &t2.GetRef();//寄存器所指向的值为常量
  // return 0;
/* } */ 

//int main(int argc,char *argv[])  */
// {
  // Test t1(10);
  // const Test t2(20);
  // int a1 = t1.GetValue();
  // //int &b1 = t1.GetValue();//寄存器默认为常
  // const int &c1 = t1.GetValue();
  // //int *p1 = &t1.GetValue();//寄存器没法取引用

  // int a2 = t2.GetValue();
  // //int &b2 = t2.GetValue();
  // const int &c2 = t2.GetValue();
  // //int *p2 = &t2.GetValue();
  // return 0;
// } 

