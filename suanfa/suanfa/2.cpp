/*************************************************************************
    > File Name: b×.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年05月03日 星期二 18时36分37秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <algorithm>
#define M 5 
#define LEAFMAX  M
#define LEAFMIN  (M/2+1)

#define BRCHMAX  (M-1)
#define BRCHMIN  (M/2)
typedef enum{LEAF = 0,BRCH = 1} NodeType;
typedef int KeyType;
typedef struct {}Record;
typedef struct BPNode
{
	int num;
	BPNode *parent;
	NodeType utype;
	KeyType data[M+1];
	BPNode *prev,*next;
	union
	{
		struct
		{
			Record *recptr[M+1];
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

BPTree myt;
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

Result Findpa(BPNode *ptr,KeyType kx)
{
	Result res = {NULL,-1,false};
//	if(myt.root == NULL) return res;
//	BPNode *p = myt.root;
//	int i = p->num;
//	while(p != NULL && p->utype != LEAF)
//	{
//		i = p->num;
//		while(kx < p->data[i] && i > 0) i--;
//		if(p->data[i] == kx)
//		{
//			res.tag = true;
//			res.index = i;
//			res.pnode = p;
//			return res;
//		}
//		p = p->sub[i];
//	}
//	printf("kkkkkkkkkkkkkkkkk%d\n",kx);
//	exit(-1);
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


void Insert_Brch_Item(BPNode *p,KeyType kx,BPNode *s)
{
	p->data[0] = kx;
	int i = 0;
	for(i = p->num;kx < p->data[i];--i)
	{
		p->data[i+1] = p->data[i];
		p->sub[i+1] = p->sub[i];
	}
	//if(i ==0) printf("error\n");
	p->data[i+1] = kx;
	p->sub[i+1] = s;
	p->sub[i+1]->parent = p;
	p->num+=1;
}

void Move_Brch_left(BPNode *ptr,int pos,int bg = 0)
{
	for(int i = bg;i < ptr->num;++i)
	{
		ptr->data[i] = ptr->data[i+pos];
		ptr->sub[i] = ptr->sub[i+pos];
	}
	ptr->num -= pos;
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

void Move_Leaf_p(BPNode *p,BPNode *s)
{
	int i = p->num;
	int j = 0;
	int k = M/3;
	for(;j < k;++i,++j)
	{
		p->data[i] = s->data[j];
		p->recptr[i] = s->recptr[j];
	}
	p->num += j;
	Move_Leaf_left(s,j-1);
}

KeyType Move_Leaf_n(BPNode *ptr,BPNode *s)
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
	s->next = ptr->next;
	s->prev = ptr;
	ptr->next = s;
	if(s->next != NULL)
		s->next->prev = s;
//	if(s->next != NULL)
//	{
//		s->next->prev = s;
//		Result res = Findpa(s->next,s->next->data[1]);
//		s->data[s->num+1] = res.pnode->data[res.index];
//		s->sub[s->num+1] = s->next->sub[0];
//		s->sub[s->num+1]->parent = s;
//		s->num += 1;
//		j++;
//		int k = M/3;
//		for(i = 1;i < k;++j,++i)
//		{
//			s->data[j] = s->next->data[i];
//			s->sub[j] = s->next->sub[i-1];
//			s->sub[j]->parent = s;
//		}
//		s->num += k;
//		Move_Brch_left(s->next,k);
//		res.pnode->data[res.index] = s->next->data[0];
//	}
	return s->data[0];
}


void Adjust_Breh(BPTree *ptree,BPNode *ptr);
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
		ptr->root->prev = ptr->root->next = NULL;
		s->parent = ptr->root;
		p->parent = ptr->root;
	}
	else
	{
		Insert_Brch_Item(p->parent,kx,s);
		if(p->parent->num > BRCHMAX)
		{
			Adjust_Breh(ptr,p->parent);
		}
	}
}

void Move_Brch_right(BPNode *ptr,int pos,BPNode *s)
{
	for(int i = ptr->num;i >= 0;--i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->sub[i+1] = ptr->sub[i];
	}
	ptr->sub[0] = s->sub[s->num];
	ptr->sub[0]->parent = ptr;
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
	leftbro->next = ptr->next;
	if(leftbro->next != NULL)
		leftbro->next->prev = leftbro;
	leftbro->num = leftbro->num+ptr->num+1;
	Del_Brch_Item(pa,pos);
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


void Adjust_Breh(BPTree *ptree,BPNode *ptr)
{
	if(ptr->next != NULL && ptr->next->num < BRCHMAX)
	{
		Result res = Findpa(ptr->next,ptr->next->data[1]);
		ptr->next->data[0] = ptr->data[ptr->num];
		Move_Brch_right(ptr->next,1,ptr);
		res.pnode->data[res.index] = ptr->data[ptr->num];
		ptr->num -= 1;
	}
	else if(ptr->prev != NULL && ptr->prev->num < BRCHMAX)
	{
		Result res = Findpa(ptr,ptr->data[1]);
		res.pnode->data[res.index] = ptr->data[2];
		ptr->prev->data[ptr->prev->num+1] = ptr->data[1];
		ptr->prev->sub[ptr->prev->num+1] = ptr->sub[0];
		ptr->prev->sub[ptr->prev->num+1]->parent = ptr->prev;
		Move_Brch_left(ptr,1);
		ptr->prev->num += 1;
	}
	else
	{
		Splice_Breh(ptree,ptr);
	}
}

void Splice_Leaf(BPTree *ptr,BPNode *p)
{
	BPNode *s = _BuyLeaf();
	s->next = s->prev = NULL;

	KeyType kx = Move_Leaf_n(p,s);
	if(p->parent == NULL)
	{
		ptr->root = _Buynode();
		ptr->root->utype = BRCH;
		ptr->root->data[1] = kx;
		ptr->root->sub[0] = p;
		ptr->root->sub[1] = s;
		ptr->root->num = 1;
		ptr->root->prev = ptr->root->next = NULL;
		p->parent = ptr->root;
		s->parent = ptr->root;
	}
	else
	{
		Insert_Brch_Item(p->parent,kx,s);
//		if(s->next != NULL)
//		{
//			Result res = Findpa(s->next,s->next->data[0]);
//			Move_Leaf_p(s,s->next);
//			res.pnode->data[res.index] = s->next->data[0];
//		}
		if(p->parent->num > BRCHMAX)
		{
			Adjust_Breh(ptr,p->parent);
		}
	}
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

void Delete_Adjust_Breh(BPTree *ptree,BPNode *ptr)
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
		Brch_Right_Rotate(leftbro,ptr,pa,pos);
	}
	else if(rightbro != NULL && rightbro->num > BRCHMIN)
	{
		Brch_Left_Rotate(rightbro,ptr,pa,pos);
	}
	else if(leftbro != NULL)
	{
		Brch_Merge_Left(leftbro,ptr,pa,pos);
		_Freenode(ptr);
		ptr = leftbro;
	}
	else if(rightbro != NULL)
	{
		Brch_Merge_Left(ptr,rightbro,pa,pos+1);
		_Freenode(rightbro);
		rightbro= NULL;
	}
	if(pa->parent != NULL && pa->num < BRCHMIN)
	{
		Delete_Adjust_Breh(ptree,pa);
	}
	else if(pa->parent == NULL && pa->num <= 0)
	{
		_Freenode(pa);
		ptr->parent = NULL;
		ptree->root = ptr;
	}
}

void Delete_Adjust_leaf(BPTree *ptree,BPNode *&ptr)
{
	if(ptr->next != NULL && ptr->next->num > LEAFMIN)
	{
		ptr->data[ptr->num] = ptr->next->data[0];
		ptr->recptr[ptr->num] = ptr->next->recptr[0];
		Result res = Findpa(ptr->next,ptr->next->data[0]);
		res.pnode->data[res.index] = ptr->next->data[1];
		Move_Leaf_left(ptr->next,0);
		ptr->num += 1;
	}
	else if(ptr->prev != NULL && ptr->prev->num > LEAFMIN)
	{
		Result res = Findpa(ptr,ptr->data[0]);
		Move_Leaf_right(ptr,1);
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
			Move_Brch_left(res.pnode,1,res.index);
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
			Move_Brch_left(res.pnode,1,res.index);
			free(tmp);	
		}
		if(res.pnode == ptree->root && res.pnode->num == 0)
		{
			_Freenode(res.pnode);
			ptree->root = ptr;
		}
		else if(res.pnode->num < BRCHMIN && res.pnode != ptree->root)
		{
			Delete_Adjust_Breh(ptree,res.pnode);
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
		Move_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN && ptree->root != ptree->first)
		{
			Delete_Adjust_leaf(ptree,ptr);
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
		Move_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN)
		{
			Delete_Adjust_leaf(ptree,ptr);
		}
	}
	else
	{
		Move_Leaf_left(ptr,pos);
		if(ptr->num < LEAFMIN)
			Delete_Adjust_leaf(ptree,ptr);
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
			std::cout << p->data[i]	 << " ";
		}
		p = p->next;
		count++;
	}
	std::cout << std::endl; 
}

int main()
{
	//KeyType ar[]={"8qw5ert6yuio7pa9sd3fghj4klzx2cv1bn0m"};
	//int n = sizeof(ar)/sizeof(ar[0])-1;
	Record *rec = (Record*)0x00008888;
	int n = 1000;
	int count = 0;
	Init_BPTree(&myt);
	for(int i = 0;i<n;++i)
	{
		//Insert(&myt,ar[i],rec);
		int k = rand()%1000;
		Insert(&myt,k,rec);
		std::cout << count << "--------";
		Inorder(&myt);
		count++;
	}
	Inorder(&myt);
	for(int i = 1;i <= myt.root->num;++i)
		printf("---------------------%c:%d\n",myt.root->data[i],myt.root->num);
	KeyType m;
	while(1)
	{
		std::cin >> m;
		if(m == '#') break;
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
