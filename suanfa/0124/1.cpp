/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月24日 星期日 15时55分27秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
class A
{
private:
protected:
public:
  A(){
  
  };
  ~A(){
  
  };
  A & operator=(const A
  virtual void fun(int x = 0){
    std::cout << "A::fun" << x << std::endl;
  }
};
class B:public A
{
private:
  virtual void fun(int y = 10){
    std::cout << "B::fun" << y << std::endl;
  }
protected:
public:
  B(){
  
  };
  ~B(){
  
  };

};
int main(int argc,char *argv[])
{
  B p;
  A *p1 = &p;
  p1->fun();
  return 0;
}

