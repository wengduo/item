/*************************************************************************
    > File Name: trie.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月20日 星期五 21时32分17秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#define Max 27

class Trie
{
protected:
	struct TNode
	{
		int count;
		TNode *data[Max];
	};
private:
	TNode * _BuyNode()
	{
		TNode *tmp = (TNode *)malloc(sizeof(TNode));
		memset(tmp,0,sizeof(TNode));
		return tmp;
	}
public:
	Trie():root(NULL){};
	bool Insert(const char *ptr)
	{

	}
	~Trie();
	
private:
	TNode *root;
};

int main(int argc,char *argv[])
{
	Trie wd;

	return 0;
}
