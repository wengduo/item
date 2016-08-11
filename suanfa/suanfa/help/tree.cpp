

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <ctime>
#include <cassert>
#ifdef _MSC_VER
#include "bst.hpp"
#include "treap.hpp"
#include "rbt.hpp"
#include "splay.hpp"
#include "avl.hpp"
#include "sbt.hpp"
#endif
using namespace std;
/*
int test(const treap_map<int, int>& x)
{
	return x.rbegin()->first;
}*/

int test1()
{
	int curr = clock();
	map<int, int>	m;
	srand(123456789);
	tree::sbt_map<int, int>	f;
	for (int i = 0; i < 1000000; ++i)
	{
		int u, x = rand();
//		ID() = i;
		if (x&1)
		{
			u = rand();
			f[u] = 1;
			m[u] = 1;
		}
		else
		{
			 u = rand();
			 tree::sbt_map<int, int>::iterator x = f.find(u);
			 if (x != f.end())
			 {
				f.erase(x);
			 }
			map<int, int>::iterator t = m.find(u);
			if (t != m.end()) m.erase(t);
			
		}
		//cerr << x << " " << u << endl;
		//cerr << f.size() << " " << m.size() << endl;
		//cerr << endl;
		//if (f.size() != m.size()) cerr << "fuck" << endl;
		assert(f.size() == m.size());
	}
	//cerr << f.size() << " " << m.size() << endl;
	return clock() - curr;
}

template<typename T>
int run_rand()
{
	int curr = clock();
	srand(123456789);
	T f;
	for (int i = 0; i < 100000; ++i)
	{
		int u, x = rand();
		if (x&1)
		{
			u = rand();
			f[u] = 1;
		}
		else
		{
			 u = rand();
			 typename T::iterator x = f.find(u);
			 if (x != f.end())
			 {
				f.erase(x);
			 }
		}
	}
	return clock() - curr;
}

template<typename T>
int run_insert()
{
	int curr = clock();
	srand(123456789);
	T f;
	for (int i = 0; i < 100000; ++i)
	{
		f[i] = 0;
	}
	return clock() - curr;
}
void test_comp()
{
	cerr << run_rand<tree::bst_map<int, int> >() << endl;
	cerr << run_rand<tree::treap_map<int, int> >() << endl;
	cerr << run_rand<tree::rbt_map<int, int> >() << endl;
	cerr << run_rand<tree::splay_map<int, int> >() << endl;
	cerr << run_rand<tree::avl_map<int, int> >() << endl;
	cerr << run_rand<tree::sbt_map<int, int> >() << endl;
	cerr << run_rand<std::map<int, int> >() << endl;
	cerr << endl;

	//cerr << run_insert<tree::bst_map<int, int> >() << endl;
	cerr << run_insert<tree::treap_map<int, int> >() << endl;
	cerr << run_insert<tree::rbt_map<int, int> >() << endl;
	cerr << run_insert<tree::splay_map<int, int> >() << endl;
	cerr << run_insert<tree::avl_map<int, int> >() << endl;
	cerr << run_insert<tree::sbt_map<int, int> >() << endl;
	cerr << run_insert<std::map<int, int> >() << endl;

	cerr << endl;
}

void sbt_test()
{
	tree::sbt_map<int, int> t;
	for (int i = 0; i < 10; ++i) t[i] = i;
	for (int i = 0; i <= 11; ++i) cerr << t.select(i)->first << endl;
	for (int i = 0; i <= 11; ++i) cerr << t.rank(i) << endl;
	cerr << endl;
	tree::sbt_multiset<int> f;
	for (int i = 0; i < 100; ++i) f.insert(123456789);
	for (int i = 0; i < 100; ++i) f.insert(12345678);
	cerr << f.count(0) << endl;
	for (int i = 50; i < 60; ++i) cerr << *f.select(i) << endl;
	cerr << f.rank(12345678) << endl;
	cerr << f.rank(123456789) << endl;
}
int main()
{
	//cerr << run_rand<tree::treap_map<int, int> >() << endl;
	sbt_test();
	cerr << test1() << endl;
	test_comp();
	tree::bst_multiset<int> f;
	tree::bst_multiset<int>::iterator x = f.end();
	--x;
	cerr << * x << endl;
	tree::bst_map<int, int> ff;
	ff.insert(std::make_pair<int, int>(1, 2));
	for (int i = 0; i < 3; ++i) f.insert(3);
	for (tree::bst_multiset<int>::reverse_iterator curr = f.rbegin(); curr != f.rend(); ++curr)
		cerr << *curr << endl;
	f.erase(3);
	cerr << f.count(12345) << endl;
	cerr << f.count(123456789) << endl;
	cerr << f.count(-1) << endl;
	cerr << f.size() << endl;
	return 0;
}
