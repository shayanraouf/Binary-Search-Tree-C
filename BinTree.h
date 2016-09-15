// --------------------------------------------- BinTree.h --------------------
// Shayan Raouf CSS343 Section Number
// Creation Date: 1/13/2015
// Date of Last Modification: 1/23/2015
// ----------------------------------------------------------------------------
// Purpose - To create an ADT (Abstract Data Type) of a Binary Search Tree
// ----------------------------------------------------------------------------
// Features - This BST I created supports the following functions:
//			- insert, remove, retrieve, getHeight, bstreeToArray, 
//			  arrayToBSTree, makeEmpty, displaySideways
//			- supports the following operator overloads:
//			operator<<, operator>>, operator=, operator==, operator!=
// **NOTE** SHOULD RUN ON LINUX & Valgrind with no memory leaks***
// ----------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include "NodeData.h"
using namespace std;
class BinTree
{
public:

	// console input and output 
	friend ostream& operator<<(ostream& ostream, const BinTree& rhs);
	friend istream& operator>>(istream& istream, BinTree& rhs);
	 
	//constructors 
	BinTree();
	BinTree(const BinTree& rhs);
	~BinTree();

	//Tree behaviors 
	bool insert(NodeData* data);
	bool remove(NodeData*& data);
	bool retrieve(const NodeData& data, NodeData*& getData);

	int getHeight(const NodeData &) const;

	void bstreeToArray(NodeData*[]);
	void arrayToBSTree(NodeData*[]);
	void makeEmpty();

	// provided below, displays the tree sideways
	void displaySideways() const;			
	
	//operator overloads 
	bool operator==(const BinTree& rhs) const;
	bool operator!=(const BinTree& rhs) const;

	const BinTree& operator=(const BinTree& rhs);
	

private:
	struct Node
	{
		NodeData* data;
		Node* left;
		Node* right;
	};

	Node* root; 

// ----------------------- private helper methods -----------------------------
	Node* insert(Node* parent, NodeData* data, bool& inserted);
	Node* getMax(Node* parent);
	Node* getMin(Node* parent);
	Node* getNodeDataPtr(const NodeData& data, Node* parent) const;

	void inOrderHelper(ostream& ostream, Node* parent) const;
	void remove(Node* parent, NodeData*& data);
	void makeEmpty(Node*& parent);
	void copy(Node* parent);
	void bstreeToArray(NodeData*[], Node* T, int& i);
	void arrayToBSTree(NodeData*[], int start, int end);
	// provided below, helper for displaySideways()
	void sideways(Node*, int) const;			

	int numOfChildren(Node* parent);
	int getDepth(Node* parent) const;
	int numofNodes(Node* parent) const;
	int sizeOf(NodeData*[]) const;

	bool isEqual(Node* left, Node* right) const;
	bool retrieve(const NodeData&, NodeData*& , Node*) const;
// ----------------------------------------------------------------------------
	
};

