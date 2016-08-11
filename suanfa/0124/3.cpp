/*************************************************************************
    > File Name: 3.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月25日 星期一 11时34分34秒
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
  Test(int x=0):value(x) {
  
  };
  ~Test(){
  
  };
  int GetValue() {
    return value;
  }
  /* int GetValue() const { */
    // return value;
  /* } */
  int & GetRef() {
    return value;
  }// *const this
  /* int & GetRef() const {  */
    // return value;
  /* } */ 
  int * GetPtr() {
    return &value;
  }
  /* int * GetPtr() const {  */
    // return &value;
  /* } */ 
};
int main(int argc,char *argv[])
{
  Test t1(10);
  const Test t2(20); 
  int a1 = t1.GetValue(); 
  //int &b1 = t1.GetValue(); 
  const int &c1 = t1.GetValue();
  int *p1 = &*(int *)t1.GetValue();    
  printf("%d\n",t1.GetValue());
  return 0;
}

