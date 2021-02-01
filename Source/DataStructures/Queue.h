/*
	FILE: Queue.h
	AUTHOR: Ozzie Mercado
	CREATED: February 1, 2021
	MODIFIED: February 1, 2021
	DESCRIPTION: A templated Queue data structure. The benefits of this Queue are:
		- Enqueue(): On average O(1), worst case O(1).
		- Dequeue(): On average O(1), worst case O(1).
		- Find(): On average O(N/2), worst case O(N).
		- Peek(): On average O(1), worst case O(1).
*/

#pragma once

/*
	DESCRIPTION: A Queue of nodes that supports forward traversal only.
*/
template<typename Type>
class Queue
{
public:
	/*
		DESCRIPTION: A queue node to house data.
	*/
	class Node
	{
		friend typename Queue<Type>;

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
		Node& operator=(const Node& _queue) = delete;

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

	Node* m_head; // The head of the queue.
	Node* m_tail; // The tail of the queue.
	unsigned int m_size; // The number of items in the queue.

public:
	// FUNCTIONS

	/*
		DESCRIPTION: Constructs an empty queue.
	*/
	Queue();

	/*
		DESCRIPTION: Deep copies the provided queue.
		PARAMETERS:
			const Queue<Type>& _queue, the queue to copy.
	*/
	Queue(const Queue<Type>& _queue);

	/*
		DESCRIPTION: Deallocates the queue.
	*/
	virtual ~Queue();

	/*
		DESCRIPTION: Deep copies the provided queue.
		PARAMETERS:
			const Queue<Type>& _queue, the queue to copy.
	*/
	Queue<Type>& operator=(const Queue<Type>& _queue);

	/*
		DESCRIPTION: Adds an item to the tail of the queue.
		PARAMETERS:
			const Type& _data, the item to add.
	*/
	void Enqueue(const Type& _data);

	/*
		DESCRIPTION: Removes the item at the head of the queue.
		RETURNS: (bool) true, if the item was removed. Otherwise, false.
	*/
	bool Dequeue();

	/*
		DESCRIPTION: Returns if an item is in the queue.
		PARAMETERS:
			const Type& _data, the item to find.
		RETURNS: (bool) true, if the item is in the queue. Otherwise, false.
	*/
	bool Find(const Type& _data);

	/*
		DESCRIPTION: Clears all items from the queue and cleans up dynamic memory.
	*/
	void Clear();

	/*
		DESCRIPTION: Returns the number of items in the queue.
		RETURNS: (unsigned int), count of items in the queue.
	*/
	inline unsigned int Size() const;

	/*
		DESCRIPTION: Returns the head node of the queue.
		RETURNS: (Node*) The node at the head.
	*/
	inline Node* Peek();
};

template<typename T>
Queue<T>::Queue()
{
	m_head = m_tail = nullptr;
	m_size = 0;
}

template<typename Type>
Queue<Type>::Queue(const Queue<Type>& _queue)
{
	Node* iter = _queue.m_head;

	if (iter)
	{
		m_head = m_tail = new Node(iter->m_data, nullptr);

		while (iter = iter->m_next)
		{
			m_tail->m_next = new Node(iter->m_data, nullptr);
			m_tail = m_tail->m_next;
		}

		m_size = _queue.m_size;
	}
}

template<typename T>
Queue<T>::~Queue()
{
	Clear();
}

template<typename Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& _queue)
{
	// We don't need to do anything if we are assigning to ourself.
	if (this == &_queue)
		return *this;

	Clear();

	// Copy each node.
	Node* iter = _queue.m_head;

	if (iter)
	{
		m_head = m_tail = new Node(iter->m_data, nullptr);

		while (iter = iter->m_next)
		{
			m_tail->m_next = new Node(iter->m_data, nullptr);
			m_tail = m_tail->m_next;
		}

		m_size = _queue.m_size;
	}

	return *this;
}

template<typename Type>
void Queue<Type>::Enqueue(const Type& _data)
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
bool Queue<Type>::Dequeue()
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
bool Queue<Type>::Find(const Type& _data)
{
	for (Node* iter = m_head; iter; iter = iter->m_next)
		if (iter->m_data == _data)
			return true;

	return false;
}

template<typename Type>
void Queue<Type>::Clear()
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
inline unsigned int Queue<Type>::Size() const
{
	return m_size;
}

template<typename Type>
typename Queue<Type>::Node* Queue<Type>::Peek()
{
	return m_head;
}
