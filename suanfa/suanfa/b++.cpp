/*************************************************************************
    > File Name: b+.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月01日 星期日 14时53分43秒
 ************************************************************************/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
#define M 5 
#define LEAFMAX  M      // 5
#define LEAFMIN  (M/2+1) // 3

#define BRCHMAX  (M-1)
#define BRCHMIN  (M/2)
typedef enum{LEAF = 0,BRCH = 1} NodeType;
typedef int KeyType;
typedef struct {}Record;
typedef struct BPNode
{
	int num;
	BPNode *parent;
	NodeType utype;// LEAF BRCH
	KeyType data[M+1];
	union
	{
		struct
		{
			Record *recptr[M+1];
			BPNode *prev,*next;
		};
		BPNode *sub[M+1];
	};
}BPNode;

typedef struct
{
	BPNode *root;
	BPNode *first;
}BPTree;

typedef struct
{
	BPNode *pnode;
	int    index;
	bool   tag;
}Result;

BPNode * _Buynode()
{
	BPNode * s = (BPNode *)malloc(sizeof(BPNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BPNode));
	return s;
}
void _Freenode(BPNode *p)
{
	free(p);
}
BPNode * _BuyLeaf()
{
	BPNode *s = _Buynode();
	s->utype = LEAF;
	return s;
}

void Init_BPTree(BPTree *ptree)
{
	ptree->first = ptree->root = NULL;
}

Result Find(BPNode *ptr,KeyType kx)
{
	Result res={NULL,-1,false};
	int i = ptr->num-1;
	while(i>= 0 && kx < ptr->data[i]) --i;
	res.pnode = ptr;
	res.index = i;
	if(i>=0 && kx == ptr->data[i])
	{
		res.tag = true;
	}else if(i< 0 && ptr->prev != NULL)
	{
		ptr = ptr->prev;
		res.pnode = ptr;
		res.index = ptr->num-1;
	}
	return res;
}

Result FindFirst(BPNode *ptr,KeyType kx)
{
	Result res={NULL,-1,false};
	while(ptr != NULL && 
		   ptr->next != NULL  &&
		    kx > ptr->data[ptr->num-1])
	{
		ptr = ptr->next;
	}
	if(ptr != NULL)
	{
		res = Find(ptr,kx);
	}
	return res;
	
}

Result FindRoot(BPNode *ptr,KeyType kx)
{
	Result res = {NULL,-1,false};
	while(ptr != NULL && ptr->utype != LEAF)
	{
		int i = ptr->num;
		ptr->data[0] = kx;
		while(kx < ptr->data[i]) --i;
		ptr = ptr->sub[i];
	}
	if(ptr != NULL)
	{
		res = Find(ptr,kx);
	}
	return res;
}

KeyType Move_Brch(BPNode *ptr,BPNode *s)
{
	int i = BRCHMIN+1;
	int j = 0;
	for(;i <= M;++i,++j)
	{
		s->data[j] = ptr->data[i];
		s->sub[j] = ptr->sub[i];
		s->sub[j]->parent = s;
	}
	ptr->num = BRCHMIN;
	s->num = BRCHMIN;
	return s->data[0];
}

KeyType Move_Leaf(BPNode *ptr,BPNode *s)
{
	int i = LEAFMIN;
	int j = 0;
	for(;i < ptr->num;++i,++j)
	{
		s->data[j] = ptr->data[i];
		s->recptr[j] = ptr->recptr[i];
	}
	ptr->num = LEAFMIN;
	s->num = LEAFMIN;
	s->next = ptr->next;
	s->prev = ptr;
	ptr->next = s;
	if(s->next != NULL)
		s->next->prev = s;
	return s->data[0];
}

void Insert_Brch_Item(BPNode *p,KeyType kx,BPNode *s)
{
	p->data[0] = kx;
	int i = 0;
	for(i = p->num;kx < p->data[i];--i)
	{
		p->data[i+1] = p->data[i];
		p->sub[i+1] = p->sub[i];
	}
	p->data[i+1] = kx;
	p->sub[i+1] = s;
	s->parent = p;
	p->num+=1;
}

void Splice_Breh(BPTree *ptr,BPNode *p)
{
	BPNode *s = _Buynode();
	s->utype = BRCH;
	KeyType kx = Move_Brch(p,s);
	if(p->parent == NULL)
	{
		ptr->root = _Buynode();
		ptr->root->utype = BRCH;
		ptr->root->data[1] = kx;
		ptr->root->sub[0] = p;
		ptr->root->sub[1] = s;
		ptr->root->num = 1;
		s->parent = ptr->root;
		p->parent = ptr->root;
	}
	else
	{
		Insert_Brch_Item(p->parent,kx,s);
		if(p->parent->num > BRCHMAX)
		{
			Splice_Breh(ptr,p->parent);
		}
	}
}

void Splice_Leaf(BPTree *ptr,BPNode *p)
{
	BPNode *s = _BuyLeaf();
	s->next = s->prev = NULL;

	KeyType kx = Move_Leaf(p,s);
	if(p->parent == NULL)
	{
		ptr->root = _Buynode();
		ptr->root->utype = BRCH;
		ptr->root->data[1] = kx;
		ptr->root->sub[0] = p;
		ptr->root->sub[1] = s;
		ptr->root->num = 1;
		p->parent = ptr->root;
		s->parent = ptr->root;
	}
	else
	{
		Insert_Brch_Item(p->parent,kx,s);
		if(p->parent->num > BRCHMAX)
		{
			Splice_Breh(ptr,p->parent);
		}
	}
}
void Insert_Leaf_Item(BPNode *ptr,int pos,KeyType kx,Record *rec)
{
	for(int i = ptr->num-1; i>pos; --i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->recptr[i+1] = ptr->recptr[i];
	}
	ptr->data[pos+1] = kx;
	ptr->recptr[pos+1] = rec;
	ptr->num+=1;
}

Result Findpa(BPNode *ptr,KeyType kx)
{
	Result res = {NULL,-1,false};
	BPNode *pa = ptr->parent;

	int i = pa->num;
	while(i > 0)
	{
		if(pa->data[i] == kx)
		{
			res.pnode = pa;
			res.index = i;
			res.tag = true;
		}
		i--;
	}
	if(res.pnode == NULL) 
	{
		if(pa->parent == NULL) 
		{
			printf("nciancinaicnsibncii%d\n",kx);
			exit(-1);
		}
		return Findpa(pa,kx);
	}
	else
		return res;
}
void Move_Leaf_left(BPNode *ptr,int pos)
{
	for(int i = pos;i < ptr->num-1;++i)
	{
		ptr->data[i] = ptr->data[i+1];
		ptr->recptr[i] = ptr->recptr[i+1];
	}
	ptr->num -= 1;
}

void Move_Leaf_right(BPNode *ptr,int pos)
{
	for(int i = ptr->num-1;i >= 0;--i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->recptr[i+1] = ptr->recptr[i];
	}
	ptr->num += 1;
}

void Adjust_Leaf(BPTree *ptree,BPNode *ptr)
{
	Result res;
	if(ptr->next != NULL && ptr->next->num < LEAFMAX)
	{
		res = Findpa(ptr->next,ptr->next->data[0]);
		res.pnode->data[res.index] = ptr->data[ptr->num-1];
		Move_Leaf_right(ptr->next,0);
		ptr->next->data[0] = ptr->data[ptr->num-1];
		ptr->next->recptr[0] = ptr->recptr[ptr->num-1];
		ptr->num -= 1;
	}
	else if(ptr->prev != NULL && ptr->prev->num < LEAFMAX)
	{
		res = Findpa(ptr,ptr->data[0]);
		res.pnode->data[res.index] = ptr->data[1];
		ptr->prev->data[ptr->prev->num] = ptr->data[0];
		ptr->prev->recptr[ptr->prev->num] = ptr->recptr[0];
		ptr->prev->num += 1;
		Move_Leaf_left(ptr,0);
	}
	else
	{
		Splice_Leaf(ptree,ptr);
	}
}

bool Insert(BPTree *ptree,KeyType kx,Record *rec)
{
	if(ptree == NULL) return false;
	if(ptree->first == NULL || ptree->root == NULL)
	{
		BPNode *s  = _BuyLeaf();
		s->data[0] = kx;
		s->recptr[0] = rec;
		s->num = 1;
		s->parent = NULL;
		s->next = s->prev = NULL;
		ptree->first = ptree->root = s;
		return true;
	}
	Result res = FindRoot(ptree->root,kx);
	if(res.pnode == NULL || res.tag ) return false;
	BPNode *ptr = res.pnode;
	int pos = res.index;
	Insert_Leaf_Item(ptr,pos,kx,rec);
	if(ptr->num > LEAFMAX)
	{
		Adjust_Leaf(ptree,ptr);
	}
	return true;
}

Result Findvalue(BPNode *ptr,KeyType kx)
{
	Result res={NULL,-1,false};
	while(ptr != NULL && kx > ptr->data[ptr->num-1])
	{
		ptr = ptr->next;
	}
	if(ptr != NULL)
	{
		for(int i = 0;i < ptr->num;++i)
		{
			if(ptr->data[i] == kx)
			{
				res.pnode = ptr;
				res.tag = true;
				res.index = i;
				break;
			}
		}
	}
	return res;
}

void Remove_Breh_left(BPNode *ptr,int pos)
{
	for(int i = pos;i <= ptr->num;++i)
	{
		ptr->data[i] = ptr->data[i+1];
		ptr->sub[i] = ptr->sub[i+1];
	}
	ptr->num -= 1;
}

void Remove_Leaf_left(BPNode *ptr,int pos)
{
	for(int i = pos;i < ptr->num;++i)
	{
		ptr->data[i] = ptr->data[i+1];
		ptr->recptr[i] = ptr->recptr[i+1];
	}
	ptr->num -= 1;
}

void Remove_Breh_right(BPNode *ptr,int pos)
{
	for(int i = pos;i >= 0;--i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->sub[i+1] = ptr->sub[i];
	}
	ptr->num += 1;
}

void Brch_Right_Rotate(BPNode *leftbro,BPNode *ptr,
					             BPNode *pa,int pos)
{
	ptr->data[0] = pa->data[pos];
	ptr->num+=1;
	for(int i = ptr->num; i>0; --i)
	{
		ptr->data[i] = ptr->data[i-1];
		ptr->sub[i] = ptr->sub[i-1];
	}
	ptr->sub[0] = leftbro->sub[leftbro->num];
	if(ptr->sub[0] != NULL) 
		ptr->sub[0]->parent = ptr;
	pa->data[pos] = leftbro->data[leftbro->num];
	leftbro->num-=1;
}

void Leaf_Right_Rotate(BPNode *leftbro,BPNode *ptr,
					             BPNode *pa,int pos)
{
	Brch_Right_Rotate(leftbro,ptr,pa,pos);
}

void Brch_Left_Rotate(BPNode *rightbro,BPNode *ptr,
					             BPNode *pa,int pos)
{
	ptr->num+=1;
	ptr->data[ptr->num] = pa->data[pos+1];
	pa->data[pos+1] = rightbro->data[1];
	ptr->sub[ptr->num] = rightbro->sub[0];
	if(ptr->sub[ptr->num] != NULL) 
		ptr->sub[ptr->num]->parent = ptr;
	int i;
	for(i = 0 ;i<rightbro->num; ++i)
	{
		rightbro->data[i] = rightbro->data[i+1];
		rightbro->sub[i] = rightbro->sub[i+1];
	}
	rightbro->sub[i] = NULL;
	rightbro->num -=1;
}
void Leaf_Left_Rotate(BPNode *rightbro,BPNode *ptr,
					             BPNode *pa,int pos)
{
	Brch_Left_Rotate(rightbro,ptr,pa,pos);
}

void Remove_Leaf_right(BPNode *ptr,int pos)
{
	for(int i = pos;i >= 0;--i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->recptr[i+1] = ptr->recptr[i];
	}
	ptr->num += 1;
}

void Del_Brch_Item(BPNode *ptr,int pos)
{
	int i;
	for(i = pos ; i<ptr->num; ++i)
	{
		ptr->data[i] = ptr->data[i+1];
		ptr->sub[i]= ptr->sub[i+1];
	}
	ptr->sub[i] = NULL;
	ptr->num-=1;
}

void Brch_Merge_Left(BPNode *leftbro,BPNode *ptr,
					            BPNode *pa,int pos)
{
	ptr->data[0] = pa->data[pos];
	for(int i= leftbro->num+1,j = 0;j<=ptr->num;++i,++j)
	{
		leftbro->data[i] = ptr->data[j];
		leftbro->sub[i] = ptr->sub[j];
		if(leftbro->sub[i] != NULL) 
			leftbro->sub[i]->parent=leftbro;
	}
	leftbro->num = leftbro->num+ptr->num+1;
	Del_Brch_Item(pa,pos);
}

void Leaf_Merge_Left(BPNode *leftbro,BPNode *ptr,
					           BPNode *pa,int pos)
{
	Brch_Merge_Left(leftbro,ptr,pa,pos);
}

void Remove_move_brch_to_brch(BPNode *p,BPNode *s)
{
	int i = p->num+1;
	int j = 1;
	int k = s->num+1;
	for(;j < k;++i,++j)
	{
		p->data[i] = s->data[j];
		p->sub[i] = s->sub[j];
	}
	p->num += s->num;
}

void Remove_move_leaf_to_leaf(BPNode *p,BPNode *s)
{
	int	i = p->num;
	int	j = 0;
	int	k = s->num;
	for(;j < k;++i,++j)
	{
		p->data[i] = s->data[j];
		p->recptr[i] = s->recptr[j];
	}
	p->num += s->num;
}

void Adjust_Breh(BPTree *ptree,BPNode *ptr)
{
	BPNode *leftbro = NULL,*rightbro = NULL;
	BPNode *pa = ptr->parent;
	int pos = pa->num;
	while(pos >= 0 && ptr != pa->sub[pos]) --pos;
	if(pos < 0)
	{
		std::cout << "btree struct error" << std::endl;
		exit(1);
	}
	if(pos > 0)
		leftbro = pa->sub[pos-1];
	if(pos < pa->num)
		rightbro = pa->sub[pos+1];
	if(leftbro != NULL && leftbro->num > BRCHMIN)
	{
		Leaf_Right_Rotate(leftbro,ptr,pa,pos);
	}
	else if(rightbro != NULL && rightbro->num > BRCHMIN)
	{
		Leaf_Left_Rotate(rightbro,ptr,pa,pos);
	}
	else if(leftbro != NULL)
	{
		Leaf_Merge_Left(leftbro,ptr,pa,pos);
		_Freenode(ptr);
		ptr = leftbro;
	}
	else if(rightbro != NULL)
	{
		Leaf_Merge_Left(ptr,rightbro,pa,pos+1);
		_Freenode(rightbro);
		rightbro= NULL;
	}
	if(pa->parent != NULL && pa->num < BRCHMIN)
	{
		Adjust_Breh(ptree,pa);
	}
	else if(pa->parent == NULL && pa->num <= 0)
	{
		_Freenode(pa);
		ptr->parent = NULL;
		ptree->root = ptr;
	}
}

void Adjust(BPTree *ptree,BPNode *&ptr)
{
	if(ptr->next != NULL && ptr->next->num > LEAFMIN)
	{
		ptr->data[ptr->num] = ptr->next->data[0];
		ptr->recptr[ptr->num] = ptr->next->recptr[0];
		Result res = Findpa(ptr->next,ptr->next->data[0]);
		res.pnode->data[res.index] = ptr->next->data[1];
		Remove_Leaf_left(ptr->next,0);
		ptr->num += 1;
	}
	else if(ptr->prev != NULL && ptr->prev->num > LEAFMIN)
	{
		Result res = Findpa(ptr,ptr->data[0]);
		Remove_Leaf_right(ptr,ptr->num-1);
		ptr->data[0] = ptr->prev->data[ptr->prev->num-1];
		ptr->recptr[0] = ptr->prev->recptr[ptr->prev->num-1];
		ptr->prev->num -= 1;
		res.pnode->data[res.index] = ptr->data[0];
	}
	else 
	{
		Result res;
		if(ptr->prev != NULL && ptr->prev->parent == ptr->parent)
		{
			res = Findpa(ptr,ptr->data[0]);
			BPNode *tmp = ptr;
			Remove_move_leaf_to_leaf(ptr->prev,ptr);
			ptr->prev->next = ptr->next;
			if(ptr->next != NULL)
				ptr->next->prev = ptr->prev;
			Remove_Breh_left(res.pnode,res.index);
			ptr = ptr->prev;
			free(tmp);
		}
		else if(ptr->next != NULL && ptr->next->parent == ptr->parent)
		{
			res = Findpa(ptr->next,ptr->next->data[0]);
			BPNode *tmp = ptr->next;
			Remove_move_leaf_to_leaf(ptr,ptr->next);
			ptr->next = ptr->next->next;
			if(ptr->next != NULL)
				ptr->next->prev = ptr;
			Remove_Breh_left(res.pnode,res.index);
			free(tmp);	
		}
		if(res.pnode == ptree->root && res.pnode->num == 0)
		{
			_Freenode(res.pnode);
			ptree->root = ptr;
		}
		else if(res.pnode->num < BRCHMIN && res.pnode != ptree->root)
		{
			Adjust_Breh(ptree,res.pnode);
		}
	}
}

bool Remove(BPTree *ptree,KeyType kx)
{
	bool res = false;
	if(ptree == NULL) return res;
	Result t = Findvalue(ptree->first,kx);
	if(!t.tag) return res;
	BPNode *ptr = t.pnode;
	int pos = t.index;
	if(ptr->prev == NULL)
	{
		Remove_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN && ptree->root != ptree->first)
		{
			Adjust(ptree,ptr);
		}
		else
		{
			if(ptr->num == 0)
			{
				_Freenode(ptr);
				ptree->root = ptree->first = NULL;
			}
		}
	}
	else if(pos == 0)
	{
		Result pa = Findpa(ptr,ptr->data[0]);
		pa.pnode->data[pa.index] = ptr->data[1];
		Remove_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN)
		{
			Adjust(ptree,ptr);
		}
	}
	else
	{
		Remove_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN)
			Adjust(ptree,ptr);
	}
	return res;
}

void Inorder(BPTree *ptr)
{
	if(ptr == NULL) return;
	BPNode *p = ptr->first;
	int count = 0;
	while(p != NULL)
	{
		std::cout << count << ":"; 
		for(int i = 0;i < p->num;++i)
		{
			std::cout << p->data[i] << " ";
		}
		p = p->next;
		count++;
	}
	std::cout << std::endl; 
}

void cc(BPTree *ptr)
{
	int i,k;
	if(ptr == NULL) return;
	BPNode *p = ptr->root;
	std::queue<BPNode *> st;
	st.push(p);
	while(!st.empty())
	{
		p = st.front();st.pop();
		i = 0;
		k = p->num;
		if(p->utype == BRCH)
		{
			i = 1;
			k = p->num+1;
		}
		for(;i < k;++i)
		{
			std::cout << p->data[i];
			if(p->utype != LEAF)
				st.push(p->sub[i-1]);
		}
		printf("\n");
		if(p->utype != LEAF)
			st.push(p->sub[i]);
	}
}

int main()
{
	BPTree myt;
	//KeyType ar[]={"9qwer5tyui6opa8sdfg7hjk4lz2xc3v1bnm0"};
	//int n = sizeof(ar)/sizeof(ar[0])-1;
	Record *rec = (Record*)0x00008888;
	int n = 1000;
	Init_BPTree(&myt);
	for(int i = 0;i<n;++i)
	{
		int k = rand()%1000;
		Insert(&myt,k,rec);
		//std::cout << ar[i] << ":";
		Inorder(&myt);
	}
	Inorder(&myt);
	for(int i = 1;i <= myt.root->num;++i)
		printf("---------------------%c:%d\n",myt.root->data[i],myt.root->num);
	KeyType m;
	while(1)
	{
		std::cin >> m;
		if(m == -1) 
			break;
		Remove(&myt,m);
		Inorder(&myt);
		printf("llllllllllll\n");
		//for(int i = 1;i <= myt.root->num;++i)
		//	printf("---------------------%c:%d\n",myt.root->data[i],myt.root->num);
		//cc(&myt);
		std::cout << std::endl;
	}
	return 0;
}


