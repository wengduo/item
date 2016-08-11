#ifndef _BST_BASE_HPP_
#define _BST_BASE_HPP_

#include <utility>
#include <iterator>
#include <queue>

namespace tree{

template<typename Traits, typename Derived>
struct	basic_bst_node
{
private:

	typedef Derived					node_type;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::value_allocator value_allocator;
	typedef typename value_allocator::template rebind<node_type>::other
									node_allocator;

public:

	enum{LEFT, RIGHT};

	basic_bst_node(const value_type& v = value_type()) : data(v){}

	value_type		data;
	union
	{
		struct
		{
			node_type* l;
			node_type* r;
		};
		node_type* cld[2];
	};

	node_type* p;

	static node_type* new_node()
	{
		node_allocator node_alloc;
		node_type* s = node_alloc.allocate(1);
		new (s) node_type;
		return s;
	}

	static node_type* new_node(const value_type& v)
	{
		node_allocator node_alloc;
		node_type* s = node_alloc.allocate(1);
		new (s) node_type(v);
		return s;
	}

	static void delete_node(node_type* ptr)
	{
		node_allocator node_alloc;
		node_alloc.destroy(ptr);
		node_alloc.deallocate(ptr, 0);
	}

};

namespace helper
{
	template<typename T1, typename T2>
	struct is_same_type{enum {value=false};};
	template<typename T>
	struct is_same_type<T, T>{enum {value=true};};

	template<int v>
	struct int2type{enum{value=v};};

	template<typename T>
	struct second_type{typedef T value_type;};
	template<typename T1, typename T2>
	struct second_type<std::pair<T1, T2> > {typedef T2 value_type;};

	template<typename T>
	struct first_type{typedef T value_type;};
	template<typename T1, typename T2>
	struct first_type<std::pair<T1, T2> > {typedef T1 value_type;};

	template<typename T>
	struct remove_const{typedef T value_type;};
	template<typename T>
	struct remove_const<const T>{typedef typename remove_const<T>::value_type value_type;};

}

#ifdef	HAS_STATIC_ASSERT
	#define	STATIC_ASSERT(x) static_assert(x, #x)
#else
	namespace
	{
		template <bool x>
			struct STATIC_ASSERTION_FAILURE;
		template <>
			struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
		template<int x>
			struct static_assert_test{};
	}
	#define STATIC_ASSERT(x) typedef static_assert_test<\
									sizeof(STATIC_ASSERTION_FAILURE<(bool)((x)) >)\
									>	static_assert_typedef
#endif

template<typename Key, typename Value,
	typename KeyCompare, typename ValueAllocator,
	bool AllowMulti, bool IsMap>
struct basic_bst_traits_common
{
	typedef Key					key_type;
	typedef Value				value_type;
	typedef KeyCompare			key_compare;
	typedef ValueAllocator		value_allocator;
	typedef	size_t				size_type;
	typedef	typename value_allocator::reference				reference;
	typedef	typename value_allocator::const_reference		const_reference;
	typedef typename value_allocator::pointer				pointer;
	typedef typename value_allocator::const_pointer			const_pointer;

	enum{allow_multi = AllowMulti};
	enum{is_map = IsMap};
	enum{is_set = !IsMap};
};

template<typename Key, typename Value,
	typename KeyCompare, typename ValueAllocator,
	bool AllowMulti, bool IsMap = false>
struct basic_bst_traits_impl 
	: public basic_bst_traits_common<Key, Value, KeyCompare, ValueAllocator, AllowMulti, IsMap>
{
private:

	typedef basic_bst_traits_common<Key, Value, KeyCompare, ValueAllocator, AllowMulti, IsMap> base;

public:
	//依赖项
	typedef typename base::key_type key_type;
	typedef typename base::value_type value_type;

public:
	//接口
	typedef typename base::key_compare value_compare;

	static const key_type& get_key(const value_type& v)
	{
		return v;
	}

	static void set_value(value_type& v, const value_type& o)
	{
		v = o;
	}
};

template<typename Key, typename Value,
	typename KeyCompare, typename ValueAllocator, bool AllowMulti>
struct basic_bst_traits_impl<Key, Value, KeyCompare, 
	ValueAllocator, AllowMulti, true>
	: public basic_bst_traits_common<Key, Value, KeyCompare, ValueAllocator, AllowMulti, true>
{
private:

	typedef basic_bst_traits_common<Key, Value, KeyCompare, ValueAllocator, AllowMulti, true> base;

public:

	typedef typename base::key_type key_type;
	typedef typename base::value_type value_type;

private:

	typedef typename helper::first_type<value_type>::value_type CT1;
	typedef typename helper::remove_const<CT1>::value_type       T1;
	typedef typename helper::second_type<value_type>::value_type T2;

public:

	typedef std::pair<T1, T2>	xvalue_type;
	typedef T2					mapped_type;

	struct value_compare
	{
		bool operator () (const value_type& l, const value_type& r) const
		{
			return comp(l.first, r.first);
		}
		bool operator () (const value_type& l, const key_type& r) const
		{
			return comp(l.first, r);
		}
		bool operator () (const key_type& l, const value_type& r) const
		{
			return comp(l, r.first);
		}
		bool operator () (const key_type& l, const key_type& r) const
		{
			return comp(l, r);
		}
		typename base::key_compare comp;
	};

	static const key_type& get_key(const value_type& v)
	{
		return v.first;
	}

	static void set_value(value_type& v, const value_type& o)
	{
		const_cast<key_type&>(v.first) = o.first;
		v.second = o.second;
	}
};

template<typename Key, typename Value,
	typename KeyCompare, typename ValueAllocator, bool AllowMulti = false
>
struct basic_bst_traits 
	: public basic_bst_traits_impl<
	Key, Value, KeyCompare, ValueAllocator, AllowMulti,
	!helper::is_same_type<Key, Value>::value
	>
{
	
};


#define VIRTUAL_FUNCTION
#define PURE_VIRTUAL_FUNCTION
#define UTILITY_FUNCTION
#define UTILITY_MEMBER
#define UTILITY_TYPE
#define UTILITY_MACRO

#define MUST_HAVE_AN_IMPLEMENTATION false

#ifdef _MSC_VER
//通过静态断言实现
#define FORCE_IMPLEMENTATION(T) STATIC_ASSERT(MUST_HAVE_AN_IMPLEMENTATION)
#else
//引入依赖性名字实现，因为使用这个的肯定是在一个类模板之中
#define FORCE_IMPLEMENTATION(T) typedef typename T::none_exist_type orz
#endif

template<typename Traits, typename Node>
struct	basic_bst_algo
{
private:

	typedef Node						node_type;
	typedef typename Traits::key_type	key_type;
	typedef typename Traits::value_type value_type;

protected:

	UTILITY_TYPE
	struct	iterator
	{
		friend	struct basic_bst_algo;

		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef typename Traits::value_type			value_type;
		typedef int									difference_type;
		typedef int									distance_type;
		typedef typename Traits::pointer				pointer;
		typedef typename Traits::reference			reference;

	private:

		node_type*	curr;
		node_type*	head;

	public:

		iterator(node_type* curr_, node_type* head_) : curr(curr_), head(head_){};

		pointer	operator->() const
		{
			return	&(operator * ());
		}

		reference	operator*() const
		{
			return	curr->data;
		}

		bool	operator == (iterator o) const
		{
			return curr == o.curr;
		}

		bool	operator != (iterator o) const
		{
			return	!(*this == o);
		}

		iterator&	operator ++()
		{
			//头结点++无意义
			if (curr == head) return *this;
			if (curr->r != head)
			{
				curr = curr->r;
				while (curr->l != head) curr = curr->l;
			}
			else
			{
				node_type* y = curr->p;
				while (y != head && curr == y->r) curr = y, y = y->p;
				curr = y;
			}
			return *this;
		}

		iterator operator ++ (int)
		{
			iterator ret(*this);
			++*this;
			return ret;
		}

		iterator& operator -- ()
		{
			//头结点--有意义：实现反向迭代效果
			//if (curr == head) return *this;
			if (curr->l != head)
			{
				curr = curr->l;
				while (curr->r != head) curr = curr->r;
			}
			else if (curr != head)
			{
				node_type* y = curr->p;
				while (y != head && curr == y->l) curr = y, y = curr->p;
				curr = y;
			}
			return *this;
		}

		iterator operator -- (int)
		{
			iterator ret(*this);
			--*this;
			return ret;
		}
	};
	
	UTILITY_TYPE
	struct	const_iterator : public iterator
	{
		friend struct basic_bst_algo;
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef typename Traits::value_type			value_type;
		typedef int									difference_type;
		typedef int									distance_type;
		typedef typename Traits::const_pointer		pointer;
		typedef typename Traits::const_reference		reference;

		const_iterator(node_type* curr_, node_type* head_) : iterator(curr_, head_){};
		const_iterator(iterator other) : iterator(other){}

		pointer	operator->() const
		{
			return	iterator::operator->();
		}

		reference	operator*() const
		{
			return	iterator::operator*();
		}

		const_iterator&	operator ++()
		{
			this->iterator::operator++();
			return	*this;
		}

		const_iterator	operator ++(int)
		{
			const_iterator ret(*this);
			++*this;
			return ret;
		}

		const_iterator&	operator --()
		{
			this->iterator::operator--();
			return	*this;
		}

		const_iterator	operator --(int)
		{
			const_iterator ret(*this);
			--*this;
			return ret;
		}
	};
	
	UTILITY_TYPE
	typedef	std::reverse_iterator<iterator>				reverse_iterator;

	UTILITY_TYPE
	typedef	std::reverse_iterator<const_iterator>		const_reverse_iterator;

	UTILITY_MACRO
	#define	KEY(x) Traits::get_key(x)

	UTILITY_MACRO
	#define CHILD_TYPE(x, p) ((x)==(p)->r)

	UTILITY_FUNCTION
	node_type* rotate(node_type* curr, const int type, node_type* head)
	{
		node_type* p = curr->p, *q = curr->cld[type^1];

		if	(q == head) return curr;
		const int	p_type = CHILD_TYPE(curr, p);

		if (p == head)	p->l = q;
		else p->cld[p_type] = q;
		q->p = p;

		curr->cld[type^1] = q->cld[type];
		if (q->cld[type] != head) q->cld[type]->p = curr;
		
		q->cld[type] = curr;
		curr->p = q;

		return q;
	}

	UTILITY_FUNCTION
	node_type* find_one_of(const key_type& key, node_type*& p, node_type* head)
	{
		p = head;
		for (node_type* which = head->l; which != head; )
		{
			int	u = comp(key, KEY(which->data));
			if (u) p = which, which = which->l;
			else if(!comp(KEY(which->data), key)) return which;
			else p = which, which = which->r;
		}
		return head;
	}

	UTILITY_FUNCTION
	node_type* find_first(const key_type& key, node_type*& p, node_type* head)
	{
		iterator iter(find_one_of(key, p, head), head);
		while (iter.curr != head)
		{
			iterator x(iter);
			--x;
			if (x.curr == head || comp(KEY(x.curr->data), KEY(iter.curr->data))) break;
			iter = x;
		}
		return iter.curr;
	}

	UTILITY_FUNCTION
	node_type* find_last(const key_type& key, node_type*& p, node_type* head)
	{
		iterator iter(find_one_of(key, p, head), head);
		while (iter.curr != head)
		{
			iterator x(iter);
			++x;
			if (x.curr == head || comp(KEY(iter.curr->data), KEY(x.curr->data))) break;
			iter = x;
		}
		return iter.curr;
	}

	UTILITY_FUNCTION
	node_type*	successor(node_type* p, node_type* head)
	{
		iterator iter(p, head);
		++iter;
		return iter.curr;
	}

	UTILITY_FUNCTION
	node_type*	predecessor(node_type* p, node_type* head)
	{
		iterator iter(p, head);
		--iter;
		return iter.curr;
	}

	UTILITY_FUNCTION
	node_type* get_curr(iterator iter)
	{
		return iter.curr;
	}

	UTILITY_FUNCTION
	node_type* get_head(iterator iter)
	{
		return iter.head;
	}

	UTILITY_FUNCTION
	node_type*	normal_insert_impl_ext(node_type* p, const value_type& elem, int& flag, node_type* head)
	{
		node_type* z = node_type::new_node(elem);
		z->p = p, z->l = z->r = head;
		if	(p == head) head->l = z;
		else if (comp(KEY(elem), KEY(p->data))) p->l = z;
		else p->r = z;
		flag = CHILD_TYPE(z, p);
		return	z;
	}

	UTILITY_FUNCTION
	node_type*	normal_insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		int flag = 0;
		return	normal_insert_impl_ext(p, elem, flag, head);
	}

	UTILITY_FUNCTION
	node_type*	normal_erase_impl_ext(node_type* z, int& flag, node_type* head)
	{
		node_type* y = z->l == head || z->r == head ?
						z : successor(z, head);
		node_type* x = y->l != head ? y->l : y->r;
		if (x != head) x->p = y->p;
		flag = CHILD_TYPE(y, y->p);
		(y == y->p->l ? y->p->l : y->p->r) = x;
		if (y != z) Traits::set_value(z->data, y->data);
		return y;
	}

	UTILITY_FUNCTION
	node_type*	normal_erase_impl(node_type* z, node_type* head)
	{
		int flag = 0;
		return normal_erase_impl_ext(z, flag, head);
	}

	UTILITY_FUNCTION
	void splay(node_type* x, node_type* dest, node_type* head)
	{
		if (x == dest || x == head) return;
		while (x->p != dest)
		{
			node_type* y = x->p, * z = y->p;
			const int type_x = CHILD_TYPE(x, y);
			const int type_y = CHILD_TYPE(y, z);
			if (z == dest) rotate(y, type_x^1, head);
			else if (type_x == type_y)
			{
				rotate(z, type_y^1, head);
				rotate(y, type_x^1, head);
				
			}
			else
			{
				rotate(y, type_x^1, head);
				rotate(z, type_y^1, head);
			}
		}
	}

	VIRTUAL_FUNCTION
	void construct_head(node_type* head){}

	VIRTUAL_FUNCTION
	void after_find(node_type* x, node_type* head){}

	VIRTUAL_FUNCTION
	void after_count(node_type* x, node_type* head){}

	PURE_VIRTUAL_FUNCTION
	node_type*	insert_impl(node_type* p, const value_type& elem, node_type* head)
	{
		FORCE_IMPLEMENTATION(Traits);
		return NULL;
	}

	PURE_VIRTUAL_FUNCTION
	node_type*	erase_impl(node_type* z, node_type* head)
	{
		FORCE_IMPLEMENTATION(Traits);
		return NULL;
	}

protected:

	UTILITY_MEMBER
	typename Traits::key_compare comp;

	UTILITY_MEMBER
	helper::int2type<Traits::allow_multi>	multi_selector;
};

template<typename Traits, typename Node, typename Algo>
struct	basic_bst : protected Algo
{
private:

	typedef Algo		base;

public:

	typedef typename Traits::size_type					size_type;
	typedef Node										node_type;
	typedef typename Traits::key_type					key_type;
	typedef typename Traits::value_type					value_type;
	typedef typename Traits::reference					reference;
	typedef typename Traits::const_reference			const_reference;
	typedef typename Traits::pointer					pointer;
	typedef typename Traits::const_pointer				const_pointer;
	typedef typename Algo::iterator						iterator;
	typedef typename Algo::reverse_iterator				reverse_iterator;
	typedef typename Algo::const_iterator				const_iterator;
	typedef typename Algo::const_reverse_iterator		const_reverse_iterator;

private:

	void destroy(node_type* curr)
	{
		if (curr == head) return;

		std::queue<node_type*> q;
		for (q.push(curr); !q.empty(); )
		{
			node_type* curr = q.front(); q.pop();
			if (curr->l != head) q.push(curr->l);
			if (curr->r != head) q.push(curr->r);
			node_type::delete_node(curr);
		}
	}

	void	clear_impl()
	{
		destroy(head->l);
		tot_size = 0;
		head->l = head;
	}

public:
	
	basic_bst()
	{
		head = new node_type;
		head->l = head;
		base::construct_head(head);
		tot_size = 0;
	}
	
	~basic_bst()
	{
		clear();
		delete head;
	}

	//容量相关接口
	size_type size() const {return tot_size;}
	bool	empty() const {return size() == 0;}
	size_type max_size() const {return -1;}
	void clear(){clear_impl();}

	void	swap(basic_bst& o)
	{
		std::swap(tot_size, o.tot_size);
		std::swap(head, o.head);
	}

	//迭代器相关接口
	iterator begin()
	{
		node_type* curr = head;
		while (curr->l != head) curr = curr->l;
		return iterator(curr, head);
	}
	
	iterator end(){return iterator(head, head);}
	reverse_iterator rbegin(){return	reverse_iterator(end());}
	reverse_iterator rend() {return	reverse_iterator(begin());}
	const_iterator	begin() const{return const_cast<basic_bst*const>(this)->begin();}
	const_iterator	end() const{return const_cast<basic_bst*const>(this)->end();}
	const_reverse_iterator	rbegin() const{return const_cast<basic_bst*const>(this)->rbegin();}
	const_reverse_iterator	rend() const{return const_cast<basic_bst*const>(this)->rend();}

	//查找
	iterator find(const key_type& key)
	{
		node_type* p, *z = base::find_one_of(key, p, head);
		base::after_find(z, head);
		return iterator(z, head);
	}

	//插入
	node_type* insert(const value_type& elem, helper::int2type<0>)
	{
		node_type* p, *z = base::find_one_of(KEY(elem), p, head);
		if (z == head) {++tot_size; z = base::insert_impl(p, elem, head);}
		return z;
	}

	/*
		如果已经存在相同的则找到最后一个相同的。
		如果最后一个相同的没有右子树，则在其右子树上插入。
		否则在其后继的左子树上插入。
	*/
	node_type* insert(const value_type& elem, helper::int2type<1>)
	{
		node_type* p, *z = base::find_last(KEY(elem), p, head);
		if (z != head)
		{
			if (z->r == head)
			{
				p = z;
			}
			else
			{
				iterator x(z, head);
				++x;
				p = base::get_curr(x);
			}
		}
		++tot_size;
		return base::insert_impl(p, elem, head);
	}

	iterator insert(const value_type& elem)
	{
		node_type* z = insert(elem, base::multi_selector);
		return iterator(z, head);
	}

	//删除
	void erase(iterator iter)
	{
		if (base::get_curr(iter) == head) return;
		node_type* z = erase_impl(base::get_curr(iter), head);
		node_type::delete_node(z);
		--tot_size;
	}

	void	erase(const key_type& key, helper::int2type<0>)
	{
		node_type* p, *z = base::find_one_of(key, p, head);
		erase(iterator(z, head));
	}

	void	erase(const key_type& key, helper::int2type<1>)
	{
		/*
		删除一个结点后，可能导致后一个结点跑到x前面。
		可以把下面的代码改造为反复迭代的版本，以提高执行效率。
		node_type* p, *z = base::find_first(key, p, head);
		for (iterator x(z, head); base::get_curr(x) != head && !comp(key, KEY(base::get_curr(x)->data));)
		{
			iterator to_del = x++;
			erase(to_del);
		}
		*/
		for (;;)
		{
			node_type* p, *z = base::find_one_of(key, p, head);
			if (z == head) break;
			erase(iterator(z, head));
		}
	}

	void	erase(const key_type& key)
	{
		erase(key, base::multi_selector);
	}

	//计数
	size_type count(const key_type& key, helper::int2type<0>)
	{
		node_type* p, *z = base::find_one_of(key, p, head);
		if (z != head) base::after_count(z, head);
		return z == head ? 0 : 1;
	}

	size_type count(const key_type& key, helper::int2type<1>)
	{
		node_type* p, *z = base::find_first(key, p, head);
		size_type ret = 0;
		for (iterator x(z, head); base::get_curr(x) != head && !base::comp(key, KEY(base::get_curr(x)->data)); ++x)
		{
			++ret;
		}
		if (ret) base::after_count(z, head);
		return ret;
	}

	size_type count(const key_type& key)
	{
		return count(key, base::multi_selector);
	}

protected:

	typename Traits::size_type				tot_size;
	node_type*								head;

};

template<typename Traits,
	typename Node,
	typename Algo>
struct TrivialAddionalInterface
	: public basic_bst<Traits, Node, Algo>
{
};

/*
	set转发
*/
template<typename Traits,
	template<typename> class NodeTemplate,
	template<typename, typename> class AlgoTemplate,
	template<typename, typename, typename> class AdditionalInterface>
struct basic_set
	: public AdditionalInterface<
			Traits,
			NodeTemplate<Traits>,
			AlgoTemplate<Traits, NodeTemplate<Traits> >
			>
{
};

/*
	map转发
	根据是不是multimap嵌入operator []
*/

template<typename Traits,
	typename Node,
	typename Algo,
	int IsMulti,
	template<typename, typename, typename> class AdditionalInterface>
struct basic_map_dispatcher
	: public AdditionalInterface<Traits, Node, Algo>
{
private:

	typedef AdditionalInterface<Traits, Node, Algo> base;

public:

	typedef typename base::key_type key_type;
	typedef typename base::value_type value_type;
	typedef typename Traits::xvalue_type xvalue_type;
	typedef typename Traits::mapped_type mapped_type;

public:

	mapped_type& operator [] (const key_type& key)
	{
		value_type dummy;
		const_cast<key_type&>(dummy.first) = key;
		return base::insert(dummy)->second;
	}
};

template<typename Traits,
	typename Node,
	typename Algo,
	template<typename, typename, typename> class AdditionalInterface>
struct basic_map_dispatcher<Traits, Node, Algo, true, AdditionalInterface>
	: public AdditionalInterface<Traits, Node, Algo>
{
private:

	typedef AdditionalInterface<Traits, Node, Algo> base;

public:

	typedef typename base::key_type key_type;
	typedef typename base::value_type value_type;
	typedef typename Traits::xvalue_type xvalue_type;
	typedef typename Traits::mapped_type mapped_type;
};

template<typename Traits,
	template<typename> class NodeTemplate,
	template<typename, typename> class AlgoTemplate,
	template<typename, typename, typename> class AdditionalInterface>
struct basic_map
	: public basic_map_dispatcher<
			Traits,
			NodeTemplate<Traits>,
			AlgoTemplate<Traits, NodeTemplate<Traits> >,
			Traits::allow_multi,
			AdditionalInterface
			>
{
private:
	typedef basic_map_dispatcher<
			Traits,
			NodeTemplate<Traits>,
			AlgoTemplate<Traits, NodeTemplate<Traits> >,
			Traits::allow_multi,
			AdditionalInterface
			> base;
	
public:

	typedef typename base::iterator iterator;
	typedef typename Traits::value_type value_type;
	typedef typename Traits::xvalue_type xvalue_type;

public:

	iterator insert(const xvalue_type& v)
	{
		return base::insert(reinterpret_cast<const value_type&>(v));
	}

};

#define MAKE_SET(name, Key, Multi, TNode, TAlgo) \
template<typename Key,\
	typename Compare = std::less<Key>,\
	typename Allocator = std::allocator<Key> >\
struct name \
	: public basic_set<\
			basic_bst_traits<Key, Key, Compare, Allocator, Multi>,\
			TNode, TAlgo,\
			TrivialAddionalInterface\
		>\
{\
}

#define MAKE_MAP(name, Key, T, Multi, TNode, TAlgo) \
template<typename Key, typename T,\
	typename Compare = std::less<Key>,\
	typename Allocator = std::allocator<std::pair<const Key, T> > >\
struct name\
	: public basic_map<\
			basic_bst_traits<Key, std::pair<const Key, T>, Compare, Allocator, Multi>, \
			TNode, TAlgo,\
			TrivialAddionalInterface\
		>\
{\
}

#define MAKE_SET_I(name, Key, Multi, TNode, TAlgo, AddionalInterface) \
template<typename Key,\
	typename Compare = std::less<Key>,\
	typename Allocator = std::allocator<Key> >\
struct name \
	: public basic_set<\
			basic_bst_traits<Key, Key, Compare, Allocator, Multi>,\
			TNode, TAlgo,\
			AddionalInterface\
		>\
{\
}

#define MAKE_MAP_I(name, Key, T, Multi, TNode, TAlgo, AddionalInterface) \
template<typename Key, typename T,\
	typename Compare = std::less<Key>,\
	typename Allocator = std::allocator<std::pair<const Key, T> > >\
struct name\
	: public basic_map<\
			basic_bst_traits<Key, std::pair<const Key, T>, Compare, Allocator, Multi>, \
			TNode, TAlgo,\
			AddionalInterface\
		>\
{\
}

}

#endif
