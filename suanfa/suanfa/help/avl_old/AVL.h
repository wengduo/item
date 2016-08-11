#ifndef __AVL_H__
#define __AVL_H__

#include <stack>
using	namespace	std;

template<typename T> class AVL;

template<typename T>
class AvlNode
{
friend class AVL<T>;
//private:
public:
	AvlNode():	m_LeftChild(0), m_RightChild(0),m_BalanceFactor(0)
	{}
	AvlNode(T _Data):m_LeftChild(0), m_RightChild(0),m_BalanceFactor(0), m_Data(_Data)
	{}
	T			m_Data;
	AvlNode*	m_LeftChild;
	AvlNode*	m_RightChild;
	int			m_BalanceFactor;
};

template<typename T>
class AVL
{
public:
	AvlNode<T>*		root;
	inline		void	SwapData(AvlNode<T>* _X, AvlNode<T>* _Y)							//����������������
	{
		if (!_X || !_Y)	return;
		T	tData;
		tData	=	_X->m_Data, _X->m_Data = _Y->m_Data, _Y->m_Data = tData;

	}
public:
	AVL(AvlNode<T>* init = 0) :  root(init){}
	int			Insert(T it);
	int			Delete(T it);
	AvlNode<T>*	Search(T it);
};

template<typename T>
int		AVL<T>::Insert(T  it)
{
	if (!root)
	{
		root = new AvlNode<T>(it);
		return	1;
	}

	AvlNode<T>* LatestNotBalance, * ParentOfLatestNotBalance;	//�����ƽ����,�����ƽ����ĸ����
	AvlNode<T>*	Current, * ParentOfCurrent;						//��ǰ���ҵ�,���ڲ��ҵ�����
	Current = LatestNotBalance = root;
	ParentOfLatestNotBalance = ParentOfCurrent = 0;

	while (Current)												//���ҹؼ�ֵΪit�Ľ��,���ҳɹ�ʱ���ز���ʧ��
	{
		if (Current->m_BalanceFactor)
		{
			LatestNotBalance =  Current;
			ParentOfLatestNotBalance = ParentOfCurrent;
		}

		if (it < Current->m_Data)
		{
			ParentOfCurrent = Current;
			Current = Current->m_LeftChild;
		}
		else if (it > Current->m_Data)
		{
			ParentOfCurrent = Current;
			Current = Current->m_RightChild;
		}

		else
		{
			return	0;
		}
	}

	AvlNode<T>*		newNode =	new AvlNode<T>;										//�����½��
	newNode->m_Data			=	it;
	newNode->m_BalanceFactor=	0;
	newNode->m_LeftChild	=	newNode->m_RightChild	=	0;

	if (it < ParentOfCurrent->m_Data)
	{
		ParentOfCurrent->m_LeftChild	=	newNode;
	}
	else
	{
		ParentOfCurrent->m_RightChild	=	newNode;
	}

	int		LeftOrRight;

	AvlNode<T>*		SubRoot;														//����������������������
	if (it > LatestNotBalance->m_Data)
	{
		Current		=	LatestNotBalance->m_RightChild;
		SubRoot		=	Current;
		LeftOrRight	=	-1;
	}
	else
	{
		Current		=	LatestNotBalance->m_LeftChild;
		SubRoot		=	Current;
		LeftOrRight	=	1;
	}

	while (Current != newNode)														//�޸�������ƽ������
	{
		if (it > Current->m_Data)
		{
			Current->m_BalanceFactor = -1;
			Current		=	Current->m_RightChild;
		}
		else
		{
			Current->m_BalanceFactor = 1;
			Current		=	Current->m_LeftChild;
		}
	}
	
	if (!LatestNotBalance->m_BalanceFactor ||										//�ж��Ƿ�ƽ��
		!(LatestNotBalance->m_BalanceFactor + LeftOrRight))
	{
		LatestNotBalance->m_BalanceFactor += LeftOrRight;
		return	1;
	}

	if (LeftOrRight == 1)															//�޸�,ʹ֮ƽ��
	{
		if (SubRoot->m_BalanceFactor ==	1)
		{
			LatestNotBalance->m_LeftChild	=	SubRoot->m_RightChild;
			SubRoot->m_RightChild	=	LatestNotBalance;
			LatestNotBalance->m_BalanceFactor	=	0;
			SubRoot->m_BalanceFactor	=	0;
		}
		else
		{
			AvlNode<T>*	RightOfSubRoot	=	SubRoot->m_RightChild;
			SubRoot->m_RightChild		=	RightOfSubRoot->m_LeftChild;
			LatestNotBalance->m_LeftChild =	RightOfSubRoot->m_RightChild;
			RightOfSubRoot->m_LeftChild	=	SubRoot;
			RightOfSubRoot->m_RightChild=	LatestNotBalance;
			switch (RightOfSubRoot->m_BalanceFactor)
			{
			case	0:
				SubRoot->m_BalanceFactor	=	0;
				LatestNotBalance->m_BalanceFactor	=	0;
				break;
			case	-1:
				SubRoot->m_BalanceFactor	=	1;
				LatestNotBalance->m_BalanceFactor	=	0;
				break;
			case	1:
				SubRoot->m_BalanceFactor	=	0;
				LatestNotBalance->m_BalanceFactor	=	-1;
				break;
			}
			RightOfSubRoot->m_BalanceFactor	=	0;
			SubRoot	=	RightOfSubRoot;
		}
	}
	else
	{
		if (SubRoot->m_BalanceFactor ==	-1)
		{
			LatestNotBalance->m_RightChild	=	SubRoot->m_LeftChild;
			SubRoot->m_LeftChild	=	LatestNotBalance;
			LatestNotBalance->m_BalanceFactor	=	0;
			SubRoot->m_BalanceFactor	=	0;
		}
		else
		{
			AvlNode<T>*	LeftOfSubRoot	=	SubRoot->m_LeftChild;
			SubRoot->m_LeftChild		=	LeftOfSubRoot->m_RightChild;
			LatestNotBalance->m_RightChild =	LeftOfSubRoot->m_LeftChild;
			LeftOfSubRoot->m_LeftChild	=	LatestNotBalance;
			LeftOfSubRoot->m_RightChild=	SubRoot;
			switch (LeftOfSubRoot->m_BalanceFactor)
			{
			case	0:
				SubRoot->m_BalanceFactor	=	0;
				LatestNotBalance->m_BalanceFactor	=	0;
				break;
			case	-1:
				SubRoot->m_BalanceFactor	=	0;
				LatestNotBalance->m_BalanceFactor	=	1;
				break;
			case	1:
				SubRoot->m_BalanceFactor	=	-1;
				LatestNotBalance->m_BalanceFactor	=	0;
				break;
			}
			LeftOfSubRoot->m_BalanceFactor	=	0;
			SubRoot	=	LeftOfSubRoot;
		}
	}

	if (!ParentOfLatestNotBalance)
	{
		root	=	SubRoot;
	}
	else
	{
		if (LatestNotBalance	==	ParentOfLatestNotBalance->m_LeftChild)
			ParentOfLatestNotBalance->m_LeftChild	=	SubRoot;
		else
			ParentOfLatestNotBalance->m_RightChild	=	SubRoot;
	}

	return	1;
}

template<typename T>
int			AVL<T>::Delete(T it)
{
	AvlNode<T>*			Current		=	root;	
	stack<AvlNode<T>*>	NodeStack;
	int					LeftOrRight;									//��ǰ�����ջ����������������������
	
	if (Current == 0)	return 0;
	enum{LEFT,RIGHT};
	while (1)
	{
		if (it > Current->m_Data)
		{
			NodeStack.push(Current);
			Current	=	Current->m_RightChild;
			LeftOrRight	=	RIGHT;
		}
		else if (it < Current->m_Data)
		{
			NodeStack.push(Current);
			Current	=	Current->m_LeftChild;
			LeftOrRight	=	LEFT;
		}
		else if (Current->m_LeftChild == 0 && Current->m_RightChild == 0)
		{
			break;
		}
		else if (Current->m_LeftChild != 0)
		{
			AvlNode<T>*	LeftMax			=	Current->m_LeftChild;						//�������������

			if (LeftMax->m_RightChild != 0)												
			{
				NodeStack.push(Current);
				while (LeftMax->m_RightChild)											//��������������Ѱ��
				{
					NodeStack.push(LeftMax);
					LeftMax			=	LeftMax->m_RightChild;
				}
				
				SwapData(Current, LeftMax);
				Current		=		LeftMax;
				LeftOrRight	=		RIGHT;
			}
			else
			{
				switch (LeftMax->m_BalanceFactor)
				{
				case	1:
						SwapData(Current, LeftMax);
						SwapData(LeftMax, LeftMax->m_LeftChild);
						NodeStack.push(Current);
						NodeStack.push(LeftMax);
						Current		=	LeftMax->m_LeftChild;
						break;
				case	0:
						SwapData(Current, LeftMax);
						NodeStack.push(Current);
						Current		=	LeftMax;
						break;
				}
				LeftOrRight	=		LEFT;
			}
		}
		else
		{
			AvlNode<T>*	RightMin			=	Current->m_RightChild;						//����������С���

			if (RightMin->m_LeftChild != 0)												
			{
				NodeStack.push(Current);
				while (RightMin->m_LeftChild)												//����������С����Ѱ��
				{
					NodeStack.push(RightMin);
					RightMin			=	RightMin->m_LeftChild;
				}

				SwapData(Current, RightMin);
				Current		=		RightMin;
				LeftOrRight	=		LEFT;
			}
			else
			{
				switch (RightMin->m_BalanceFactor)
				{
				case	-1:
					SwapData(Current, RightMin);
					SwapData(RightMin, RightMin->m_RightChild);
					NodeStack.push(Current);
					NodeStack.push(RightMin);
					Current		=	RightMin->m_RightChild;
					break;
				case	0:
					SwapData(Current, RightMin);
					NodeStack.push(Current);
					Current		=	RightMin;
					break;
				}
				LeftOrRight	=		RIGHT;
			}

		}

		if (Current == 0)																	//û���ҵ����
		{
			return	0;
		}
	}

	if (Current	==	root)
	{
		delete	Current;
		root	=	0;
		return	1;
	}

	delete	Current;

	if (LeftOrRight == LEFT)										//����ɾ�����ĸ����Ķ�Ӧλ������ΪNULL
	{
		NodeStack.top()->m_LeftChild	=	0;
	}
	else
	{
		NodeStack.top()->m_RightChild	=	0;
	}

	int		HeightDec	=	1;										//�Ե�ǰԪ��Ϊ�����������߶Ƚ������
	Current	=	NodeStack.top();
	NodeStack.pop();
	AvlNode<T>*		ParentOfCurrent;
	while (HeightDec)
	{	
		switch (LeftOrRight)
		{
		case	LEFT:
				Current->m_BalanceFactor	-=	1;
				break;
		case	RIGHT:
				Current->m_BalanceFactor	+=	1;
				break;
		}
		
		if (NodeStack.size())
		{
			ParentOfCurrent	=	NodeStack.top();
		}
		else
		{
			ParentOfCurrent	=	0;
		}

		if (Current->m_BalanceFactor == -1 || Current->m_BalanceFactor == 1)
		{
			return	1;
		}
		else if (Current->m_BalanceFactor == 0)
		{
			if (ParentOfCurrent)										//֪ͨ����,�����ĸ߶ȼ���1
			{
				HeightDec	=	1;
				if (Current->m_Data < ParentOfCurrent->m_Data)
					LeftOrRight = LEFT;
				else
					LeftOrRight = RIGHT;
				Current	=	ParentOfCurrent;
				NodeStack.pop();
			}
			else
			{
				return	1;												//Ϊ��,ֱ�ӷ���
			}
		}
		else if (Current->m_BalanceFactor == 2)
		{
			AvlNode<T>*	t	=	Current->m_LeftChild;
			if (t->m_BalanceFactor == 0)
			{
				Current->m_LeftChild	=	t->m_RightChild;
				t->m_RightChild			=	Current;
				Current->m_BalanceFactor=	1;
				t->m_BalanceFactor		=	-1;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	t;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	t;
						LeftOrRight	=	RIGHT;
					}
				}
				else
				{
					root	=	t;
				}

				return	1;
			}
			else if (t->m_BalanceFactor == 1)
			{
				Current->m_LeftChild	=	t->m_RightChild;
				t->m_RightChild			=	Current;
				Current->m_BalanceFactor=	0;
				t->m_BalanceFactor		=	0;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	t;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	t;
						LeftOrRight	=	RIGHT;
					}

					HeightDec	=	1;
				}
				else
				{
					root	=	t;
					HeightDec	=	0;
					return	1;
				}
			}
			else
			{
				AvlNode<T>*	tr	=	t->m_RightChild;
				Current->m_LeftChild	=	tr->m_RightChild;
				t->m_RightChild			=	tr->m_LeftChild;
				tr->m_LeftChild			=	t;
				tr->m_RightChild		=	Current;
				switch (tr->m_BalanceFactor)
				{
				case	0:
						Current->m_BalanceFactor	=	0;
						t->m_BalanceFactor			=	0;
						break;
				case	1:
						Current->m_BalanceFactor	=	-1;
						t->m_BalanceFactor			=	0;
						break;
				case	-1:
						Current->m_BalanceFactor	=	0;
						t->m_BalanceFactor			=	1;
						break;
				}
				tr->m_BalanceFactor	=	0;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	tr;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	tr;
						LeftOrRight	=	RIGHT;
					}
					HeightDec	=	1;
				}
				else
				{
					root	=	tr;
					return	1;
				}
			}

			Current	=	ParentOfCurrent;
			NodeStack.pop();
		}
		else
		{
			AvlNode<T>*	t	=	Current->m_RightChild;
			if (t->m_BalanceFactor == 0)
			{
				Current->m_RightChild	=	t->m_LeftChild;
				t->m_LeftChild			=	Current;
				Current->m_BalanceFactor=	-1;
				t->m_BalanceFactor		=	1;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	t;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	t;
						LeftOrRight	=	RIGHT;
					}
				}
				else
				{
					root	=	t;
					return	1;
				}

				return	1;
			}
			else if (t->m_BalanceFactor == -1)
			{
				Current->m_RightChild	=	t->m_LeftChild;
				t->m_LeftChild			=	Current;
				Current->m_BalanceFactor=	0;
				t->m_BalanceFactor		=	0;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	t;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	t;
						LeftOrRight	=	RIGHT;
					}
					HeightDec	=	1;
				}
				else
				{
					root	=	t;
					return	1;
				}
			}
			else
			{
				AvlNode<T>*	tr	=	t->m_LeftChild;
				Current->m_RightChild	=	tr->m_LeftChild;
				t->m_LeftChild			=	tr->m_RightChild;
				tr->m_LeftChild			=	Current;
				tr->m_RightChild		=	t;
				switch (tr->m_BalanceFactor)
				{
				case	0:
					Current->m_BalanceFactor	=	0;
					t->m_BalanceFactor			=	0;
					break;
				case	1:
					Current->m_BalanceFactor	=	0;
					t->m_BalanceFactor			=	-1;
					break;
				case	-1:
					Current->m_BalanceFactor	=	1;
					t->m_BalanceFactor			=	0;
					break;
				}
				tr->m_BalanceFactor	=	0;
				if (ParentOfCurrent)
				{
					if (Current->m_Data < ParentOfCurrent->m_Data)
					{
						ParentOfCurrent->m_LeftChild	=	tr;
						LeftOrRight	=	LEFT;
					}
					else
					{
						ParentOfCurrent->m_RightChild	=	tr;
						LeftOrRight	=	RIGHT;
					}

					HeightDec	=	1;
				}
				else
				{
					root	=	tr;
					return	1;
				}
			}

			Current	=	ParentOfCurrent;
			NodeStack.pop();
		}
	}

	return	1;
}

template<typename T>
AvlNode<T>*		AVL<T>::Search(T it)
{
	AvlNode<T>*		Current = root;
	while (Current)
	{
		if (it > Current->m_Data)
		{
			Current	=	Current->m_RightChild;
		}
		else if (it < Current->m_Data)
		{
			Current	=	Current->m_LeftChild;
		}
		else
		{
			return	Current;
		}
	}

	return	0;
}


#endif