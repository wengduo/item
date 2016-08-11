#ifndef _RBT_HPP_
#define _RBT_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	rbt_node_type : basic_bst_node<Traits, rbt_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, rbt_node_type<Traits> > base;

public:

	enum COLOR {RED, BLACK};
	COLOR color;

public:

	rbt_node_type(const value_type& v = value_type())
		: base(v), color(RED)
	{
	}
};

template<typename Traits, typename Node>
struct	rbt_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

private:

	node_type* rbt_insert_balance_fixup(node_type* z, node_type* head)
	{
		node_type* ret = z;
		while (z->p->color == node_type::RED)
		{
			//z->p是其父亲结点的type_pz子树
			const int type_pz = CHILD_TYPE(z->p, z->p->p);
			//y是z的叔结点
			node_type* y = z->p->p->cld[type_pz^1];
			if (y->color == node_type::RED)
			{
				z->p->color = node_type::BLACK;
				y->color = node_type::BLACK;
				z->p->p->color = node_type::RED;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->cld[type_pz^1])
				{
					z = z->p;
					base::rotate(z, type_pz, head);
				}
				z->p->color = node_type::BLACK;
				z->p->p->color = node_type::RED;
				base::rotate(z->p->p, type_pz^1, head);
				break;
			}
		}
		head->l->color = node_type::BLACK;
		return ret;
	}

	node_type* rbt_erase_balance_fixup(node_type* x, node_type* head)
	{
		while (x != head->l && x->color == node_type::BLACK)
		{
			const int type_x = CHILD_TYPE(x, x->p);
			node_type* w = x->p->cld[type_x^1];
			if (w->color == node_type::RED)
			{
				w->color = node_type::BLACK;
				x->p->color = node_type::RED;
				base::rotate(x->p, type_x, head);
				w = x->p->cld[type_x^1];
			}
			if (w->l->color == node_type::BLACK && w->r->color == node_type::BLACK)
			{
				w->color = node_type::RED;
				x = x->p;
			}
			else
			{
				if (w->cld[type_x^1]->color == node_type::BLACK)
				{
					w->cld[type_x]->color = node_type::BLACK;
					w->color = node_type::RED;
					base::rotate(w, type_x^1, head);
					w = x->p->cld[type_x^1];
				}
				w->color = x->p->color;
				x->p->color = node_type::BLACK;
				w->cld[type_x^1]->color = node_type::BLACK;
				base::rotate(x->p, type_x, head);
				break;
			}
		}
		x->color = node_type::BLACK;
		return x;
	}

public:

	VIRTUAL_FUNCTION
	void	construct_head(node_type* head)
	{
		head->color = node_type::BLACK;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		node_type* z = base::normal_insert_impl(p, elem, head);
		z->color = node_type::RED;
		return	rbt_insert_balance_fixup(z, head);
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		node_type* y = base::normal_erase_impl(z, head);
		if (y->color == node_type::BLACK)
		{
			node_type* x = y->l != head ? y->l : y->r;
			if (x == head) x->p = y->p;
			rbt_erase_balance_fixup(x, head);
			if (x == head) x->p = NULL;
			return y;
		}
		return y;
	}
};

MAKE_SET(rbt_set, Key, false, rbt_node_type, rbt_algo);
MAKE_SET(rbt_multiset, Key, true, rbt_node_type, rbt_algo);
MAKE_MAP(rbt_map, Key, T, false, rbt_node_type, rbt_algo);
MAKE_MAP(rbt_multimap, Key, T, true, rbt_node_type, rbt_algo);

}

#endif
