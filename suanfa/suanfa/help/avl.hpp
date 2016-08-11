#ifndef _AVL_HPP_
#define _AVL_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	avl_node_type : public basic_bst_node<Traits, avl_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, avl_node_type<Traits> > base;

public:

	int bf;
	
	avl_node_type(const value_type& v = value_type())
		: base(v), bf(0)
	{
	}

};

template<typename Traits, typename Node>
struct	avl_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

private:

	void ChangeFactorRight(node_type* x)
	{
		node_type* y = x->l;
		//通过枚举可以知道下面的平衡因子调整表达式
		--x->bf -= y->bf > 0 ? y->bf : 0;
		--y->bf += x->bf < 0 ? x->bf : 0;
	}

	void ChangeFactorLeft(node_type* x)
	{
		node_type* y = x->r;
		//通过枚举可以知道下面的平衡因子调整表达式
		++x->bf -= y->bf < 0 ? y->bf : 0;
		++y->bf += x->bf > 0 ? x->bf : 0;
	}

	node_type* RightBalanceFixup(node_type* x, node_type* head)
	{
		if (x->l != head && x->l->bf == -1)
		{
			ChangeFactorLeft(x->l);
			base::rotate(x->l, node_type::LEFT, head);
		}
		ChangeFactorRight(x);
		return base::rotate(x, node_type::RIGHT, head);
	}

	node_type* LeftBalanceFixup(node_type* x, node_type* head)
	{
		if (x->r != head && x->r->bf == 1)
		{
			ChangeFactorRight(x->r);
			base::rotate(x->r, node_type::RIGHT, head);
		}
		ChangeFactorLeft(x);
		return base::rotate(x, node_type::LEFT, head);
	}

	node_type* BalanceFixup(node_type* x, node_type* head)
	{
		if (x->bf == -2) x = LeftBalanceFixup(x, head);
		else if (x->bf == 2) x = RightBalanceFixup(x, head);
		return x;
	}

public:

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		node_type* z = base::normal_insert_impl(p, elem, head);
		node_type* ret = z;
		int flag = CHILD_TYPE(z, p);
		for (node_type* changed = p, *cld = z; changed != head; )
		{
			flag == node_type::LEFT ? ++changed->bf : --changed->bf;
			changed = BalanceFixup(changed, head);
			//可以通过枚举，知道旋转后bf为0，高度不变
			if (changed->bf == 0) break;
			cld = changed, changed = changed->p;
			flag = CHILD_TYPE(cld, changed);
		}
		return	ret;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		int flag = 0;
		node_type* y = base::normal_erase_impl_ext(z, flag, head);
		//cld一定不是NULL，但是这里并不用到，实际需要的是flag
		for (node_type* changed = y->p, *cld = NULL; changed != head;)
		{
			flag == node_type::LEFT ? --changed->bf : ++changed->bf;
			changed = BalanceFixup(changed, head);
			//可以通过枚举，知道旋转后bf非零，高度不变
			if (changed->bf) break;
			cld = changed, changed = changed->p;
			flag = CHILD_TYPE(cld, changed);
		}
		return y;
	}
};

MAKE_SET(avl_set, Key, false, avl_node_type, avl_algo);
MAKE_SET(avl_multiset, Key, true, avl_node_type, avl_algo);
MAKE_MAP(avl_map, Key, T, false, avl_node_type, avl_algo);
MAKE_MAP(avl_multimap, Key, T, true, avl_node_type, avl_algo);

}

#endif
