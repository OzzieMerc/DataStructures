/*
	FILE: SinglyLinkedList.h
	AUTHOR: Ozzie Mercado
	CREATED: January 23, 2021
	MODIFIED: January 29, 2021
	DESCRIPTION: A templated Singly-Linked List data structure. The benefits of this Linked List are:
		- AddHead(): On average O(1), worst case O(1).
		- AddTail(): On average O(1), worst case O(1).
		- Insert(): On average O(N/2), worst case O(N).
		- Remove(): On average O(N/2), worst case O(N).
		- RemoveHead(): On average O(1), worst case O(1).
		- RemoveTail(): On average O(N), worst case O(N).
		- Find(): On average O(N/2), worst case O(N).
		- PeekHead(): On average O(1), worst case O(1).
		- PeekTail(): On average O(1), worst case O(1).
*/

#pragma once

/*
	DESCRIPTION: A Linked List of nodes that supports forward traversal only.
*/
template<typename Type> 
class SinglyLinkedList
{
public:
	/*
		DESCRIPTION: A linked list node to house data.
	*/
	class Node
	{
		friend typename SinglyLinkedList<Type>;

	private:
		// DATA MEMBERS

		Type m_data;
		Node* m_next;

	public:
		// FUNCTIONS

		Node(Type _data, Node* _next) :
			m_data(_data),
			m_next(_next)
		{
		}

		Node(const Node& _node) = delete;
		Node& operator=(const Node& _list) = delete;

		inline Type& Data()
		{
			return m_data;
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
	SinglyLinkedList();

	/*
		DESCRIPTION: Deep copies the provided list.
		PARAMETERS:
			const SinglyLinkedList<Type>& _list, the list to copy.
	*/
	SinglyLinkedList(const SinglyLinkedList<Type>& _list);

	/*
		DESCRIPTION: Deallocates the list.
	*/
	virtual ~SinglyLinkedList();

	/*
		DESCRIPTION: Deep copies the provided list.
		PARAMETERS:
			const SinglyLinkedList<Type>& _list, the list to copy.
	*/
	SinglyLinkedList<Type>& operator=(const SinglyLinkedList<Type>& _list);

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
SinglyLinkedList<T>::SinglyLinkedList()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename Type>
SinglyLinkedList<Type>::SinglyLinkedList(const SinglyLinkedList<Type>& _list)
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
SinglyLinkedList<T>::~SinglyLinkedList()
{
	Clear();
}

template<typename Type>
SinglyLinkedList<Type>& SinglyLinkedList<Type>::operator=(const SinglyLinkedList<Type>& _list)
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
void SinglyLinkedList<Type>::AddHead(const Type& _data)
{
	if (m_head)
		m_head = new Node(_data, m_head);
	else
		m_head = m_tail = new Node(_data, nullptr);

	++m_size;
}

template<typename Type>
void SinglyLinkedList<Type>::AddTail(const Type& _data)
{
	if (m_tail)
	{
		m_tail->m_next = new Node(_data, nullptr);
		m_tail = m_tail->m_next;
	}
	else
		m_head = m_tail = new Node(_data, nullptr);

	++m_size;
}

template<typename Type>
void SinglyLinkedList<Type>::Insert(Node* _node, const Type& _data)
{
	if (_node == m_head)
		AddHead(_data);
	else
	{
		Node* iter;
		for (iter = m_head; iter->m_next != _node; iter = iter->m_next) {}

		iter->m_next = new Node(_data, iter->m_next);
		++m_size;
	}
}

template<typename Type>
bool SinglyLinkedList<Type>::Remove(Node* _node)
{
	if (!_node)
		return false;

	if (_node == m_head)
		return RemoveHead();
	else if (_node == m_tail)
		return RemoveTail();
	else
	{
		Node* iter;
		for (iter = m_head; iter->m_next != _node; iter = iter->m_next) {}

		iter->m_next = _node->m_next;

		delete _node;
		--m_size;
	}

	return true;
}

template<typename Type>
bool SinglyLinkedList<Type>::RemoveHead()
{
	if (!m_head)
		return false;

	Node* delNode = m_head;
	m_head = m_head->m_next;

	if (!m_head)
		m_tail = nullptr;

	delete delNode;
	--m_size;

	return true;
}

template<typename Type>
bool SinglyLinkedList<Type>::RemoveTail()
{
	if (!m_tail)
		return false;
	
	Node* delNode = m_tail;

	if (m_head == m_tail)
		m_head = m_tail = nullptr;
	else
	{
		Node* iter;
		for (iter = m_head; iter->m_next != m_tail; iter = iter->m_next) {}

		m_tail = iter;
		m_tail->m_next = nullptr;
	}

	delete delNode;
	--m_size;

	return true;
}

template<typename Type>
bool SinglyLinkedList<Type>::Find(const Type& _data)
{
	for (Node* iter = m_head; iter; iter = iter->m_next)
		if (iter->m_data == _data)
			return true;

	return false;
}

template<typename Type>
void SinglyLinkedList<Type>::Clear()
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
inline unsigned int SinglyLinkedList<Type>::Size() const
{
	return m_size;
}

template<typename Type>
typename SinglyLinkedList<Type>::Node* SinglyLinkedList<Type>::PeekHead()
{
	return m_head;
}

template<typename Type>
typename SinglyLinkedList<Type>::Node* SinglyLinkedList<Type>::PeekTail()
{
	return m_tail;
}
