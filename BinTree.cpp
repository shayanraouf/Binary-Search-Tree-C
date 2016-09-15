// --------------------------------------------- BinTree.cpp --------------------
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
#include "stdafx.h"
#include "BinTree.h"
#include "NodeData.h"

// ------------------------------------ BinTree -------------------------------
// Description: Defauly constructor that creates an empty tree
// ----------------------------------------------------------------------------
BinTree::BinTree()
{
	root = NULL;
}

// ------------------------------------Poly------------------------------------
// Description: Copy Constructor 
// Preconditions: Assignment operator= overloaded
// ----------------------------------------------------------------------------
BinTree::BinTree(const BinTree& rhs)
{
	root = NULL;
	*this = rhs;
}

// ------------------------------------~Poly-----------------------------------
// Description: Destructor destroys dynamically allocated array
// ----------------------------------------------------------------------------
BinTree::~BinTree()
{
	makeEmpty();
}

// ------------------------------------ Insert --------------------------------
// Description: 
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
bool BinTree::insert(NodeData* data)
{
	if (root == NULL)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		root = newNode;
		return true;
	}
	bool inserted; 
	insert(root, data, inserted);
	return inserted;
}

// ------------------------------------ Insert --------------------------------
// Description: Private helper method
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::insert(Node* parent, NodeData* data, bool& inserted)
{

	if (parent == NULL)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;
		parent = newNode;
		inserted = true;
	}
	else
	{
		if (*data < *parent->data)
		{
			inserted = true;
			parent->left = insert(parent->left, data, inserted); // go left
		}
		else if (*data > *parent->data)
		{
			inserted = true;
			parent->right = insert(parent->right, data, inserted); // go right
		}
		else if (*data == *parent->data)
		{
			inserted = false;
		}
	}

	return parent;
}

// -------------------------------- DeleteList --------------------------------
// Description: Recursively traverses (Post-Order Traversal) the BST and 
// deletes the NodeData and Node
// Precondition: root must not be NULL
// Features: Calls private helper function 
// ----------------------------------------------------------------------------
void BinTree::makeEmpty()
{
	makeEmpty(root);
}

// -------------------------------- DeleteList --------------------------------
// Description: Private 
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
void BinTree::makeEmpty(Node* &parent)
{
	if (parent != NULL)
	{
		makeEmpty(parent->left);
		makeEmpty(parent->right);
		delete parent->data;
		parent->data = NULL;
		delete parent;
		parent = NULL;
	}
}

// ------------------------------------ Remove --------------------------------
// Description: 
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
bool BinTree::remove(NodeData*& data)
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		remove(root, data);
		return true;
	}
}

// ------------------------------------ Remove --------------------------------
// Description: Private helper function 
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
void BinTree::remove(Node* parent, NodeData*& data)
{
	//----------- left sub tree ---------------------
	if (parent->left->data == data)
	{
		// Case 1: no children 
		if (numOfChildren(parent->left) == 0) 
		{
			delete parent->left->data;
			delete parent->left;
			parent->left = NULL;
		}
		// Case 2: One child 
		else if(numOfChildren(parent->left) == 1) 
		{
			Node* nodeToDelete = parent->left;
			if (parent->left->left == NULL)
			{
				parent->left = parent->left->right;
			}
			else
			{
				parent->left = parent->left->left;
			}
			delete nodeToDelete->data;
			delete nodeToDelete;
		}
		else  // Case 3: two children
		{
			// replace value with the min of the left sub-tree
			parent->left->data = getMin(parent->left->right)->data; 
			// recursively call helper method 
			// to delete the replaced value Node
			remove(parent->left, parent->left->data);  
		}
		
	}

	//----------- right sub tree ---------------------
	else if (parent->right->data == data)
	{
		// Case 1: no children
		if (numOfChildren(parent->right) == 0)  
		{
			delete parent->right->data;
			delete parent->right;
			parent->right = NULL;
		}
		// Case 2: One child 
		else if (numOfChildren(parent->right) == 1) 
		{
			// save to delete later
			Node* nodeToDelete = parent->right; 

			// if left child on right sub-tree is NULL
			if (parent->right->left == NULL) 
			{
				parent->right = parent->right->left;
			}
			else
			{
				parent->right = parent->right->right;
			}
			// free memory previously saved
			delete nodeToDelete->data;
			delete nodeToDelete; 
		}
		else  // Case 2: One child 
		{
			// replace value with the min 
			// of the right sub-tree
			parent->right->data = getMin(parent->right->left)->data; 
			// recursively call helper method 
			// to delete the replaced value Node
			remove(parent->right, parent->right->data); 
		}
	}

	// go left
	else if (data < parent->data)
	{
		remove(parent->left, data);
	}

	// go right
	else if (data > parent->data)
	{
		remove(parent->right, data);
	}

}


// ------------------------------------ getMax --------------------------------
// Description: Private helper method
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::getMax(Node* parent)
{
	if (parent == NULL)
	{
		return NULL;
	}
	else if (parent->right == NULL)
	{
		return parent;
	}
	else
	{
		return getMax(parent->right);
	}
}

// ------------------------------------ getMin --------------------------------
// Description: Private helper method
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::getMin(Node* parent)
{
	if (parent == NULL)
	{
		return NULL;
	}
	else if (parent->left == NULL)
	{
		return parent;
	}
	else
	{
		return getMin(parent->left);
	}
}

// ------------------------------------ NumOfChildren -------------------------
// Description: Private helper method returns the number of children 
//				a node has 
// Precondition: NONE
// Features: returns the number of child nodes a parent node has
// ----------------------------------------------------------------------------
int BinTree::numOfChildren(Node* parent)
{
	if (parent->left == NULL && parent->right == NULL)
	{
		return 0;
	}
	else if (parent->left != NULL && parent->right != NULL)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

// ------------------------------------ retrieve ------------------------------
// Description: Given a const NodeData&, this function returns a bool
//				if the data exists in the array and updates NodeData*&
//				with that data found
// Precondition: private retrieve(...) helper function created 
// Features: Calls private helper function
// ----------------------------------------------------------------------------
bool  BinTree::retrieve(const NodeData& data, NodeData*& getData)
{
	return retrieve(data, getData, root);
}

// ------------------------------------ retrieve ------------------------------
// Description: Private helper method
// Precondition: NONE
// Features: recursively goes left and right until found. returns true if
//			 found and false otherwise. 
// ----------------------------------------------------------------------------
bool  BinTree::retrieve(const NodeData& data, NodeData*& getData, 
	Node* parent) const
{
	if (parent != NULL)
	{
		// found
		if (data == *parent->data)
		{
			NodeData* retVal(parent->data);
			getData = retVal;
			return true;
		}
		// go left
		else if (data < *parent->data) 
		{
			return retrieve(data, getData, parent->left);
		}
		// go right
		else if (data > *parent->data) 
		{
			return retrieve(data, getData, parent->right);
		}
	}
	
	getData = NULL;
	return false;
}


// ------------------------------------ getHeight ----------------------------
// Description: Private helper method
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
int BinTree::getHeight(const NodeData& data) const
{

	Node* get = getNodeDataPtr(data, root);
	if (get != NULL)
	{
		return getDepth(get);
	}
}

// ------------------------------------ getDepth ----------------------------
// Description: Private helper method
// Precondition:
// Features: 
// ----------------------------------------------------------------------------
int BinTree::getDepth(Node* parent) const
{
	// Base case
	if (parent == NULL)
		return 0;

	int left = getDepth(parent->left) + 1;
	int right = getDepth(parent->right) + 1;

	// returns the max of the two
	if (left > right)
	{
		return left;
	}
	else
	{
		return right;
	}
	
}

// ------------------------------------ getNodeDataPtr ----------------------------
// Description: Private helper function that traverses the tree with a given
//				NodeData and returns the Node* pointer associated with it
// Precondition: NONE
// Features: Traverses the tree using an Dept First Search approach with a given
//			 NodeData and returns the Node* pointer 
// ----------------------------------------------------------------------------
BinTree::Node* BinTree::getNodeDataPtr(const NodeData& data, 
	Node* parent) const
{
	if (parent != NULL)
	{
		// found
		if (data == *parent->data) 
		{
			return parent;
		}
		// go left
		else if (data < *parent->data) 
		{
			return getNodeDataPtr(data, parent->left);
		}
		// go right
		else if (data > *parent->data) 
		{
			return getNodeDataPtr(data, parent->right);
		}
	}
	return NULL;
}

// ------------------------------------ bstreeToArray ------------------------
// Description: Builds a balanced BST from 
//				a sorted array of NodeData* pointers
// Precondition: makeEmpty() , operator= and NumofNodes(...) 
//		         and bstreeToArray(...) helper functionhave been created
// Features: Creates a new copy of BST and calls helper function
// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[])
{
	// Creates a new copy of BST
	BinTree T; 
	T = *this; 
	// deletes the existing one 
	makeEmpty(); 

	// calls NumofNodes to be used as our arraysize
	int arraySize = numofNodes(root);
	array[arraySize];
	int index = 0;
	bstreeToArray(array, T.root, index);
}

// ------------------------------------ bstreeToArray ------------------------
// Description: Builds a sorted array of NodeData* pointers from a BST 	
// Precondition: NONE
// Features: Traverses the BST tree using an in-order traversal 
//			 adding the NodeData* to each index of the array
// ----------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[], Node* parent, int& index)
{
	if (parent != NULL)
	{
		// go left
		bstreeToArray(array, parent->left, index);
		// insert
		array[index++] = new NodeData(*parent->data);
		// go right
		bstreeToArray(array, parent->right, index);
	}	
}

// ------------------------------------ arrayToBSTree ------------------------
// Description: Builds a balanced BST from 
//				a sorted array of NodeData* pointers
// Precondition: arrayToBSTree(...) helper function
//				 and sizeOf(..) already created
// Features: Refer to the private helper function
// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[])
{
	//call to size of array
	int size = sizeOf(array);
	arrayToBSTree(array, 0, size - 1);

}

// ------------------------------------ arrayToBSTree ------------------------
// Description: Private helper method that creates a BST from an array
// Precondition: insert(...) function already created 
// Features: recursively calls the function inserting the middle element
//			 of the sorted integer array which creates a ballanced BST
//			 this algorithm is essentialy the binary search algorithm 
// ----------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[], int start, int end)
{
	if (start > end)
	{
		return;
	}
		int mid = start + (end - start) / 2;
		NodeData* temp = new NodeData(*array[mid]);
		insert(temp);
		delete array[mid];

		// call to private helper function
		arrayToBSTree(array, start, mid - 1);
		arrayToBSTree(array, mid + 1, end);
	
}

// ------------------------------------ sizeOf ------------------------
// Description: Private function calculates the length of an array
// Precondition: NONE
// Features: loops through the array while not NULL and increments 
// ---------------------------------------------------------------------
int BinTree::sizeOf(NodeData* array[]) const
{
	int size = 0;
	// while not NULL proceed
	while (array[size] != NULL)
	{
		//increment size
		size++;
	}
	return size;
}


// ------------------------------------ NumofNodes ----------------------------
// Description: Private helper functions that returns
//				the number of nodes in a BST
// Precondition: NONE
// Features: Traverses the BST adding each node 
// ----------------------------------------------------------------------------
int  BinTree::numofNodes(Node* parent) const
{
	if (parent == NULL)
	{
		return 0;
	}
	int retVal; 
	// recursively goes left & right 
	retVal = numofNodes(parent->left) + 
				numofNodes(parent->right) + 1;
	return retVal;
}

// ------------------------------------ operator<< ----------------------------
// Description: operator<< overloaded to display the BST in accending order
// Precondition: inOrderHelper(...) method be created
// Features: calls inOrderHelper(...) function passing in the ostream 
//			and reference to the root of the right hand side
// ----------------------------------------------------------------------------
ostream& operator<<(ostream& ostream, const BinTree& rhs)
{
	BinTree::Node* current = rhs.root;
	rhs.inOrderHelper(ostream, current);
	ostream << "\n";
	return ostream;
}

// ------------------------------------ Display -------------------------------
// Description: Private helper method that displays the BST in order
// Precondition: NONE
// Features: traverses the BST doing in an in-order traversal algorithm 
// ----------------------------------------------------------------------------
void BinTree::inOrderHelper(ostream& ostream, Node* parent) const
{
	if (parent != NULL)
	{
		inOrderHelper(ostream, parent->left);
		ostream << *parent->data << " ";
		inOrderHelper(ostream, parent->right);
	}
}


// ------------------------------------ operator== ----------------------------
// Description: Compares if two BST's are equal to each other
// Precondition: isEqual(...) method must be created
// Features: - returns false if both trees are empty
//			 - calls isEqual(...) passing in the root of the 
//				left hand side and right hand side 
// ----------------------------------------------------------------------------
bool BinTree::operator==(const BinTree& rhs) const
{
	if (root == NULL && rhs.root == NULL)
	{
		return false;
	}
	else
	{
		// call to helper function
		return isEqual(root, rhs.root);
	}
}

// ------------------------------------ operator!= ----------------------------
// Description: Compares if two BST's are not equal to each other
// Precondition: operator= overloaded
// Features: negates the operator=. Refer to operator=
// ----------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree& rhs) const
{
	return !(*this == rhs);
}

// ------------------------------------ isEqual ----------------------------
// Description: Compares two BST and returns if they are equal or not
// Precondition: NONE
// Features: recursively traverses both trees comparing data 
// ----------------------------------------------------------------------------
bool BinTree::isEqual(Node* lhs, Node* rhs) const
{
	if (lhs != NULL && rhs != NULL)
	{
			// compares data in both trees
		return *lhs->data == *rhs->data 
			&& isEqual(lhs->left, rhs->left) 
			&& isEqual(lhs->right, rhs->right);

	}		
}

// ------------------------------------ operator= -----------------------------
// Description: Assigns a tree 
// Precondition: Copy(Node* parent) and makeEmpty(); must be created
// Features: - empties and deletes the left tree
//			 - calls the copy method passing in reference to the rhs root
// ----------------------------------------------------------------------------
const BinTree& BinTree::operator=(const BinTree& rhs)
{
	// return if self assignment 
	if (this == &rhs)
	{
		return *this;
	}

	// clear original list
	makeEmpty(); 

	root = NULL;
	// call to helper funtion 
	copy(rhs.root); 
	return *this;
}

// ------------------------------------ copy ----------------------------------
// Description: Private helper method for the operator=
// Precondition: 
// Features: recursively calls the function and 
//			 executes a post-order algorithm 
// ----------------------------------------------------------------------------
void BinTree::copy(Node* parent)
{
	if (parent != NULL)
	{
		// creates a new NodeData* with prev. data
		NodeData* temp = new NodeData(*parent->data);
		// calls insert function
		insert(temp);
		// go left
		copy(parent->left);
		// go right
		copy(parent->right);
	}
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		// display information of object
		cout << *current->data << endl;        
		sideways(current->left, level);
	}
}