#ifndef _TREAP_HPP_
#define _TREAP_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	treap_node_type : basic_bst_node<Traits, treap_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, treap_node_type<Traits> > base;

public:

	int	rdv;

public:

	treap_node_type(const value_type& v = value_type())
		: base(v)
	{
	}

};

template<typename Traits, typename Node>
struct	treap_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

private:

	node_type* heap_adjust_up(node_type* z, node_type* head)
	{
		for (node_type* p = z->p; p != head && z->rdv < p->rdv;)
		{
			base::rotate(p, z == p->l, head);
			p = z->p;
		}
		return z;
	}

public:

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		node_type* z = base::normal_insert_impl(p, elem, head);
		z->rdv = rand();
		return	heap_adjust_up(z, head);
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		node_type* y = z;
		for (;y->l != head || y->r != head;)
		{
			node_type* best = y->l;
			if (best == head) best = y->r;
			if (best == y->l && y->r != head &&
				y->r->rdv < best->rdv) best = y->r;
			base::rotate(y, best == y->l, head);
		}
		(y == y->p->l ? y->p->l : y->p->r) = head;
		return y;
	}


};

MAKE_SET(treap_set, Key, false, treap_node_type, treap_algo);
MAKE_SET(treap_multiset, Key, true, treap_node_type, treap_algo);
MAKE_MAP(treap_map, Key, T, false, treap_node_type, treap_algo);
MAKE_MAP(treap_multimap, Key, T, true, treap_node_type, treap_algo);

}

#endif
