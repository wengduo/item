#ifndef _BST_HPP_
#define _BST_HPP_

#ifdef _MSC_VER
#include "bst_base.hpp"
#endif

namespace tree{

template<typename Traits>
struct	bst_node_type : public basic_bst_node<Traits, bst_node_type<Traits> >
{
private:

	typedef typename Traits::value_type value_type;
	typedef basic_bst_node<Traits, bst_node_type<Traits> > base;

public:

	bst_node_type(const value_type& v = value_type())
		: base(v)
	{
	}

};

template<typename Traits, typename Node>
struct	bst_algo : public basic_bst_algo<Traits, Node>
{
private:

	typedef basic_bst_algo<Traits, Node> base;
	
	typedef Node						node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::key_type	key_type;

public:

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		return	base::normal_insert_impl(p, elem, head);
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		return base::normal_erase_impl(z, head);
	}
};

MAKE_SET(bst_set, Key, false, bst_node_type, bst_algo);
MAKE_SET(bst_multiset, Key, true, bst_node_type, bst_algo);
MAKE_MAP(bst_map, Key, T, false, bst_node_type, bst_algo);
MAKE_MAP(bst_multimap, Key, T, true, bst_node_type, bst_algo);

}

#endif
