/*************************************************************************
    > File Name: String.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月24日 星期二 11时18分22秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
using namespace std;

class String
{
	friend ostream & operator<<(ostream &os,String &o);
	friend istream & operator>>(istream &os,String &o);
protected:
	struct Date
	{
		int count;
		size_t size;
		char date[0];
	};
public:
	String(const char *ptr = NULL)
	{
		printf("kkkkkkkkkkk\n");
		root = NULL;
		if(ptr != NULL)
		{
			root = (Date *)malloc(sizeof(Date));
			root->count = 1;
			root->size = strlen(ptr);
			strcpy(root->date,ptr);
		}
	}
	String(const String &o)
	{
		root = o.root;
		root->count++;
	}
	String & operator=(const String &o)
	{
		if(&o != this)
		{
			if(this->root != NULL)
				delete root;
			root = o.root;
			root->count++;
		}
		return *this;
	}
	size_t size() const
	{
		if(root != NULL)
			return root->count;
		else
			return 0;
	}
	~String()
	{
		if(root != NULL)
			cout << root->count << "lllll\n"; 
		if(root != NULL && --root->count == 0)
		{
			printf("pppp\n");
			free(root);
			root = NULL;
		}
	}
private:
	Date *root;
};

ostream & operator<<(ostream &os,String &o)
{
	os << o.root->date;
	return os;
}
istream & operator>>(istream &os,String &o)
{
	char temp[256] = {0};
	os >> temp;
	o = temp;
	return os;
}
int main(int argc,char *argv[])
{
	String d("hello");
	String a(d);
	printf("lllllllll\n");
	String c = a;
	//d.show();
	String b;
	cin >> b;
	cout << d << d.size() << "\n"<< a << a.size() << "\n" << c << c.size() << "\n" << b << b.size() << "\n";
	printf("%d\n",(int)sizeof(d));
	
	return 0;
}
