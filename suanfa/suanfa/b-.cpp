/*
 * =====================================================================================
 *       Filename:  b--.cpp
 *        Version:  1.0
 *        Created:  2016年04月27日 22时20分28秒
 *       Compiler:  gcc
 *         Author:  wengduo (mn), 2292466904@qq.com
 * =====================================================================================
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cassert>
#define M 5
#define MAXSIZE (M-1)
#define MINSIZE (M/2)

typedef char KeyType;
#define END '#'
typedef struct {} Record;
typedef struct
{
	KeyType key;
	Record *recptr;
}ElemType;

typedef struct BNode
{
	int num;
	BNode *parent;
	ElemType data[M+1];
	BNode *  sub[M+1];
}BNode, *BTree;

typedef struct
{
	BNode *pnode;
	int    pos;
	bool   tag; 
}Result;

Result FindValue(BNode * ptr, KeyType kx)
{
	Result res = { NULL,-1,false};
	while(ptr != NULL)
	{
		ptr->data[0].key = kx;
		int i = ptr->num;
		while(kx < ptr->data[i].key) --i;
		res.pnode = ptr;
		res.pos = i;
		if(i>0 && ptr->data[i].key == kx)
		{
			res.tag = true;
			break;
		}
		ptr = ptr->sub[i];
	}
	return res;
}
Result SearchValue(BNode *ptr,KeyType kx)
{
	Result res = { NULL,-1,false};
	if(ptr != NULL)
	{
		ptr->data[0].key = kx;
		int i = ptr->num;
		while(kx < ptr->data[i].key) --i;
		res.pnode = ptr;
		res.pos = i;
		if(i>0 && ptr->data[i].key == kx)
		{
			res.tag = true;
		}else if(ptr->sub[i] != NULL)
		{
			res = SearchValue(ptr->sub[i],kx);
		}
	}
	return res;
}
BNode * _Buynode()
{
	BNode *s = (BNode *)malloc(sizeof(BNode));
	if(NULL == s) exit(1);
	memset(s,0,sizeof(BNode));
	return s;
}
void _Freenode(BNode *p)
{
	free(p);
}

BNode * MakeRoot(ElemType x,BNode *left,BNode *right)
{
	BNode * s = _Buynode();
	s->data[1] = x;
	s->num = 1;
	s->parent = NULL;
	s->sub[0] = left;
	if(left != NULL) left->parent = s;
	s->sub[1] = right;
	if(right != NULL) right->parent = s;
	return s;
}

void Insert_Item(BNode *ptr,int pos,ElemType x,BNode *right)
{
	for(int i = ptr->num; i>pos; --i)
	{
		ptr->data[i+1] = ptr->data[i];
		ptr->sub[i+1] = ptr->sub[i];
	}
	ptr->data[pos+1] = x;
	ptr->sub[pos+1] = right;
	if(right != NULL) right->parent = ptr;
	ptr->num+=1;
}

ElemType Move_Item(BNode *ptr,BNode *s)
{
   for(int i = 0,j=MINSIZE+1;j<=ptr->num;++i,++j)
   {
       s->data[i] = ptr->data[j];
       s->sub[i] = ptr->sub[j];
       if(s->sub[i] != NULL)
           s->sub[i]->parent = s;
   }
   s->num = MINSIZE;
   ptr->num = MINSIZE;
   s->parent = ptr->parent;
   return s->data[0];
}

BNode *Splice(BNode *ptr)
{
	BNode *s = _Buynode();
	ElemType x = Move_Item(ptr,s);
	if(ptr->parent == NULL)
	{
		return MakeRoot(x,ptr,s);
	}
	ptr=ptr->parent;
	int pos = ptr->num;
	ptr->data[0]= x;
	while(x.key < ptr->data[pos].key) --pos;
	Insert_Item(ptr,pos,x,s);
	if(ptr->num > MAXSIZE)
	{
		return Splice(ptr);
	}else
	{
		return NULL;
	}
}

bool Insert(BTree *ptree,ElemType x)
{
	if(ptree == NULL) return false;
	if(*ptree == NULL)
	{
		*ptree = MakeRoot(x,NULL,NULL);
		return true;
	}
	Result res = FindValue(*ptree,x.key);
	if(res.pnode == NULL || res.tag) return false;
	BNode *ptr = res.pnode;
	int    pos = res.pos;
	Insert_Item(ptr,pos,x,NULL);
	if(ptr->num > MAXSIZE)
	{
		BNode *newroot = Splice(ptr);
		if(newroot != NULL)
		{
			*ptree = newroot;
		}
	}
	return true;
}

void InOrder(BNode *ptr)
{
	if(ptr != NULL)
	{
		InOrder(ptr->sub[0]);
		for(int i = 1;i<=ptr->num;++i)
		{
			std::cout << ptr->data[i].key;
			InOrder(ptr->sub[i]);
		}
	}
}
///////////////////////////////////////////////////////

BNode * FindPrev(BNode *ptr)
{
	while(ptr != NULL && ptr->sub[ptr->num] != NULL)
	{
		ptr = ptr->sub[ptr->num];
	}
	return ptr;
}

BNode * FindNext(BNode *ptr)
{
	while(ptr != NULL && ptr->sub[0])
	{
		ptr = ptr->sub[0];
	}
	return ptr;
}
////////////////////////////////
// Del brch  leaf;
				         
void Del_Brch_Item(BNode *ptr,int pos)
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
//#define Del_Leaf_Item(ptr,pos) Del_Brch_Item(ptr,pos);
void Del_Leaf_Item(BNode *ptr,int pos)
{
	Del_Brch_Item(ptr,pos);
}
///////////////////////////////////
void Brch_Right_Rotate(BNode *leftbro,BNode *ptr,
					             BNode *pa,int pos)
{
	ptr->data[0] = pa->data[pos];
	// right_1
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
void Leaf_Right_Rotate(BNode *leftbro,BNode *ptr,
					             BNode *pa,int pos)
{
	Brch_Right_Rotate(leftbro,ptr,pa,pos);
}
///////////////////////

void Brch_Left_Rotate(BNode *rightbro,BNode *ptr,
					             BNode *pa,int pos)
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
void Leaf_Left_Rotate(BNode *rightbro,BNode *ptr,
					             BNode *pa,int pos)
{
	Brch_Left_Rotate(rightbro,ptr,pa,pos);
}
//////////////////////////////////////

void Brch_Merge_Left(BNode *leftbro,BNode *ptr,
					            BNode *pa,int pos)
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
void Leaf_Merge_Left(BNode *leftbro,BNode *ptr,
					           BNode *pa,int pos)
{
	Brch_Merge_Left(leftbro,ptr,pa,pos);
}
BNode * Rotate_Leaf(BNode *ptr);

BNode * Rotate_Brch(BNode *ptr)
{
	return Rotate_Leaf(ptr);
}
BNode * Rotate_Leaf(BNode *ptr)
{
	BNode *leftbro = NULL, *rightbro = NULL;
	BNode *pa = ptr->parent;
	int pos = pa->num;
	while(pos >= 0 && ptr != pa->sub[pos]) --pos;
	if(pos < 0 ) 
	{
		std::cout<<"btree struct error"<<std::endl;
		exit(1);
	}
	if(pos > 0)
		leftbro = pa->sub[pos-1];
	if(pos <pa->num)
		rightbro = pa->sub[pos+1];

	if(leftbro != NULL && leftbro->num > MINSIZE)
	{
		Leaf_Right_Rotate(leftbro,ptr,pa,pos);
	}else if(rightbro != NULL && rightbro->num > MINSIZE)
	{
		Leaf_Left_Rotate(rightbro,ptr,pa,pos);
	}else if(leftbro != NULL)
	{
		Leaf_Merge_Left(leftbro,ptr,pa,pos);
		_Freenode(ptr);
		ptr = leftbro;
	}else if(rightbro != NULL)
	{
		Leaf_Merge_Left(ptr,rightbro,pa,pos+1);
		_Freenode(rightbro);
		rightbro= NULL;
	}
	////////////////////////////////
	if(pa->parent != NULL && pa->num < MINSIZE)
	{
		return Rotate_Brch(pa);
	}else if(pa->parent == NULL && pa->num <= 0)
	{
		_Freenode(pa);
		ptr->parent = NULL;
		return ptr;
	}
	return NULL;
}

bool Remove(BTree *ptree,KeyType kx)
{
	if(ptree == NULL) return false;
	Result res = FindValue(*ptree,kx);
	if(res.pnode == NULL || !res.tag) return false;
	BNode *ptr = res.pnode;
	int    pos = res.pos;
	BNode *ps = FindPrev(ptr->sub[pos-1]);
	BNode *ns = FindNext(ptr->sub[pos]);
	if(ps != NULL && ps->num > MINSIZE)
	{
		ptr->data[pos] = ps->data[ps->num];
		ptr = ps;
		pos = ps->num;
	}else if(ns != NULL && ns->num > MINSIZE)
	{
		ptr->data[pos] = ns->data[1];
		ptr = ns;
		pos = 1;
	}else if(ps != NULL)
	{
		ptr->data[pos] = ps->data[ps->num];
		ptr = ps;
		pos = ps->num;
	}else if(ns != NULL)
	{ /// ???
		ptr->data[pos] = ns->data[1];
		ptr = ns;
		pos = 1;
	}
	/////////////////////////////////
	// ptr leaf
	Del_Leaf_Item(ptr,pos);
	if(ptr->parent != NULL && ptr->num < MINSIZE)
	{
		BNode *newroot = Rotate_Leaf(ptr);
		if(newroot != NULL)
		{
			*ptree = newroot;
		}
	}else if(ptr->parent == NULL && ptr->num <= 0)
	{
		_Freenode(ptr);
		*ptree= NULL;
	}
	return true;
}


int main()
{
	BTree root =NULL;
	KeyType ar[]={"qwx1er2tyui7opa3sd0fgh5jak9l4zx8ccvb6nm"};
	int n = sizeof(ar)/sizeof(ar[0])-1;
	ElemType item;
	KeyType kx;
	for(int i = 0;i<n;++i)
	{
		item.key = ar[i];
		item.recptr = NULL;
		std::cout << Insert(&root,item);
		InOrder(root);
		std::cout << std::endl;
	}
	while(std::cin >> kx, kx != END)
	{
		std::cout << Remove(&root,kx)<<" : ";
		InOrder(root);
		std::cout << std::endl;
	}
}
