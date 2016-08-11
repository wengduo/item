#include<iostream>
using namespace std;

#include"MGraph.h"
#include"ALGraph.h"
#include"yhp_set.h"
#include"MinSpanTree.h"
void main()
{
	MGraph<char,int> myg;

	cin>>myg;
	cout<<myg<<endl;
	MinSpanTree<int> mst(myg.GetVexNum()-1);

	myg.Prim(mst);

	mst.Print_MinTree();


}
