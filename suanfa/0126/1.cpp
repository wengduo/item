/*************************************************************************
    > File Name: 1.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月26日 星期二 10时08分41秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <new>
#include <cstring>

class Int
{
private:  
protected:
public:
  int value;
  explicit Int(int x = 0):value(x) {
    std::cout << "Create Int:" << this << std::endl;
  };

  Int(const Int &it):value(it.value) {
    std::cout << "Copy Create Int:"<< this << std::endl;
  }

  Int &operator=(const Int &it) {
    if(this != &it)
    {
      value = it.value;
    }
    return *this;
  }

  Int &operator++() {
    value++;
    return *this;
  }

  Int operator++(int) {
    return Int(value++);
  }

  Int operator--() {
    value--;
    return *this;
  }

  Int operator--(int) {
    return Int(value--);
  }

  Int operator+(const Int &it) const {
    return Int(it.value+value);
  }

  Int operator+(const int x) const {
    return Int(value+x);
  }

  operator int() const {
    return value;
  }

  ~Int(){
    std::cout << "Destory Int:" << std::endl;
  };
  
};
int main(int argc,char *argv[])
{
  Int p(9);
  assert(p.value == 9);
  Int p1(p);
  assert(p1.value == 9);
  Int p2;
  assert(p2.value == 0);
  p2 = p;
  assert(p2.value == p.value);
  
  assert((++p2).value == 10);

  assert((p2++).value == 10);
  
  assert((--p2).value == 10);

  assert((p2--).value == 10);
  
  assert((p2+p).value == 18);

  assert((p2+4).value == 13);

  assert(int(p2) == 9);
	
	Int c;
	c = p+p1;
	assert(c.value == 18);
	Int a(0);
	a = a++ + 1;// a operator++(a,int) + 1
	assert(a.value == 1);

  int b = 0;
  printf("%d %d %d\n",b++,++b,b++);
  printf("%d\n",b);


  printf("all pass\n");
  return 0;
}

