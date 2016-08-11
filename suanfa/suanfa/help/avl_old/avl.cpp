
#define BALANCE_CHECK

#ifndef NULL
#define NULL 0
#endif

/*
    Default Value Control
*/
template<typename Type>
struct DefaultValue
{static Type Value;};
template<typename Type>
Type DefaultValue<Type>::Value;

#define DECLARE_DEFAULT_VALUE(T, value) template<>\
struct DefaultValue<T>{static T Value;};\
template<>\
T DefaultValue<T>::Value = value;

DECLARE_DEFAULT_VALUE(int, 0)
DECLARE_DEFAULT_VALUE(double, 0)

/*
    Node
        if BALANCE_CHECK is defined, LHeight, RHeight and Height are used;
*/
template<typename Type>
struct Node
{
	Type	Data;
	Node* 	LChild, *RChild;
	int 	BalanceFactor;
	
#ifdef BALANCE_CHECK
int		LHeight, RHeight, Height;
#endif
	
	Node(const Type& _Data = DefaultValue<Type>::Value,
		Node* _LChild = NULL,
		Node* _RChild = NULL,
		int	  _BalanceFactor = 0):
		Data(_Data), 
		LChild(_LChild), 
		RChild(_RChild),
		BalanceFactor(_BalanceFactor)
	{}
};

/*
    AVLTree
        if BALANCE_CHECK is defined, you can check the balance;
*/
template<typename Type>
class AVLTree
{
public:
    
        typedef Type              DataType;
		typedef Node<Type>        NodeType;
		typedef NodeType*         pNodeType;
		typedef DefaultValue<Type> DefaultValueType;
		
		enum {LEFT, RIGHT};
		
public:
    
		AVLTree(): head(new NodeType) {}
		~AVLTree() {Destroy();}
		
public:
    
		int   	Insert(const Type& it);
		int  	Delete(const Type& it);
		int     GetMin(Type& it);
		int      GetMax(Type& it);
public:
        
        template<typename OP>
		void	PreOrder(OP);
		
        template<typename OP>
		void	InOrder(OP);
		
	template<typename OP>
		void	PreInOrder(int type, OP);
		
private:

		inline	void		ReplaceChild(pNodeType  Parent, pNodeType Child, pNodeType NewChild);
		
		inline	void		RRotateFactorI(pNodeType Parent, pNodeType Tree);
		inline	void		RRotateFactorD(pNodeType Parent, pNodeType Tree);
		inline	pNodeType	RRotate(pNodeType Parent, pNodeType Tree);
		
		inline	void		LRRotateFactorI(pNodeType Parent, pNodeType Tree);
		inline	void		LRRotateFactorD(pNodeType Parent, pNodeType Tree);
		inline	pNodeType	LRRotate(pNodeType Parent, pNodeType Tree);
		
		inline	void		LRotateFactorI(pNodeType Parent, pNodeType Tree);
		inline	void		LRotateFactorD(pNodeType Parent, pNodeType Tree);
		inline	pNodeType	LRotate(pNodeType Parent, pNodeType Tree);
		
		
		inline	void		RLRotateFactorI(pNodeType Parent, pNodeType Tree);
		inline	void		RLRotateFactorD(pNodeType Parent, pNodeType Tree);
		inline	pNodeType	RLRotate(pNodeType Parent, pNodeType Tree);
		
		void                Destroy();
		void                Destroy(pNodeType Tree);
private:
		NodeType* head;	
		
		
#ifdef BALANCE_CHECK
public:
		int		BalanceCheck();
		int		BalanceCheck(pNodeType tree);
#endif
};

template<typename Type>
int AVLTree<Type>::Insert(const Type& it)
{
	pNodeType Parent = head, Curr = head->LChild;
	pNodeType LastNotBalance = NULL, ParentLastNotBalance = NULL;
	
	while (Curr)
	{
		if (Curr->Data == it) return 0;
		if (Curr->BalanceFactor) 
			ParentLastNotBalance = Parent, LastNotBalance = Curr;
		Parent = Curr;
		Curr = it < Curr->Data ? Curr->LChild : Curr->RChild;
	}
	
	pNodeType NewNode = new NodeType(it);
	
	if (Parent == head)
	{
		head->LChild = NewNode;
		return 1;
	}
	else
	{
		it < Parent->Data ? 
			Parent->LChild = NewNode :
			Parent->RChild = NewNode;
	}
	
	for (Curr = LastNotBalance ? LastNotBalance : head->LChild;
		Curr != NewNode;)
	{
		it < Curr->Data ?
			(++Curr->BalanceFactor, Curr = Curr->LChild):
			(--Curr->BalanceFactor, Curr = Curr->RChild);
	}
	
	if (!LastNotBalance || LastNotBalance->BalanceFactor < 2 &&
			LastNotBalance->BalanceFactor > -2)
		return 1;
	
	if (it < LastNotBalance->Data)
	{
		if (it < LastNotBalance->LChild->Data )
		{
			RRotateFactorI(ParentLastNotBalance, LastNotBalance);
			ReplaceChild(
						ParentLastNotBalance, 
						LastNotBalance,
						RRotate(ParentLastNotBalance, LastNotBalance)
						);
		}
		else
		{
			LRRotateFactorI(ParentLastNotBalance, LastNotBalance);		
			ReplaceChild(
						ParentLastNotBalance, 
						LastNotBalance,
						LRRotate(ParentLastNotBalance, LastNotBalance)
						);
		}
	}
	else
	{
		if (it > LastNotBalance->RChild->Data)
		{
			LRotateFactorI(ParentLastNotBalance, LastNotBalance);
			ReplaceChild(
						ParentLastNotBalance, 
						LastNotBalance,
						LRotate(ParentLastNotBalance, LastNotBalance)
						);
		}
		else
		{
			
			RLRotateFactorI(ParentLastNotBalance, LastNotBalance);
			ReplaceChild(
						ParentLastNotBalance, 
						LastNotBalance,
						RLRotate(ParentLastNotBalance, LastNotBalance)
						);
		}
	}
	return 1;
}

template<typename Type>
int AVLTree<Type>::Delete(const Type& it)
{
	pNodeType SearchHistory[64];
	int		  SearchDirection[64];
	int		  CurrIdx;
	
	pNodeType Curr = head->LChild;
	SearchHistory[0] = head;
	SearchDirection[0] = 0;
	CurrIdx = 1;
	
	while (Curr && Curr->Data != it)
	{
		SearchHistory[CurrIdx] = Curr;
		it < Curr->Data ?
			(Curr = Curr->LChild, SearchDirection[CurrIdx] = LEFT): 
			(Curr = Curr->RChild, SearchDirection[CurrIdx] = RIGHT);
		++CurrIdx;
	}
	
	if (!Curr) return 0;
	
	pNodeType ToBeDeleted = Curr;
	if (Curr->LChild && Curr->RChild)
	{
		pNodeType  CurrT = Curr->LChild;
		SearchHistory[CurrIdx] = Curr;
		SearchDirection[CurrIdx++] = LEFT;
		while (CurrT->RChild)
		{
			SearchHistory[CurrIdx] = CurrT;
			SearchDirection[CurrIdx++] = RIGHT;
			CurrT = CurrT->RChild;
		}
		Curr->Data = CurrT->Data;
		ToBeDeleted = CurrT;
	}
	
	
	// There exists at least one child that is NULL
	{
		pNodeType Temp = 
			ToBeDeleted->LChild ?
				ToBeDeleted->LChild :
					(ToBeDeleted->RChild  ? ToBeDeleted->RChild : NULL);
		delete ToBeDeleted;
		--CurrIdx;//	Indidate the pointer to the parent of the node to be deleted
		SearchDirection[CurrIdx] == RIGHT ?
			SearchHistory[CurrIdx]->RChild = Temp:
			SearchHistory[CurrIdx]->LChild = Temp;
	}

	for (int HeightChanged = 1; HeightChanged && CurrIdx; --CurrIdx)
	{	
		pNodeType ToBeAdjusted = SearchHistory[CurrIdx];
		pNodeType ParentToBeAdjusted = SearchHistory[CurrIdx-1];
		int		  ChangedChild = SearchDirection[CurrIdx];
		if (ToBeAdjusted->BalanceFactor == 0)
		{
			ToBeAdjusted->BalanceFactor = ChangedChild == LEFT? -1 : 1;
			HeightChanged = 0;
		}
		else if (ToBeAdjusted->BalanceFactor == -1)
		{
			if (ChangedChild == RIGHT)
			{
				ToBeAdjusted->BalanceFactor = 0;
				HeightChanged = 1;
			}
			else
			{
				switch (ToBeAdjusted->RChild->BalanceFactor)
				{
				case 0:
					HeightChanged = 0;
					LRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								LRotate(ParentToBeAdjusted, ToBeAdjusted));
					break;
				case -1:
					HeightChanged = 1;
					LRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								LRotate(ParentToBeAdjusted, ToBeAdjusted));
					break;
				case 1:
					HeightChanged = 1;
					RLRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								RLRotate(ParentToBeAdjusted, ToBeAdjusted));
				}
			}
		}
		else
		{
			if (ChangedChild == LEFT)
			{
				ToBeAdjusted->BalanceFactor = 0;
				HeightChanged = 1;
			}
			else
			{
				switch (ToBeAdjusted->LChild->BalanceFactor)
				{
				case 0:
					HeightChanged = 0;
					RRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								RRotate(ParentToBeAdjusted, ToBeAdjusted));
					break;
				case 1:
					HeightChanged = 1;
					RRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								RRotate(ParentToBeAdjusted, ToBeAdjusted));
					break;
				case -1:
					HeightChanged = 1;
					LRRotateFactorD(ParentToBeAdjusted, ToBeAdjusted);
					ReplaceChild(ParentToBeAdjusted, ToBeAdjusted,
								LRRotate(ParentToBeAdjusted, ToBeAdjusted));
				}
			}
		}		
	}
	
	return 1;
}

template<typename Type>
int     AVLTree<Type>::GetMin(Type& it)
{
    pNodeType   Curr = head->LChild;
    if (!Curr) return 0;
    while (Curr->LChild) Curr = Curr->LChild;
    it = Curr->Data;
    return 1;
}   
 
template<typename Type>
int     AVLTree<Type>::GetMax(Type& it)
{
    pNodeType   Curr = head->LChild;
    if (!Curr) return 0;
    while (Curr->RChild) Curr = Curr->RChild;
    it = Curr->Data;
    return 1;
}    

template<typename Type>
template<typename OP>
void AVLTree<Type>::PreOrder(OP ope)
{
	PreInOrder(0, ope);
}

template<typename Type>
template<typename OP>
void AVLTree<Type>::InOrder(OP ope)
{
    PreInOrder(1, ope);
}

template<typename Type>
template<typename OP>
void AVLTree<Type>::PreInOrder(int type, OP ope)
{
	pNodeType Curr = head->LChild;
	pNodeType R = NULL;
	
	while (true)
	{
		if (Curr == NULL) break;
		
		pNodeType q = Curr->LChild;
		if (q == NULL)
		{
			ope(Curr->Data);
			R = Curr;
			Curr = Curr->RChild;
		}
		else
		{
			while (q->RChild != NULL && q->RChild != Curr)
				q = q->RChild;
			if (q->RChild == NULL)
			{
				q->RChild = Curr;
				if (type == 0) ope(Curr->Data);;
				Curr = Curr->LChild;
			}
			else
			{	
				R = Curr;
				if (type == 1) ope(Curr->Data);
				Curr = Curr->RChild;
				q->RChild = NULL;
			}
			
		}
	}
}

template<typename Type>
inline	void		
AVLTree<Type>::ReplaceChild(pNodeType  Parent, pNodeType Child, pNodeType NewChild)
{
	Parent->LChild == Child ?
		Parent->LChild = NewChild :
		Parent->RChild = NewChild ;
}

// Right rotate the tree
template<typename Type>
inline void 
AVLTree<Type>::RRotateFactorI(pNodeType Parent, pNodeType Tree)
{
	Tree->BalanceFactor = 0;
	Tree->LChild->BalanceFactor = 0;
}

template<typename Type>
inline void
AVLTree<Type>::RRotateFactorD(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->LChild;
	if (B->BalanceFactor == 0)
	{
		A->BalanceFactor = 1;
		B->BalanceFactor = -1;
	}
	else
	{
		A->BalanceFactor = 0;
		B->BalanceFactor = 0;
	}
}

template<typename Type>
inline typename AVLTree<Type>::pNodeType 
AVLTree<Type>::RRotate(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->LChild;
	A->LChild = B->RChild;
	B->RChild = A;
	return B;
}

// Left rotate the LChild of the tree and right rotate the tree
template<typename Type>
inline void
AVLTree<Type>::LRRotateFactorI(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->LChild;
	pNodeType C = B->RChild;
	
	switch (C->BalanceFactor)
	{
	case  1:
				B->BalanceFactor = 0;
				A->BalanceFactor = -1;
				C->BalanceFactor = 0;
				break;
	case -1:
				B->BalanceFactor = 1;
				A->BalanceFactor = 0;
				C->BalanceFactor = 0;
				break;
	case 0:
				B->BalanceFactor = 0;
				A->BalanceFactor = 0;
				C->BalanceFactor = 0;
	}
}

template<typename Type>
inline void
AVLTree<Type>::LRRotateFactorD(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->LChild;
	pNodeType C = B->RChild;
	
	switch (C->BalanceFactor)
	{
	case  -1:
				A->BalanceFactor = 0;
				B->BalanceFactor = 1;
				C->BalanceFactor = 0;
				break;
	case 0:
				A->BalanceFactor = 0;
				B->BalanceFactor = 0;
				C->BalanceFactor = 0;
				break;
	case 1:
				A->BalanceFactor = -1;
				B->BalanceFactor = 0;
				C->BalanceFactor = 0;
	}
}

template<typename Type>
inline typename AVLTree<Type>::pNodeType
AVLTree<Type>::LRRotate(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->LChild;
	pNodeType C = B->RChild;
	
	B->RChild = C->LChild;
	A->LChild = C->RChild;
	C->LChild = B;
	C->RChild = A;
				
	return C;
}

// Left rotate the tree
template<typename Type>
inline void
AVLTree<Type>::LRotateFactorI(pNodeType Parent, pNodeType Tree)
{
	Tree->BalanceFactor = 0;
	Tree->RChild->BalanceFactor = 0;
}

template<typename Type>
inline void
AVLTree<Type>::LRotateFactorD(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->RChild;
	if (B->BalanceFactor == 0)
	{
		A->BalanceFactor = -1;
		B->BalanceFactor = 1;
	}
	else
	{
		A->BalanceFactor = 0;
		B->BalanceFactor = 0;
	}
}

template<typename Type>
inline typename AVLTree<Type>::pNodeType
AVLTree<Type>::LRotate(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->RChild;
	
	A->RChild = B->LChild;
	B->LChild = A;
	
	return B;
}

// Right rotate the RChild of the tree and left rotate the tree
template<typename Type>
inline void
AVLTree<Type>::RLRotateFactorI(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->RChild;
	pNodeType C = B->LChild;
	
	switch (C->BalanceFactor)
	{
	case  1:
			B->BalanceFactor = -1;
			A->BalanceFactor = 0;
			C->BalanceFactor = 0;
			break;
	case -1:
			B->BalanceFactor = 0;
			A->BalanceFactor = 1;
			C->BalanceFactor = 0;
			break;
	case 0:
			B->BalanceFactor = 0;
			A->BalanceFactor = 0;
			C->BalanceFactor = 0;
	}
}

template<typename Type>
inline void
AVLTree<Type>::RLRotateFactorD(pNodeType Parent, pNodeType Tree)
{
    
	pNodeType A = Tree;
	pNodeType B = Tree->RChild;
	pNodeType C = B->LChild;
	
	switch (C->BalanceFactor)
	{
	case  -1:
				A->BalanceFactor = 1;
				B->BalanceFactor = 0;
				C->BalanceFactor = 0;
				break;
	case 0:
				A->BalanceFactor = 0;
				B->BalanceFactor = 0;
				C->BalanceFactor = 0;
				break;
	case 1:
				A->BalanceFactor = 0;
				B->BalanceFactor = -1;
				C->BalanceFactor = 0;
	}
}

template<typename Type>
inline typename AVLTree<Type>::pNodeType
AVLTree<Type>::RLRotate(pNodeType Parent, pNodeType Tree)
{
	pNodeType A = Tree;
	pNodeType B = Tree->RChild;
	pNodeType C = B->LChild;
			
	B->LChild = C->RChild;
	A->RChild = C->LChild;
	C->LChild = A;
	C->RChild = B;
			
	return C;
}

template<typename Type>
void    AVLTree<Type>::Destroy()
{
    if (head) Destroy(head->LChild);
    head = NULL;
}    

template<typename Type>
void    AVLTree<Type>::Destroy(pNodeType Tree)
{
    if (!Tree) return;
    Destroy(Tree->LChild);
    Destroy(Tree->RChild);
    delete Tree;
}

#ifdef BALANCE_CHECK
template<typename Type>
int AVLTree<Type>::BalanceCheck()
{
	return BalanceCheck(head->LChild);
}

template<typename Type>
int AVLTree<Type>::BalanceCheck(pNodeType tree)
{
	int LBalance = 1, RBalance = 1;
	if (tree->LChild)
	{	
		LBalance = BalanceCheck(tree->LChild);
		tree->LHeight = tree->LChild->Height;
	}
	else
	{
		tree->LHeight = 0;
	}
	if (tree->RChild)
	{	
		RBalance = BalanceCheck(tree->RChild);
		tree->RHeight = tree->RChild->Height;
	}
	else
	{
		tree->RHeight = 0;
	}
	
	tree->Height = max(tree->LHeight, tree->RHeight) + 1;
	return LBalance && RBalance &&
		tree->BalanceFactor == tree->LHeight - tree->RHeight;
}
#endif

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
void visit(T i)
{cout << i << " ";}    

int main()
{
	AVLTree<int> it;
	int m;
	
	it.Insert(1);
	for (int i = 0; i < 24; ++i)
        it.Insert(rand());
    it.InOrder(visit<int>);
    it.GetMax(m);
    cout << endl << m << endl;
    it.GetMin(m);
    cout << m << endl;

    system("pause");
    return 0;
}


