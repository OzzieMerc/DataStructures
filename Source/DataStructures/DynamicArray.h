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

	/*
		DESCRIPTION: Constructs an empty array.
	*/
	DynamicArray();

	/*
		DESCRIPTION: Deep copies the provided array.
		PARAMETERS:
			const DynamicArray<Type>& _array, the array to copy.
	*/
	DynamicArray(const DynamicArray<Type>& _array);

	/*
		DESCRIPTION: Deallocates the array.
	*/
	~DynamicArray();

	/*
		DESCRIPTION: Deep copies the provided array.
		PARAMETERS:
			const DynamicArray<Type>& _array, the array to copy.
	*/
	DynamicArray<Type>& operator=(const DynamicArray<Type>& _array);

	/*
		DESCRIPTION: Returns the item at an index.
		PARAMETERS:
			unsigned int _index, the index of the item.
	*/
	inline Type& operator[](unsigned int _index);

	/*
		DESCRIPTION: Returns the item at an index.
		PARAMETERS:
			unsigned int _index, the index of the item.
	*/
	inline const Type& operator[](unsigned int _index) const;

	/*
		DESCRIPTION: Adds an item to the end of the array.
		PARAMETERS:
			const Type& _data, the item to add.
	*/
	void Append(const Type& _data);

	/*
		DESCRIPTION: Inserts an item at an index of the array.
		PARAMETERS:
			unsigned int _index, the index where the item is to be inserted.
			const Type& _data, the item to insert.
	*/
	void Insert(unsigned int _index, const Type& _data);

	/*
		DESCRIPTION: Removes the item at an index of the array.
		PARAMETERS:
			unsigned int _index, the index where the item is to remove.
	*/
	void Remove(unsigned int _index);

	/*
		DESCRIPTION: Returns if an item is in the array.
		PARAMETERS:
			const Type& _data, the item to find.
		RETURNS: bool - If the item is in the array.
	*/
	bool Find(const Type& _data);

	/*
		DESCRIPTION: Removes all the items in the array.
	*/
	void Clear();

	/*
		DESCRIPTION: Returns the number of items stored in the array.
		RETURNS: unsigned int - The size of the array.
	*/
	inline unsigned int Size() const;

	/*
		DESCRIPTION: Returns the number of items the array can store before needing to resize.
		RETURNS: unsigned int - The capacity of the array.
	*/
	inline unsigned int Capacity() const;

	/*
		DESCRIPTION: Reserves the amount memory needed for the desired capacity. 
		PARAMETERS:
			unsigned int _newCapacity, the desired capacity.
	*/
	void Reserve(unsigned int _newCapacity);

	/*
		DESCRIPTION: Reallocates the space used by the array so that it matches the array size.
	*/
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
