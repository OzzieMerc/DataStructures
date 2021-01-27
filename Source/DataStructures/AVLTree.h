/*
	FILE: AVLTree.h
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: January 26, 2021
	DESCRIPTION: A templated AVL Tree data structure. The benefits of the AVL are:
		- Insert(): On average O(log N), worst case O(log N).
		- Remove(): On average O(log N), worst case O(log N).
		- Find(): On average O(log N), worst case O(log N).
*/

#pragma once

#include <assert.h>
#include <functional> // Used for comparison functions during Insert, Remove, and find.
/*
	INSIGHT: Originally, I chose functors for the comparison function, because of the overhead that comes
		with using std::function. Ultimately, I went with std::function, because writing a lambda is more
		readable and faster to code. This makes the Binary Search Tree more convenient to use in a program.
*/

/*
	DESCRIPTION: A node-based tree that keeps data in sorted order and the tree balanced.
*/
template<typename Type>
class AVLTree
{
private:
	/*
		DESCRIPTION: A tree node containing data and pointers to lesser and greater values.
	*/
	struct Node
	{
		Type data;
		Node* left; // Pointer to a node with data of lesser value.
		Node* right; // Pointer to a node with data of greater value.
	};

	// DATA MEMBERS

	Node* m_root; // The head of the tree.
	std::function<bool(const Type&, const Type&)> m_isLesser; // Function for determining lesser values.
	std::function<bool(const Type&, const Type&)> m_IsGreater; // Function for determining greater values.

	// FUNCTIONS

	/*
		DESCRIPTION: Helper function for Insert(const Type& _data). Inserts an item into the node or its children.
		PARAMETERS:
			const Type& _data, the item to Insert into the tree.
			Node* _node, the node to compare data to for insertion.
			Node* _parentNode, the parent of _node.
	*/
	void Insert(const Type& _data, Node* _node, Node* _parentNode);

	/*
		DESCRIPTION: Helper function for Remove(const Type& _data). Removes an item from the node or its children.
		PARAMETERS:
			const Type& _data, the item to Remove from the tree.
			Node* _node, the node to compare data to for removal.
			Node* _parentNode, the parent of _node.
		RETURNS: (bool) true, if the item was removed.
	*/
	bool Remove(const Type& _data, Node* _node, Node* _parentNode);

	/*
		DESCRIPTION: Helper function for Find(const Type& _data). Searches for an item in the node and its children.
		PARAMETERS:
			const Type& _data, the item to Find in the tree.
			Node* _node, the node to compare data to.
		RETURNS: (bool) true, if the item was found.
	*/
	bool Find(const Type& _data, Node* _node) const;

	/*
		DESCRIPTION: Helper function for Clear(). Clears items in a node, its children, and cleans up dynamic memory.
		PARAMETERS:
			Node* _node, the node to Clear.
	*/
	void Clear(Node* _node);

	/*
		DESCRIPTION: Helper function for Size(). Provides the number of items from a given node.
		PARAMETERS:
			Node* _node, the node to retrieve its Size from.
		RETURNS: (unsigned int), count of items starting at the node.
	*/
	unsigned int Size(Node* _node) const;

	/*
		DESCRIPTION: Determines the height of the node.
		PARAMETERS :
			Node * _node - The node to get the height of.
			unsigned int _height - 0 if called outside of this functions implementation.
		RETURNS : int - The height of the node.
	*/
	unsigned int Height(const Node* _node, unsigned int _height) const;

	/*
		DESCRIPTION: Helper functions for public interface "ToArray" functions. Copies the items in the node and its 
			children to a given array using a traversal described by the function.
		PARAMETERS:
			Type& _outArray, a preallocated array to copy the tree items to.
			int& _outArrayIndex, the index in the _outArray to write the next node value to.
			Node* _node, the Current node we are visiting.
	*/
	void ToArrayInorder(Type* _outArray, int& _outArrayIndex, Node* _node) const;
	void ToArrayPreorder(Type* _outArray, int& _outArrayIndex, Node* _node) const;
	void ToArrayPostorder(Type* _outArray, int& _outArrayIndex, Node* _node) const;
	void ToArrayInReverseOrder(Type* _outArray, int& _outArrayIndex, Node* _node) const;

	/*
		DESCRIPTION: Helper function for Remove(const Type& _data, Node* _node). Provides the lowest value node from 
			a given node, removing it from the tree in the process. The lowest value node is not deleted.
		PARAMETERS:
			Node* _node, the node to start looking for the lowest value to Remove.
		RETURNS: (Node*), the node with the lowest value.
	*/
	Node* RemovePostorderPredecessor(Node* _node);

	/*
		DESCRIPTION: Deep copies the node and its children.
		PARAMETERS:
			Node* _node, the node to copy.
	*/
	void CopyAll(Node* _node);

	/*
		DESCRIPTION: Rotates the child node to the left.
		PARAMETERS :
			Node * _node - A child node to rotate.
			Node * _parentNode - The parent of the child node.
	*/
	void RotateLeft(Node* _node, Node* _parentNode);

	/*
		DESCRIPTION: Rotates the child node to the right.
		PARAMETERS :
			Node * _node - A child node to rotate.
			Node * _parentNode - The parent of the child node.
	*/
	void RotateRight(Node* _node, Node* _parentNode);

	/*
		DESCRIPTION: Rebalances the child node by rotating it if necessary.
		PARAMETERS :
			Node * _node - A child node to balance.
			Node * _parentNode - The parent of the child node.
	*/
	void Rebalance(Node* _node, Node* _parentNode);

public:
	// FUNCTIONS

	/*
		DESCRIPTION: Constructs an empty tree.
		PARAMETERS:
			std::function<bool(const Type&, const Type&)> _isLesser, function for determining lesser values.
			std::function<bool(const Type&, const Type&)> _isGreater, function for determining greater values.
	*/
	AVLTree(std::function<bool(const Type&, const Type&)> _isLesser, std::function<bool(const Type&, const Type&)> _isGreater);

	/*
		DESCRIPTION: Copy constructs a tree by performing a deep copy of the given tree.
		PARAMETERS:
			const AVLTree& _avlTree, a tree.
	*/
	AVLTree(const AVLTree<Type>& _avlTree);

	/*
		DESCRIPTION: Destroys the tree and cleans up any dynamic memory.
	*/
	~AVLTree();

	/*
		DESCRIPTION: Clears the Current tree and deep copies the given tree.
		PARAMETERS:
			const AVLTree& _avlTree, a tree.
	*/
	AVLTree<Type>& operator=(const AVLTree<Type>& _avlTree);

	/*
		DESCRIPTION: Inserts an item into the tree.
		PARAMETERS:
			const Type& _data, the item to Insert into the tree.
	*/
	void Insert(const Type& _data);

	/*
		DESCRIPTION: Removes an item from the tree.
		PARAMETERS:
			const Type& _data, the item to Remove from the tree.
		RETURNS: (bool) true, if the item was removed.
	*/
	bool Remove(const Type& _data);

	/*
		DESCRIPTION: Searches for an item in the tree.
		PARAMETERS:
			const Type& _data, the item to Find in the tree.
		RETURNS: (bool) true, if the item was found.
	*/
	bool Find(const Type& _data) const;

	/*
		DESCRIPTION: Clears all items from the tree and cleans up dynamic memory.
	*/
	void Clear();

	/*
		DESCRIPTION: Provides the number of items in the tree.
		RETURNS: (unsigned int), count of items in the tree.
	*/
	inline unsigned int Size() const;

	/*
		DESCRIPTION: Determines the height of the tree.
		RETURNS : int - The height of the stree.
	*/
	unsigned int Height() const;

	/*
		DESCRIPTION: Copies the items in the tree to a given array using a traversal described by the function.
		PARAMETERS:
			Type& _outArray, a preallocated array to copy the tree items to.
	*/
	void ToArrayInorder(Type* _outArray) const;
	void ToArrayPreorder(Type* _outArray) const;
	void ToArrayPostorder(Type* _outArray) const;
	void ToArrayInReverseOrder(Type* _outArray) const;
};

template<typename Type>
AVLTree<Type>::AVLTree(std::function<bool(const Type&, const Type&)> _isLesser, std::function<bool(const Type&, const Type&)> _isGreater) :
	m_root(nullptr),
	m_isLesser(_isLesser),
	m_IsGreater(_isGreater)
{
}

template<typename Type>
AVLTree<Type>::AVLTree(const AVLTree<Type>& _avlTree)
{
	if (_avlTree.m_root)
		CopyAll(_avlTree.m_root);
}

template<typename Type>
AVLTree<Type>::~AVLTree()
{
	Clear();
}

template<typename Type>
AVLTree<Type>& AVLTree<Type>::operator=(const AVLTree<Type>& _avlTree)
{
	// We don't need to do anything if we are assigning to ourself.
	if (this == &_avlTree)
		return *this;

	Clear();

	if (_avlTree.m_root)
		CopyAll(_avlTree.m_root);

	return *this;
}

template<typename Type>
void AVLTree<Type>::Insert(const Type& _data)
{
	if (!m_root)
		m_root = new Node{ _data, nullptr, nullptr };
	else
		Insert(_data, m_root, nullptr);
}

template<typename Type>
void AVLTree<Type>::Insert(const Type& _data, Node* _node, Node* _parentNode)
{
	if (m_isLesser(_data, _node->data))
	{
		if (!_node->left)
			_node->left = new Node{ _data, nullptr, nullptr }; // If no left node, add one.
		else
			Insert(_data, _node->left, _node); // Otherwise, go left.
	}
	else if (!_node->right)
		_node->right = new Node{ _data, nullptr, nullptr }; // If no right node, add one.
	else
		Insert(_data, _node->right, _node); // Otherwise, go right.

	Rebalance(_node, _parentNode);
}

template<typename Type>
bool AVLTree<Type>::Remove(const Type& _data)
{
	return Remove(_data, m_root, nullptr);
}

template<typename Type>
bool AVLTree<Type>::Remove(const Type& _data, Node* _node, Node* _parentNode)
{
	if (!_node)
		return false;

	if (m_isLesser(_data, _node->data))
	{
		Node* leftNode = _node->left;

		if (leftNode && leftNode->data == _data)
		{
			// Found the node. Now Remove it.

			if (!leftNode->left)
			{
				if (!leftNode->right)
				{
					// The node has no children.

					delete leftNode;
					_node->left = nullptr;
				}
				else
				{
					// Node has child on the right.

					_node->left = leftNode->right;
					delete leftNode;
				}
			}
			else if (!leftNode->right)
			{
				// Node has child on the left.

				_node->left = leftNode->left;
				delete leftNode;
			}
			else
			{
				// Node has two children.

				Node* minNode = RemovePostorderPredecessor(leftNode->right); // Get the minimum value node from the right child...
				leftNode->data = minNode->data; // ... and assign its value to this node.

				// If the right child is the minimum value node, then its right child needs to take its place.
				if (leftNode->right == minNode)
					leftNode->right = minNode->right;

				delete minNode;
			}

			Rebalance(_node, _parentNode);

			return true;
		}

		// The node to Remove may be further left.
		bool result = Remove(_data, leftNode, _node);
		Rebalance(_node, _parentNode);

		return result;
	}
	else if (m_IsGreater(_data, _node->data))
	{
		Node* rightNode = _node->right;

		if (rightNode && rightNode->data == _data)
		{
			// Found the node. Now Remove it.

			if (!rightNode->left)
			{
				if (!rightNode->right)
				{
					// The node has no children.

					delete rightNode;
					_node->right = nullptr;
				}
				else
				{
					// Node has child on the right.

					_node->right = rightNode->right;
					delete rightNode;
				}
			}
			else if (!rightNode->right)
			{
				// Node has child on the left.

				_node->right = rightNode->left;
				delete rightNode;
			}
			else
			{
				// Node has two children.

				Node* minNode = RemovePostorderPredecessor(rightNode->right); // Get the minimum value node from the right child...
				rightNode->data = minNode->data; // ... and assign its value to this node.

				// If the right child is the minimum value node, then its right child needs to take its place.
				if (rightNode->right == minNode)
					rightNode->right = minNode->right;

				delete minNode;
			}

			Rebalance(_node, _parentNode);

			return true;
		}

		// The node to Remove may be further right.
		bool result = Remove(_data, rightNode, _node);
		Rebalance(_node, _parentNode);

		return result;;
	}
	else if (_node->right)
	{
		// The node to Remove is the root. It has a child on the right. It may or may not have a child on the left.

		Node* minNode = RemovePostorderPredecessor(_node->right); // Get the minimum value node from the right child...
		minNode->left = _node->left; // ... and point minNode's left to the left child.

		// If the right child is not the minimum value node, then point minNode's right to the right child.
		if (_node->right != minNode)
			minNode->right = _node->right;

		delete _node;
		m_root = minNode;

		Rebalance(m_root, nullptr);

		return true;
	}

	// The node to Remove is the root. It may or may not have a child on the left.

	m_root = _node->left; // This may or may not be nullptr.
	delete _node;

	if (m_root)
		Rebalance(m_root, nullptr);

	return true;
}

template<typename Type>
bool AVLTree<Type>::Find(const Type& _data) const
{
	return Find(_data, m_root);
}

template<typename Type>
bool AVLTree<Type>::Find(const Type& _data, Node* _node) const
{
	if (!_node)
		return false;

	if (m_isLesser(_data, _node->data))
		return Find(_data, _node->left);
	else if (m_IsGreater(_data, _node->data))
		return Find(_data, _node->right);

	return true;
}

template<typename Type>
void AVLTree<Type>::Clear()
{
	Clear(m_root);
	m_root = nullptr;
}

template<typename Type>
void AVLTree<Type>::Clear(Node* _node)
{
	if (!_node)
		return;

	Clear(_node->left);
	Clear(_node->right);

	delete _node;
	_node = nullptr;
}

template<typename Type>
unsigned int AVLTree<Type>::Size() const
{
	return Size(m_root);
}

template<typename Type>
unsigned int AVLTree<Type>::Size(Node* _node) const
{
	if (!_node)
		return 0;

	return Size(_node->left) + Size(_node->right) + 1;
}

template<typename Type>
unsigned int AVLTree<Type>::Height() const
{
	if (!m_root)
		return 0;

	return Height(m_root, 0);
}

template<typename Type>
unsigned int AVLTree<Type>::Height(const Node* _node, unsigned int _height) const
{
	int leftHeight = (_node->left) ? Height(_node->left, _height + 1) : _height + 1;
	int rightHeight = (_node->right) ? Height(_node->right, _height + 1) : _height + 1;

	return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

template<typename Type>
void AVLTree<Type>::ToArrayInorder(Type* _outArray) const
{
	int arrayIndex = 0;
	ToArrayInorder(_outArray, arrayIndex, m_root);
}

template<typename Type>
void AVLTree<Type>::ToArrayPreorder(Type* _outArray) const
{
	int arrayIndex = 0;
	ToArrayPreorder(_outArray, arrayIndex, m_root);
}

template<typename Type>
void AVLTree<Type>::ToArrayPostorder(Type* _outArray) const
{
	int arrayIndex = 0;
	ToArrayPostorder(_outArray, arrayIndex, m_root);
}

template<typename Type>
void AVLTree<Type>::ToArrayInReverseOrder(Type* _outArray) const
{
	int arrayIndex = 0;
	ToArrayInReverseOrder(_outArray, arrayIndex, m_root);
}

template<typename Type>
void AVLTree<Type>::ToArrayInorder(Type* _outArray, int& _outArrayIndex, Node* _node) const
{
	if (!_node)
		return;

	ToArrayInorder(_outArray, _outArrayIndex, _node->left);
	_outArray[_outArrayIndex++] = _node->data;
	ToArrayInorder(_outArray, _outArrayIndex, _node->right);
}

template<typename Type>
void AVLTree<Type>::ToArrayPreorder(Type* _outArray, int& _outArrayIndex, Node* _node) const
{
	if (!_node)
		return;

	_outArray[_outArrayIndex++] = _node->data;
	ToArrayPreorder(_outArray, _outArrayIndex, _node->left);
	ToArrayPreorder(_outArray, _outArrayIndex, _node->right);
}

template<typename Type>
void AVLTree<Type>::ToArrayPostorder(Type* _outArray, int& _outArrayIndex, Node* _node) const
{
	if (!_node)
		return;

	ToArrayPostorder(_outArray, _outArrayIndex, _node->left);
	ToArrayPostorder(_outArray, _outArrayIndex, _node->right);
	_outArray[_outArrayIndex++] = _node->data;
}

template<typename Type>
void AVLTree<Type>::ToArrayInReverseOrder(Type* _outArray, int& _outArrayIndex, Node* _node) const
{
	if (!_node)
		return;

	ToArrayInReverseOrder(_outArray, _outArrayIndex, _node->right);
	_outArray[_outArrayIndex++] = _node->data;
	ToArrayInReverseOrder(_outArray, _outArrayIndex, _node->left);
}

template<typename Type>
typename AVLTree<Type>::Node* AVLTree<Type>::RemovePostorderPredecessor(Node* _node)
{
	assert(_node);

	Node* nodeLeft = _node->left;

	if (!nodeLeft)
		return _node;

	// Iterate to the leftmost node.
	while (nodeLeft->left)
	{
		_node = nodeLeft;
		nodeLeft = nodeLeft->left;
	}

	// If nodeLeft has a child on the right, reparent the child, so it takes the place of nodeLeft.
	if (nodeLeft->right)
		_node->left = nodeLeft->right;
	else // nodeLeft has no children.
		_node->left = NULL;

	return nodeLeft;
}

template<typename Type>
void AVLTree<Type>::CopyAll(Node* _node)
{
	if (!_node)
		return;

	CopyAll(_node->left);
	CopyAll(_node->right);
	Insert(_node->data);
}

template<typename Type>
void AVLTree<Type>::RotateLeft(Node* _node, Node* _parentNode)
{
	assert(_node);

	/*
	Visual of what is happening.

		a(_node)         c
		 \              / \
		  c     to     a   d
		 / \            \
		b   d            b
	*/

	Node* c = _node->right;

	_node->right = c->left;
	c->left = _node;

	// Connect c to the parent where node was.
	if (!_parentNode)
		m_root = c;
	else if (_parentNode->left == _node)
		_parentNode->left = c;
	else
		_parentNode->right = c;
}

template<typename Type>
void AVLTree<Type>::RotateRight(Node* _node, Node* _parentNode)
{
	assert(_node);

	/*
	Visual of what is happening.

			z(_node)     x
		   /            / \
		  x     to     w   z
		 / \              /
		w   y            y
	*/

	Node* x = _node->left;

	_node->left = x->right;
	x->right = _node;

	// Connect x to the parent where node was.
	if (!_parentNode)
		m_root = x;
	else if (_parentNode->left == _node)
		_parentNode->left = x;
	else
		_parentNode->right = x;
}

template<typename Type>
void AVLTree<Type>::Rebalance(Node* _node, Node* _parentNode)
{
	assert(_node);

	const int leftHeight = (_node->left) ? Height(_node->left, 0) : 0;
	const int rightHeight = (_node->right) ? Height(_node->right, 0) : 0;
	const int balance = leftHeight - rightHeight;

	if (balance < -1) // Is tree is taller on the right?
	{
		assert(_node->right);

		if (_node->right->left) // Right left case.
		{
			RotateRight(_node->right, _node);
			RotateLeft(_node, _parentNode);
		}
		else // Right right case.
			RotateLeft(_node, _parentNode);
	}
	else if (balance > 1) // Is tree is taller on the left?
	{
		assert(_node->left);

		if (_node->left->right) // Left right case.
		{
			RotateLeft(_node->left, _node);
			RotateRight(_node, _parentNode);
		}
		else // Left left case.
			RotateRight(_node, _parentNode);
	}
}