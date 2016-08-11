#ifndef _SPLAY_HPP_
#define _SPLAY_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	splay_node_type : public basic_bst_node<Traits, splay_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, splay_node_type<Traits> > base;

public:

	splay_node_type(const value_type& v = value_type())
		: base(v)
	{
	}

};

template<typename Traits, typename Node>
struct	splay_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

public:

	VIRTUAL_FUNCTION
	void after_find(node_type* x, node_type* head)
	{
		base::splay(x, head, head);
	}

	VIRTUAL_FUNCTION
	void after_count(node_type* x, node_type* head)
	{
		base::splay(x, head, head);
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		node_type* z = base::normal_insert_impl(p, elem, head);
		base::splay(z, head, head);
		return	z;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		return base::normal_erase_impl(z, head);
	}
};

MAKE_SET(splay_set, Key, false, splay_node_type, splay_algo);
MAKE_SET(splay_multiset, Key, true, splay_node_type, splay_algo);
MAKE_MAP(splay_map, Key, T, false, splay_node_type, splay_algo);
MAKE_MAP(splay_multimap, Key, T, true, splay_node_type, splay_algo);

}

#endif
