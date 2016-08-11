#ifndef _SBT_HPP_
#define _SBT_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	sbt_node_type : public basic_bst_node<Traits, sbt_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, sbt_node_type<Traits> > base;

public:

	int size;
	
	sbt_node_type(const value_type& v = value_type())
		: base(v), size(1)
	{
	}

};

template<typename Traits, typename Node>
struct	sbt_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

private:

	void rotate_resize(node_type* t, const int type)
	{
		node_type* p = t->cld[type^1];
		t->size = t->cld[type]->size + p->cld[type]->size + 1;
		p->size = t->size + p->cld[type^1]->size + 1;
	}

	node_type* maintain(node_type* t, const int flag, node_type* head)
	{
		/*
		可以断言，如果是对sbt进行一个插入或者删除操作t一定不是head，
		但是由于对第一个if，t->l和t->r中实际上只有一个需要进行
		maintain，而对不必要的那个的进行可能导致t->cld[flag]为head
		*/
		if (t->cld[flag] == head) return t;
		if (t->cld[flag]->cld[flag]->size > t->cld[flag^1]->size)
		{
			rotate_resize(t, flag^1);
			t = base::rotate(t, flag^1, head);
		}
		else if (t->cld[flag]->cld[flag^1]->size > t->cld[flag^1]->size)
		{
			rotate_resize(t->cld[flag], flag);
			base::rotate(t->cld[flag], flag, head);
			
			rotate_resize(t, flag^1);
			t = base::rotate(t, flag^1, head);
		}
		else
		{
			return t;
		}
		maintain(t->l, false, head);
		maintain(t->r, true, head);
		t = maintain(t, false, head);
		t = maintain(t, true, head);
		return t;
	}

public:

	VIRTUAL_FUNCTION
	void	construct_head(node_type* head)
	{
		head->size = 0;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		node_type* z = base::normal_insert_impl(p, elem, head);
		int flag = CHILD_TYPE(z, p);
		for (node_type* changed = p, *cld = z; changed != head; )
		{
			++changed->size;
			changed = maintain(changed, flag == node_type::RIGHT, head);
			cld = changed, changed = changed->p;
			flag = CHILD_TYPE(cld, changed);
		}
		return	z;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		int flag = 0;
		node_type* y = base::normal_erase_impl_ext(z, flag, head);
		//cld一定不是NULL，但是这里并不用到，实际需要的是flag
		//根据nocow以及wiki，删除并不需要maintain过程，只需要一下size
		for (node_type* changed = y->p, *cld = NULL; changed != head;)
		{
			--changed->size;
			changed = maintain(changed, flag == node_type::LEFT, head);
			cld = changed, changed = changed->p;
			flag = CHILD_TYPE(cld, changed);
		}
		return y;
	}
};

template<typename Traits,
	typename Node,
	typename Algo>
struct SBTAddionalInterface
	: public basic_bst<Traits, Node, Algo>
{
private:

	typedef basic_bst<Traits, Node, Algo> base;

public:

	typedef typename base::iterator iterator;
	typedef typename base::node_type node_type;
	typedef typename base::key_type key_type;
	typedef typename base::value_type value_type;

private:

	node_type* select(node_type* root, int k)
	{
		for (;;)
		{
			const int s = root->l->size;
			if (s + 1 == k) return root;
			k <= s ? (root = root->l) : (k -= s + 1, root = root->r);
		}
	}

	int rank(const key_type& key, node_type* head, helper::int2type<0>)
	{
		int ret = 0;
		for (node_type* which = head->l; which != head; )
		{
			int	u = base::comp(key, KEY(which->data));
			if (u) which = which->l;
			else if(!base::comp(KEY(which->data), key)) return ret + which->l->size + 1;
			else ret += which->l->size + 1, which = which->r;
		}
		return -1;
	}

	int rank(const key_type& key, node_type* head, helper::int2type<1>)
	{
		node_type* p, *x = base::find_first(key, p, head);
		if (x == head) return -1;
		int ret = x->l->size + 1;
		for (node_type* p = x->p; p != head; )
		{
			if (x == p->r) ret += p->l->size + 1;
			x = p, p = p->p;
		}
		return ret;
	}

public:

	iterator select(int k)
	{
		return k < 1 || k > (int)base::size() ? 
				iterator(base::head, base::head) : 
				iterator(select(base::head->l, k), base::head);
	}

	int rank(const key_type& key)
	{
		return rank(key, base::head, base::multi_selector);
	}

};

MAKE_SET_I(sbt_set, Key, false, sbt_node_type, sbt_algo, SBTAddionalInterface);
MAKE_SET_I(sbt_multiset, Key, true, sbt_node_type, sbt_algo, SBTAddionalInterface);
MAKE_MAP_I(sbt_map, Key, T, false, sbt_node_type, sbt_algo, SBTAddionalInterface);
MAKE_MAP_I(sbt_multimap, Key, T, true, sbt_node_type, sbt_algo, SBTAddionalInterface);

}

#endif
