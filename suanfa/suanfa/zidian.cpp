/*************************************************************************
    > File Name: zidian.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月04日 星期三 21时30分00秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <queue>
#define Max 27

class DictTree
{
private:
	struct TNode
	{
		int count;
		char *pdata;
		TNode *next[Max];
	};
	TNode * _BuyNode()
	{
		TNode *tmp = new TNode;
		memset(tmp,0,sizeof(TNode));
		return tmp;
	}
	bool Insert_next(TNode *rt,const char *ptr)
	{
		bool res = false;
		TNode *p = NULL;
		const char *ps = ptr;
		int k = 0;
		while(*ps)
		{
			k = *ps-'a'+1;
			if(rt->next[k] == NULL)
			{
				p = _BuyNode();
				rt->next[k] = p;
			}
			rt->count++;
			ps++;
			rt = rt->next[k];
		}
		rt->pdata = (char *)malloc(sizeof(char)*(strlen(ptr)+1));
		strcpy(rt->pdata,ptr);
		return res;
	}
	static bool Ascal(const char *ptr)
	{
		bool res = false;
		if(ptr != NULL && strlen(ptr) > 0 && strncmp(ptr," ",1) != 0)
		{
			bool tag = true;
			const char *p = ptr;
			while(*p)
			{
				if(*p < 'a' || *p > 'z')
				{
					tag = false;
					break;
				}
				p++;
			}
			if(tag) res = true;
		}
		return res;
	}
	static void d_show(TNode *ptr)
	{
		if(ptr->pdata != NULL)
		{
			std::cout << ptr->pdata << ":" << ptr->count << std::endl;
		}
		if(ptr->count == 0) return;
		int i = 1;
		while(i < Max)
		{
			if(ptr->next[i] != NULL)
			{
				d_show(ptr->next[i]);
			}
			i++;
		}
	}
public:
	DictTree();
	bool Insert(const char *ptr = NULL);
	void show();
private:
	TNode *root;	
	std::queue<char> st;
};

DictTree::DictTree()
{
	root = _BuyNode();
}

bool DictTree::Insert(const char *ptr)
{
	bool res = false;
	if(Ascal(ptr))
	{
		res = Insert_next(root,ptr);
	}
	return res;
}

void DictTree::show()
{
	if(root->count != 0)
	{
		d_show(root);
	}
}

int main(int argc,char *argv[])
{
	DictTree root;
	root.Insert("sdcv");
	root.Insert("goods");
	root.Insert("good");
	root.show();
	return 0;
}
