#include "Tree.h"

/*
		ABOUT THE COMMENTS:
		"// ..." means that this line of code has already been explained elsewhere, look it up there.
				 elsewhere typically means in the same scope a couple of lines above or at the declaration in the header file
*/

Tree::Tree(list<int> l)
{
	root = new Node;
	bfsList.push_back(root);	// add the node to the bfs List ( this has nothing to do with construction itself, but the list might be a handy by-product
	root << l;	// assing the next value of l to the node and remove it from the list

	// this is so the sweep algorithm can be used:
	// the root cost must not be minimum/maximum, so there is no over/underflow
	root->cost = root->value;

	// TIPP: look at the description and graphic at the beginning of the Tree.h file in order to understand, how the tree is constructed
	
	// let's add the next Node
	Node* n = new Node;
	bfsList.push_back(n);	// add the node to the bfs List ( this has nothing to do with construction itself, but the list might be a handy by-product
	n << l;			// assing the next value of l to the node and remove it from the list
	n->rP = root;	// the root is it's right parent
	root->lC = n;	// it therefore is the root's left child

	// and the next one...
	n = new Node;
	bfsList.push_back(n);	// add the node to the bfs List ( this has nothing to do with construction itself, but the list might be a handy by-product
	n << l;			// ...
	n->lP = root;	// the root is it's left parent
	root->rC = n;	// it therefore is the root's right child

	// these variables will be needed to regulary add an arbitrary number of nodes to our tree in a loop
	Node* nB;		// beginning node, i.e. the first node in the current row of the pyramid map
	Node* nC;		// current node, i.e. the currently last node in the current row of the pyramid map
	int nodeNum;	// the number of nodes the current row just has

	// the last beginning node was the first node of row two:
	nB = root->lC;

	// the last current node was the second node of row two:
	nC = root->rC;

	// the now current row (2) has up to 2 nodes:
	rowSize = 2;

	// row 2 already has two nodes:
	nodeNum = 2;

	// having added the second row we may now start iterating regulary to add new nodes
	while (!l.empty())	// ... as long as the pyramid isn't complete, i.e. when the list is empty
	{
		n = new Node;
		bfsList.push_back(n);	// add the node to the bfs List ( this has nothing to do with construction itself, but the list might be a handy by-product
		n << l;					// ...

		if (nodeNum == rowSize)	// it's time to step to the next row
		{
			n->rP = nB;
			nB->lC = n;
			nB = n;			// we've got our new beginning node in the new row
			nC = n;			// and it's also the current latest node therefore

			nodeNum = 1;	// there is only one node in the row yet, the one we've just added
			rowSize++;		// this row is one node bigger than the previous one

			if (!l.empty())	// we can continue in the new row just like before
			{
				n = new Node;
				bfsList.push_back(n);	// add the node to the bfs List ( this has nothing to do with construction itself, but the list might be a handy by-product
				n << l;					// ...
			}
			else			// something's odd about the number of figures in the list:
			{
				std::cerr << "warning: the list turned out to be emtpy in the middle of a row!" << std::endl;
				break;		// can't add anymore nodes
			}
		}

		n->lP = nC->rP;		// set the left parent
		nC->rP->rC = n;		// adopt the node by the left parent

		if (nodeNum < rowSize - 1)	// only then there is a right parent to the new Node and
								// a right right grand-parent to the (previous) current Node
		{
			n->rP = nC->rP->rP->rC;
			nC->rP->rP->rC->lC = n;
		}

		nodeNum++;			// we should've added one node
		nC = nC->rP->rC;	// which is now the current node
	}
}

void Tree::dfs(list<Node*>& l, Node*n)
{
	if (n == nullptr)	// only true for the first call (not for recursive ones)
	{
		dfs(l, root);	// start the search at the root
		return;			// we're all done, all rec calls have returned
	}

	// this part will be executed in the recursive calls

	// first of all, check if n has been explored already
	for (Node* nl : l)
		if (n == nl)
			return; // this is a known node

	// o.k., we've got a new one alright
	if (n->lC != nullptr)
		dfs(l, n->lC);
	if (n->rC != nullptr)
		dfs(l, n->rC);

	l.push_back(n);
}

void Tree::bfs(list<Node*>& l)
{
	list<Node*> queue = list<Node*>();
	queue.push_back(root);

	while (!queue.empty())
	{
		Node* n = queue.front();
		queue.pop_front();

		// check if the node is explored already
		bool newNode = true;
		for (Node* nl : l)
			if (n == nl)	// known node -> dead end
			{
				newNode = false;
				break;
			}

		if (!newNode)
			continue;

		// o.k., we've got a new one!
		l.push_back(n);

		// go for the children
		if (n->lC != nullptr)
			queue.push_back(n->lC);

		if (n->rC != nullptr)
			queue.push_back(n->rC);
	}

	bfsList = l;
	return;
}

void Tree::sweep()
{
	for (Node* n : bfsList)
	{
		// relax the child-nodes:
		if (n->lC != nullptr)	// there is a left child to be relaxed
		{
			// this is the important step, where the currently shortest path to n->lC is updated
			if (n->cost + n->lC->value > n->lC->cost)
			{
				n->lC->cost = n->cost + n->lC->value;	// this is the updated cost for n->lC
				n->lC->pred = n;						// make n the new predecessor
			}
		}

		if (n->rC != nullptr)	// there is a right child to be relaxed
		{
			// ...
			if (n->cost + n->rC->value > n->rC->cost)
			{
				n->rC->cost = n->cost + n->rC->value;
				n->rC->pred = n;
			}
		}
	}
}

list<Node*> Tree::groundRow()
{
	Node* n = root;

	// go find the leftest node in the ground row
	while (n->lC != nullptr)
		n = n->lC;

	auto l = list<Node*>();
	// add all ground row nodes to the list
	for (int i = 0; i < rowSize-1; i++)
	{
		l.push_back(n);
		n = n->rP->rC;	// go one node to the right in the same row
	}

	return l;
}

list<int>& operator<<(Node* n, list<int>& l)
{
	n->value = l.front();
	l.pop_front();
	return l;
}

std::ostream& operator<<(std::ostream& os, Tree& t)
{
	/*/ put everything in curled braces
	os << "{";

	// iterate over the tree to output all nodes' values
	for (Node* n : t.bfsList)
		os << n->value << "; ";

	// end curled braces
	os << "}";
	//*/

	//different approach: output as a tree, not as a list
	int r = t.rowSize;
	auto it = t.bfsList.begin();
	
	while (--r >= 0)
	{
		for (int i = 0; i < r; i++)
			os << ' ';
		for (int i = t.rowSize - r; i > 0; i--)
		{
			os << (*it)->value << ' ';
			it++;
		}

		os << std::endl;
	}

	//*/

	return os;
}
