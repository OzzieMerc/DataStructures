/*
	FILE: Stack.h
	AUTHOR: Ozzie Mercado
	CREATED: January 31, 2021
	MODIFIED: January 31, 2021
	DESCRIPTION: A templated Stack data structure. The benefits of this Stack are:
		- Push(): On average O(1), worst case O(1).
		- Pop(): On average O(1), worst case O(1).
		- Find(): On average O(N/2), worst case O(N).
		- Peek(): On average O(1), worst case O(1).
*/

#pragma once

/*
	DESCRIPTION: A Stack of nodes that supports forward traversal only.
*/
template<typename Type>
class Stack
{
public:
	/*
		DESCRIPTION: A stack node to house data.
	*/
	class Node
	{
		friend typename Stack<Type>;

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
		Node& operator=(const Node& _stack) = delete;

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

	Node* m_head; // The head of the stack.
	unsigned int m_size; // The number of items in the stack.

public:
	// FUNCTIONS

	/*
		DESCRIPTION: Constructs an empty stack.
	*/
	Stack();

	/*
		DESCRIPTION: Deep copies the provided stack.
		PARAMETERS:
			const Stack<Type>& _stack, the stack to copy.
	*/
	Stack(const Stack<Type>& _stack);

	/*
		DESCRIPTION: Deallocates the stack.
	*/
	virtual ~Stack();

	/*
		DESCRIPTION: Deep copies the provided stack.
		PARAMETERS:
			const Stack<Type>& _stack, the stack to copy.
	*/
	Stack<Type>& operator=(const Stack<Type>& _stack);

	/*
		DESCRIPTION: Adds an item to the head of the stack.
		PARAMETERS:
			const Type& _data, the item to add.
	*/
	void Push(const Type& _data);

	/*
		DESCRIPTION: Removes the item at the head of the stack.
		RETURNS: (bool) true, if the item was removed. Otherwise, false.
	*/
	bool Pop();

	/*
		DESCRIPTION: Returns if an item is in the stack.
		PARAMETERS:
			const Type& _data, the item to find.
		RETURNS: (bool) true, if the item is in the stack. Otherwise, false.
	*/
	bool Find(const Type& _data);

	/*
		DESCRIPTION: Clears all items from the stack and cleans up dynamic memory.
	*/
	void Clear();

	/*
		DESCRIPTION: Returns the number of items in the stack.
		RETURNS: (unsigned int), count of items in the stack.
	*/
	inline unsigned int Size() const;

	/*
		DESCRIPTION: Returns the head node of the stack.
		RETURNS: (Node*) The node at the head.
	*/
	inline Node* Peek();
};

template<typename T>
Stack<T>::Stack()
{
	m_head = nullptr;
	m_size = 0;
}

template<typename Type>
Stack<Type>::Stack(const Stack<Type>& _stack)
{
	Node* iter = _stack.m_head;

	if (iter)
	{
		Node* tail = m_head = new Node(iter->m_data, nullptr);

		while (iter = iter->m_next)
		{
			tail->m_next = new Node(iter->m_data, nullptr);
			tail = tail->m_next;
		}
		
		m_size = _stack.m_size;
	}
}

template<typename T>
Stack<T>::~Stack()
{
	Clear();
}

template<typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack<Type>& _stack)
{
	// We don't need to do anything if we are assigning to ourself.
	if (this == &_stack)
		return *this;

	Clear();

	// Copy each node.
	Node* iter = _stack.m_head;

	if (iter)
	{
		Node* tail = m_head = new Node(iter->m_data, nullptr);

		while (iter = iter->m_next)
		{
			tail->m_next = new Node(iter->m_data, nullptr);
			tail = tail->m_next;
		}

		m_size = _stack.m_size;
	}

	return *this;
}

template<typename Type>
void Stack<Type>::Push(const Type& _data)
{
	m_head = new Node(_data, m_head);
	++m_size;
}

template<typename Type>
bool Stack<Type>::Pop()
{
	if (!m_head)
		return false;

	Node* delNode = m_head;
	m_head = m_head->m_next;

	delete delNode;
	--m_size;

	return true;
}

template<typename Type>
bool Stack<Type>::Find(const Type& _data)
{
	for (Node* iter = m_head; iter; iter = iter->m_next)
		if (iter->m_data == _data)
			return true;

	return false;
}

template<typename Type>
void Stack<Type>::Clear()
{
	Node* iter;

	while (m_head)
	{
		iter = m_head;
		m_head = m_head->m_next;
		delete iter;
	}

	m_head = nullptr;
	m_size = 0;
}

template<typename Type>
inline unsigned int Stack<Type>::Size() const
{
	return m_size;
}

template<typename Type>
typename Stack<Type>::Node* Stack<Type>::Peek()
{
	return m_head;
}
