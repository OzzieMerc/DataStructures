/*
	FILE: DynamicArray.h
	AUTHOR: Ozzie Mercado
	CREATED: January 16, 2021
	MODIFIED: January 27, 2021
	DESCRIPTION: A dynamically allocating data structure with contiguous storage. The benefits are:
		- Append(): On average O(1), worst case O(N).
		- Insert(): On average O(N/2), worst case O(N).
		- Remove(): On average O(N/2), worst case O(N).
		- Find(): On average O(N/2), worst case O(N).
*/

#pragma once

#include <assert.h>

/*
	DESCRIPTION: A dynamically expanding array of contiguous storage.
*/
template<typename Type>
class DynamicArray
{
private:
	// DATA MEMBERS

	Type* m_data; // A pointer to the array
	unsigned int m_size; // Number of items in the container
	unsigned int m_capacity; // Number of spaces for items in the container

public:
	// FUNCTIONS

	DynamicArray();
	DynamicArray(const DynamicArray<Type>& _array);
	~DynamicArray();
	DynamicArray<Type>& operator=(const DynamicArray<Type>& _array);
	inline Type& operator[](unsigned int _index);
	inline const Type& operator[](unsigned int _index) const;
	void Append(const Type& _data);
	void Insert(unsigned int _index, const Type& _data);
	void Remove(unsigned int _index);
	bool Find(const Type& _data);
	void Clear();
	inline unsigned int Size() const;
	inline unsigned int Capacity() const;
	void Reserve(unsigned int _newCapacity);
	inline void ShrinkToFit();
};

template<typename Type>
DynamicArray<Type>::DynamicArray() :
	m_data(nullptr),
	m_size(0),
	m_capacity(0)
{
}

template<typename Type>
DynamicArray<Type>::DynamicArray(const DynamicArray<Type>& _array) :
	m_data(new Type[_array.m_capacity]),
	m_size(_array.m_size),
	m_capacity(_array.m_capacity)
{
	memcpy_s(m_data, m_size, _array.m_data, m_size);
}

template<typename Type>
DynamicArray<Type>::~DynamicArray()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = m_capacity = 0;
}

template<typename Type>
DynamicArray<Type>& DynamicArray<Type>::operator=(const DynamicArray<Type>& _array)
{
	// Ensure we're not assigning to ourself.
	if (this != &_array)
		return *this;

	delete[] m_data;

	m_size = _array.m_size;
	m_capacity = _array.m_capacity;

	m_data = new Type[m_capacity];
	memcpy_s(m_data, m_size, _array.m_data, m_size);

	return *this;
}

template<typename Type>
Type& DynamicArray<Type>::operator[](unsigned int _index)
{
	return m_data[_index];
}

template<typename Type>
const Type& DynamicArray<Type>::operator[](unsigned int _index) const
{
	return m_data[_index];
}

template<typename Type>
void DynamicArray<Type>::Append(const Type& _data)
{
	if (m_size == m_capacity)
	{
		if (m_capacity > 0)
			Reserve(m_capacity << 1); // Double the array capacity.
		else
			Reserve(1);
	}

	m_data[m_size++] = _data;
}

template<typename Type>
void DynamicArray<Type>::Insert(unsigned int _index, const Type& _data)
{
	assert(_index <= m_size);

	if (m_size == m_capacity)
	{
		if (m_capacity > 0)
			Reserve(m_capacity << 1); // Double the array capacity.
		else
			Reserve(1);
	}

	if (_index < m_size)
	{
		// Move the array items to the right to make space for the new item.
		for (unsigned int i = m_size - 1; i >= _index; --i)
		{
			m_data[i + 1] = m_data[i];

			if (i == 0)
				break;
		}
	}

	m_data[_index] = _data;
	++m_size;
}

template<typename Type>
void DynamicArray<Type>::Remove(unsigned int _index)
{
	assert(_index < m_size);

	for (unsigned int i = _index; i < m_size; ++i)
		m_data[i] = m_data[i + 1];

	--m_size;
}

template<typename Type>
bool DynamicArray<Type>::Find(const Type& _data)
{
	for (unsigned int i = 0; i < m_size; ++i)
		if (m_data[i] == _data)
			return true;

	return false;
}

template<typename Type>
void DynamicArray<Type>::Clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = m_capacity = 0;
}

template<typename Type>
unsigned int DynamicArray<Type>::Size() const
{
	return m_size;
}

template<typename Type>
unsigned int DynamicArray<Type>::Capacity() const
{
	return m_capacity;
}

template<typename Type>
void DynamicArray<Type>::Reserve(unsigned int _newCapacity)
{
	if (_newCapacity == m_capacity)
		return;

	if (_newCapacity < m_capacity && m_size > _newCapacity)
		m_size = _newCapacity;

	m_capacity = _newCapacity;
	
	if (m_capacity == 0)
	{
		delete[] m_data;
		m_data = nullptr;
		return;
	}

	Type* temp = new Type[_newCapacity];

	for (unsigned int i = 0; i < m_size; ++i)
		temp[i] = m_data[i];

	delete[] m_data;
	m_data = temp;
}

template<typename Type>
void DynamicArray<Type>::ShrinkToFit()
{
	Reserve(m_size);
}
