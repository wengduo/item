/*************************************************************************
    > File Name: 3.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com 
    > Created Time: 2016年01月28日 星期四 14时25分33秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>

class Test
{
private:
	int *ptr;
protected:
public:
	Test(int x=0):ptr(new int(x)) {}
	~Test(){
		delete ptr;
	};
	int GetValue() { return *ptr;}
	int GetValue() const { return *ptr;}

	int & GetRef() { return *ptr;}
	int & GetRef() const { return *ptr;}

	int * GetPtr() { return ptr;}
	int * GetPtr() const { return ptr;}

	int *& GetRPtr() { return ptr;}
	int *& GetRPtr() const { return ptr;}
	
	//int ** GetRPtr() { return &ptr;}
	//int ** GetRPtr() { return &ptr;}
};
int main(int argc,char *argv[])  
{
	Test t1(10);
	const Test t2(20);
	int a1 = t1.GetRPtr();
	int &b1 = t1.GetRPtr();
	const int &c1 = t1.GetRPtr();
	int *p1 = &t1.GetRPtr();

	int a2 = t2.GetRPtr();
	int &b2 = t2.GetRPtr();
	const int &c2 = t2.GetRPtr();
	int *p2 = &t2.GetRPtr();
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
	// int &b2 = t2.GetRef();
	// const int &c2 = t2.GetRef();
	// int *p2 = &t2.GetRef();
	// return 0;
/* } */
/* int main(int argc,char *argv[])  */
// {
	// Test t1(10);
	// const Test t2(20);
	// int a1 = t1.GetValue();
	// int &b1 = t1.GetValue();//
	// const int &c1 = t1.GetValue();
	// int *p1 = &t1.GetValue();//

	// int a2 = t2.GetValue();
	// int &b2 = t2.GetValue();//
	// const int &c2 = t2.GetValue();
	// int *p2 = &t2.GetValue();//
	// return 0;
// }

