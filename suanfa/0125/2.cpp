/*************************************************************************
    > File Name: 2.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月25日 星期一 16时12分27秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
class A
{
private:
  int *p;
  mutable int value;
protected:
public:
  A(int x = 0):p(new int(x)) {
  
  };
  ~A(){
    delete p;
  };
  void fun1() {
    *p = 100;
    delete p;
    p = new int(20);
  }
  void fun2() const {
    *p = 100;
    delete p;
    //int p2 = 5;
    //value = &p2;
    //const int *&p2 = &value;
    value = 5;
    ((A*)
    //*p2 = 5;
    //p = new int(20);
  }
};
int main(int argc,char *argv[])
{
  A t;
  t.fun1();
  t.fun2();
  return 0;
}

