/*
	FILE: DoublyLinkedList.h
	AUTHOR: Ozzie Mercado
	CREATED: January 23, 2021
	MODIFIED: January 29, 2021
	DESCRIPTION: A templated Doubly-Linked List data structure. The benefits of this Linked List are:
		- AddHead(): On average O(1), worst case O(1).
		- AddTail(): On average O(1), worst case O(1).
		- Insert(): On average O(1), worst case O(1).
		- Remove(): On average O(1), worst case O(1).
		- RemoveHead(): On average O(1), worst case O(1).
		- RemoveTail(): On average O(1), worst case O(1).
		- Find(): On average O(N/2), worst case O(N).
		- PeekHead(): On average O(1), worst case O(1).
		- PeekTail(): On average O(1), worst case O(1).
*/

#pragma once

/*
	DESCRIPTION: A Linked List of nodes that supports forward and backward traversal.
*/
template<typename Type> 
class DoublyLinkedList
{
public:
	/*
		DESCRIPTION: A linked list node to house data.
	*/
	class Node
	{
		friend typename DoublyLinkedList<Type>;

	private:
		// DATA MEMBERS

		Type m_data;
		Node* m_prev;
		Node* m_next;

	public:
		// FUNCTIONS

		Node(Type _data, Node* _prev, Node* _next) :
			m_data(_data),
			m_prev(_prev),
			m_next(_next)
		{
		}

		Node(const Node& _node) = delete;
		Node& operator=(const Node& _list) = delete;

		inline Type& Data()
		{
			return m_data;
		}

		inline Node* Prev()
		{
			return m_prev;
		}

		inline Node* Next()
		{
			return m_next;
		}
	};

private:
	// DATA MEMBERS

	Node* m_head; // The head of the list.
	Node* m_tail; // The tail of the list.
	unsigned int m_size; // The number of items in the list.

public:
	// FUNCTIONS

	/*
		DESCRIPTION: Constructs an empty list.
	*/
	DoublyLinkedList();

	/*
		DESCRIPTION: Deep copies the provided list.
		PARAMETERS:
			const DoublyLinkedList<Type>& _list, the list to copy.
	*/
	DoublyLinkedList(const DoublyLinkedList<Type>& _list);

	/*
		DESCRIPTION: Deallocates the list.
	*/
	virtual ~DoublyLinkedList();

	/*
		DESCRIPTION: Deep copies the provided list.
		PARAMETERS:
			const DoublyLinkedList<Type>& _list, the list to copy.
	*/
	DoublyLinkedList<Type>& operator=(const DoublyLinkedList<Type>& _list);

	/*
		DESCRIPTION: Adds an item to the head of the list.
		PARAMETERS:
			const Type& _data, the item to add.
	*/
	void AddHead(const Type& _data);

	/*
		DESCRIPTION: Adds an item to the tail of the list.
		PARAMETERS:
			const Type& _data, the item to add.
	*/
	void AddTail(const Type& _data);

	/*
		DESCRIPTION: Inserts an item into the list where the given node is.
		PARAMETERS:
			Node* _node, the node where the item is to be inserted.
			const Type& _data, the item to insert.
	*/
	void Insert(Node* _node, const Type& _data);

	/*
		DESCRIPTION: Removes an item from the list at the given node.
		PARAMETERS:
			Node* _node, the node to remove.
		RETURNS: (bool) true, if the item was removed. Otherwise, false.
	*/
	bool Remove(Node* _node);

	/*
		DESCRIPTION: Removes the item at the head of the list.
		RETURNS: (bool) true, if the item was removed. Otherwise, false.
	*/
	bool RemoveHead();

	/*
		DESCRIPTION: Removes the item at the tail of the list.
		RETURNS: (bool) true, if the item was removed. Otherwise, false.
	*/
	bool RemoveTail();

	/*
		DESCRIPTION: Returns if an item is in the list.
		PARAMETERS:
			const Type& _data, the item to find.
		RETURNS: (bool) true, if the item is in the list. Otherwise, false.
	*/
	bool Find(const Type& _data);

	/*
		DESCRIPTION: Clears all items from the list and cleans up dynamic memory.
	*/
	void Clear();

	/*
		DESCRIPTION: Returns the number of items in the list.
		RETURNS: (unsigned int), count of items in the list.
	*/
	inline unsigned int Size() const;

	/*
		DESCRIPTION: Returns the head node of the list.
		RETURNS: (Node*) The node at the head.
	*/
	inline Node* PeekHead();

	/*
		DESCRIPTION: Returns the tail node of the list.
		RETURNS: (Node*) The node at the tail.
	*/
	inline Node* PeekTail();
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename Type>
DoublyLinkedList<Type>::DoublyLinkedList(const DoublyLinkedList<Type>& _list)
{
	Node* iter = _list.m_head;

	if (iter)
	{
		do
		{
			AddTail(iter->m_data);
		} while (iter = iter->m_next);
	}
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Clear();
}

template<typename Type>
DoublyLinkedList<Type>& DoublyLinkedList<Type>::operator=(const DoublyLinkedList<Type>& _list)
{
	// We don't need to do anything if we are assigning to ourself.
	if (this == &_list)
		return *this;

	Clear();

	// Copy each node.
	Node* iter = _list.m_head;

	if (iter)
	{
		do
		{
			AddTail(iter->m_data);
		} while (iter = iter->m_next);
	}

	return *this;
}

template<typename Type>
void DoublyLinkedList<Type>::AddHead(const Type& _data)
{
	if (m_head)
	{
		m_head->m_prev = new Node(_data, nullptr, m_head);
		m_head = m_head->m_prev;
	}
	else
		m_head = m_tail = new Node(_data, nullptr, nullptr);

	++m_size;
}

template<typename Type>
void DoublyLinkedList<Type>::AddTail(const Type& _data)
{
	if (m_tail)
	{
		m_tail->m_next = new Node(_data, m_tail, nullptr);
		m_tail = m_tail->m_next;
	}
	else
		m_head = m_tail = new Node(_data, nullptr, nullptr);

	++m_size;
}

template<typename Type>
void DoublyLinkedList<Type>::Insert(Node* _node, const Type& _data)
{
	if (!_node)
		AddHead(_data);
	else
	{
		Node* prevNode = _node->m_prev;

		if (prevNode)
		{
			prevNode->m_next = new Node(_data, prevNode, _node);
			_node->m_prev = prevNode->m_next;
		}
		else
			m_head = _node->m_prev = new Node(_data, nullptr, _node);

		++m_size;
	}
}

template<typename Type>
bool DoublyLinkedList<Type>::Remove(Node* _node)
{
	if (!_node)
		return false;

	if (_node == m_head)
		return RemoveHead();
	else if (_node == m_tail)
		return RemoveTail();
	else
	{
		Node* prevNode = _node->m_prev;
		Node* nextNode = _node->m_next;

		prevNode->m_next = nextNode;

		if (nextNode)
			nextNode->m_prev = prevNode;
		else if (_node == m_tail)
			m_tail = prevNode;

		delete _node;
		--m_size;
	}

	return true;
}

template<typename Type>
bool DoublyLinkedList<Type>::RemoveHead()
{
	if (!m_head)
		return false;

	Node* delNode = m_head;
	m_head = m_head->m_next;

	if (m_head)
		m_head->m_prev = nullptr;
	else
		m_tail = nullptr;

	delete delNode;
	--m_size;

	return true;
}

template<typename Type>
bool DoublyLinkedList<Type>::RemoveTail()
{
	if (!m_tail)
		return false;

	Node* delNode = m_tail;
	m_tail = m_tail->m_prev;

	if (m_tail)
		m_tail->m_next = nullptr;
	else
		m_head = nullptr;

	delete delNode;
	--m_size;

	return true;
}

template<typename Type>
bool DoublyLinkedList<Type>::Find(const Type& _data)
{
	for (Node* iter = m_head; iter; iter = iter->m_next)
		if (iter->m_data == _data)
			return true;

	return false;
}

template<typename Type>
void DoublyLinkedList<Type>::Clear()
{
	Node* iter;

	while (m_head)
	{
		iter = m_head;
		m_head = m_head->m_next;
		delete iter;
	}

	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename Type>
inline unsigned int DoublyLinkedList<Type>::Size() const
{
	return m_size;
}

template<typename Type>
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::PeekHead()
{
	return m_head;
}

template<typename Type>
typename DoublyLinkedList<Type>::Node* DoublyLinkedList<Type>::PeekTail()
{
	return m_tail;
}
