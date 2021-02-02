#pragma once

/*
	This datastructure will represent the pyramid as a map.
	The Nodes of this map consist of the number they represent, and two pointers to the two nodes below (child nodes), as well as
	two pointers to the Nodes above (parent nodes)
	In case of Nodes at the border of the pyramid, one parent is always nullptr.
	The root is at the top and both its parent Nodes are assigned to nullptr.

	as a graph this is what it looks like:

			root	| 1st row
		    /  \
		   N	N	| 2nd row
		  / \  / \	
		 N	 N	  N	| 3rd row
			...
*/

#include <list>
#include <iostream>
#include <limits> // so we can set the initial cost of nodes to the max of the int type

// this is the only list type we'll use anyway so there should be no confusion
using std::list;

/*
	This struct represents one node in the tree class
*/
struct Node
{
	Node* lP = nullptr;	// left Parent
	Node* rP = nullptr;	// right Parent
	int value;
	Node* lC = nullptr;	// left Child
	Node* rC = nullptr;	// right Child

	// these are for the path-finding algorithm
	Node* pred = nullptr;	// the predecessor Node
	int cost = std::numeric_limits<int>::min();	// the acummulated cost of reaching this node
};

// use the assingment operator to peek first from the list. (clear and fast to write and read)
list<int>& operator<<(Node* n, list<int>& l);

class Tree
{
	friend std::ostream& operator<<(std::ostream& os, Tree& t);	// the function needs access to the bfsList

public:

	// input the pyramid as a list of figures and construct the tree
	// a bfs sorted list is created on the fly
	Tree(list<int> l);

	// perform a depth-first-search on the tree. add accordingly to a given list
	void dfs(list<Node*>& l, Node* n = nullptr);

	// DEBUGGING ONLY, REMOVE AFTERWARDS
	// test, if after construction the bfs list can be shown again
	// by running a breadth-first-search again on the tree
	void bfs(list<Node*>& l);

	// set the predecessors for all nodes using a sweep algorithm
	// exception: paths with the hightes, not lowest cost will be chosen
	void sweep();

	// returns a list of the Nodes in the lowest row of the pyramid
	list<Node*> groundRow();

private:
	
	Node* root;				// the root of our tree
	int rowSize;			// the number of nodes the current row will have in the end. this value is incremented with each new row.
	list<Node*> bfsList;	// this will be created nearly effortless while constructing the tree

};

// for debugging we wanna be able to print the tree as a list again,
// so we can see if the input was added correctly from the initial list
std::ostream& operator<<(std::ostream& os, Tree& t);