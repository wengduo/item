//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<cstdio>
//#include<cmath>
//#include<iostream>
//constexpr int mf = 10;
//int main()
//{
//	constexpr int k = mf + 1;
//	for (unsigned u = 10; u > 0; --u)
//	{
//		std::cout << u << std::endl;
//	}
//}
/*
void show(int i)
{
	std::cout << "show(int) " << i << std::endl;
	std::cout << "\n";
}
void show(float j)
{
	std::cout << "show(float) " << j << std::endl;
}
void show(double d)
{
	std::cout << "show(double) " << d << std::endl;
}
void show(double l,int r)
{
	std::cout << "show(double int) " << l<<" " << r << std::endl;
}
void show(int l, double r)
{
	std::cout << "show(int double) " << l << " " << r << std::endl;
}
int main()
{
	show(1);
	show(1.3);
	show(1, 4.3);
	show(4.3, 4);
	show(.5f);
	show(3L);
}

int main()
{
	int carrots;
	std::cin >> carrots;
	std::cout << "i have";
	std::cout << carrots;
	std::cout << "carrots.";
	std::cout << std::endl;
	carrots = carrots - 1;
	std::cout << "Cruch,crunch.Now I have " << carrots << " carrots. " << std::endl;

}


int  main()
{
	double h;
	std::cin >> h;
	double side;
	std::cout << "jjjj" << std::endl;
	side = sqrt(h);
	std::cout << side << std::endl;
}


int main()
{


	char buff[] = "jdsvjsjvsbvjs";
	printf("%c\n", buff[strlen(buff)-1]);
	return 0;
}*/

//#include<vld.h>
//int main()
//{
//	char **a = (char **)malloc(sizeof(char *)* 10);
//	char buff[7] = "hhlllk";
//	int i = 0;
//	while (i < 10)
//	{
//		char *p= (char *)malloc(sizeof(char)* strlen(buff) + 1);
//		strncpy(p, buff, strlen(buff) + 1);
//		a[i++] = p;
//	}
//	i = 0;
//	while (i<10)
//	{
//		printf("%s\n", a[i]);
//		free(a[i++]);
//	}
//	free(a);
////	return 0;
////}
//
//void my_buff(char *p, int i,char ch)
//{
//	int k = strlen(p);
//	i++;
//	while (i--)
//	{
//		p[k + 1] = p[k];
//		k--;
//	}
//	p[k+1] = ch;
//}
//
//void my_bdel(char *p, int i)
//{
//	int k = strlen(p);
//	int h = k - i;
//	while (k--)
//	{
//		p[h] = p[h + 1];
//		h++;
//	}
//	p[h] = 0;
//}
//int main()
//{
//	char buff[30] = "exit";
//
//	int i = 4;
//
//	my_bdel(buff, i-1);
//	printf("%s", buff);
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <string>
//using namespace std;
//class P
//{
//private:
//	int a;
//	int b;
//	std::string buff;
//public:
//	P(char *s)
//	{
//		//this->a = a;
//		//this->b = b;
//		//strncpy((char *)P::buff,s,strlen(s)+1);
//		this->buff = s;
//		a = 3;
//		b = 4;
//	}
//	void show()
//	{
//		printf("%d-%d-%s\n", a, b,buff);
//	}
//};
//int main()
//{
//	char *p = "kkkkk";
//	//P A(3,4);
//	P A(p);
//	A.show();
//}
/*void init(int x,int y = 2,int z= 3)
{
	std::cout << x << " " <<y <<" "<< z << std::endl;
}
int main()
{
	init(100, 80);
	init(4);
	init(33,8);
	return 0;
}*/
//#include <cstdio>
//#include <iostream>
//class A
//{
//private:
//	int length;
//	int width;
//public:
//	A(int length = 10, int width = 10);
//	A(const A &P);
//	void disp()
//	{
//		std::cout << length << " " << width << std::endl;
//	}
//};
//
//A::A(int length, int width)
//{
//	this->length = length;
//	this->width = width;
//	std::cout << "using normal constructor" << std::endl;
//}
//
//A::A(const A &p)
//{
//	this->length = 2 * p.length;
//	this->width = 2 * p.width;
//	std::cout << "using copy constructor" << std::endl;
//}
//
//void fun1(A p)
//{
//	p.disp();
//}
//
//A fun2()
//{
//	A p4(10, 30);
//	return p4;
//}
//
//int main()
//{
//	A p1(30, 40);
//	p1.disp();
//	A p2(p1);
//	p2.disp();
//	A p3 = p1;
//	p3.disp();
//	fun1(p1);
//	p2 = fun2();
//	p2.disp();
//	//A p5 = fun2();
//	//p5.disp();
//	return 0;
//}

//#include <cstdio>
//#include <iostream>
//using namespace std;
//class A
//{
//private:
//	float real;
//	float imag;
//	int a[100];
//	
//
//public:
//	A(float x = 0.0, float y = 0.0);
//	A(A &o);
//	A add(A &o);
//	A sub(A &o);
//	A mul(A &o);
//	A div(A &o);
//	friend ostream& operator<<(ostream &out, A &o);
//	friend A operator+(A &a,A &b);
//	friend A operator-(A &o,A &b);
//	friend A operator*(A &o,A &b);
//	friend A operator/(A &o,A &b);
//	friend A operator+(float a, A &o);
//	friend A operator-(float a, A &o);
//	friend A operator*(float a, A &o);
//	friend A operator/(float a, A &o);
//	friend A operator+(A &o, float a);
//	friend A operator-(A &o, float a);
//	friend A operator*(A &o, float a);
//	friend A operator/(A &o, float a);
//	void show();
//};
//A::A(float x, float y)
//{
//	cout << "A constry" << endl;
//	real = x;
//	imag = y;
//}
//A::A(A &o)
//{
//	cout << "copy constry" << endl;
//	real = o.real;
//	imag = o.imag;
//}
//ostream& operator<<(ostream &out,A &o)
//{
//	out<<o.real;
//	if (o.imag > 0)
//	{
//		out << "+";
//	}
//	if (o.imag != 0)
//	{
//		out << o.imag << "i\n";
//	}
//	return out;
//}
//
//
//A A::add(A &o)
//{
//	A t;
//	t.real = real + o.real;
//	t.imag = imag + o.imag;
//	return t;
//}
//
//A A::sub(A &o)
//{
//	A t;
//	t.real = real - o.real;
//	t.imag = imag - o.imag;
//	return t;
//}
//
//A A::mul(A &o)
//{
//	A t;
//	t.real = real * o.real - imag*o.imag;
//	t.imag = real*o.imag + imag*o.real;
//	return t;
//}
//
//A A::div(A &o)
//{
//	A temp;
//	double t;
//	t = 1 / (o.real*o.real + o.imag*o.imag);
//	temp.real = (real*o.real + imag*o.imag) * t;
//	temp.imag = (o.real*imag - real*o.imag) * t;
//	return temp;
//}
//
//A operator+(A &a,A &b)
//{
//	A t;
//	t.real = a.real + b.real;
//	t.imag = a.imag + b.imag;
//	return t;
//}
//
//A operator-(A &a,A &b)
//{
//	A t;
//	t.real = a.real - b.real;
//	t.imag = a.imag - b.imag;
//	return t;
//}
//A operator*(A &a,A &b)
//{
//	A t;
//	t.real = a.real * b.real - a.imag*b.imag;
//	t.imag = a.real*b.imag + a.imag*b.real;
//	return t;
//}
//A operator/(A &a,A &b)
//{
//	A temp;
//	double t;
//	t = 1 / (b.real*b.real + b.imag*b.imag);
//	temp.real = (a.real*b.real + a.imag*b.imag) * t;
//	temp.imag = (b.real*a.imag - a.real*b.imag) * t;
//	return temp;
//}
//
//A operator+(float a, A &o)
//{
//	cout << "operator+" << endl;
//	A t;
//	t.real = a + o.real;
//	t.imag = o.imag;
//	return t;
//}
//A operator-(float a, A &o)
//{
//	A t;
//	t.real = a - o.real;
//	t.imag = -o.imag;
//	return t;
//}
//A operator*(float a, A &o)
//{
//	A t;
//	t.real = a * o.real;
//	t.imag = a * o.imag;
//	return t;
//}
//A operator/(float a, A &o)
//{
//	A t(a, 0);
//	return t.div(o);
//}
//A operator+(A &o, float a)
//{
//	cout << "operator+" << endl;
//	A t;
//	t.real = a + o.real;
//	t.imag = o.imag;
//	return t;
//}
//A operator-(A &o, float a)
//{
//	A t;
//	t.real = o.real - a;
//	t.imag = o.imag;
//	return t;
//}
//A operator*(A &o, float a)
//{
//	A t;
//	t.real = a * o.real;
//	t.imag = a * o.imag;
//	return t;
//}
//A operator/(A &o, float a)
//{
//	A t;
//	t.real = o.real / a;
//	t.imag = o.imag / a;
//	return t;
//}
//void A::show()
//{
//	std::cout << real;
//	if (imag > 0)
//	{
//		std::cout << "+";
//	}
//	if (imag != 0)
//	{
//		std::cout << imag << "i\n";
//	}
//}
//
//int main()
//{
//	A p(2, 3);
//	A h(4, 6);
//	//cout << p;
//	//p.show();
//	//h.show();
//	A p1 = p + 1;
//	p1.show();
	//A p2 = 1 - p ;
	//p2.show();
	//A p3 = 2 * p;
	//p3.show();
	//A p4 = 2 / p;
	//p4.show();
	/*A p1 = p + 1;
	p1.show();
	A p2 = p - 1;
	p2.show();
	A p3 = p * 2;
	p3.show();
	A p4 = p / 2;
	p4.show();*/
	//A p1 = p + h;
	//p1.show();
	//A p2 = p - h;
	//p2.show();
	//A p3 = p * h;
	//p3.show();
	//A p4 = p / h;
	//p4.show();
	/*A p1 = p.add(p);
	p1.show();
	A p2 = p.sub(p);
	p2.show();
	printf("\n");
	A p3 = p.mul(p);
	p3.show();
	A p4 = p.div(p);
	p4.show();
	printf("\n");*/

	//return 0;
//}