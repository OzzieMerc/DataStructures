/*
	FILE: Sorting.h
	AUTHOR: Ozzie Mercado
	CREATED: February 3, 2021
	MODIFIED: February 4, 2021
	DESCRIPTION: A collection of various templated sorting algrorithms.
*/

#pragma once

#include <assert.h>
#include <functional> // Used for comparison functions.

namespace Sort
{
	/*
		DESCRIPTION: Swaps item A with item B.
		PARAMETERS:
			Type& _a, item A.
			Type& _b, item B.
	*/
	template<typename Type>
	inline void Swap(Type& _a, Type& _b)
	{
		Type temp = _a;
		_a = _b;
		_b = temp;
	}

	/*
		DESCRIPTION: Swaps adjacent items in the array until the array is sorted.
		PARAMETERS:
			Type* _array, the array to sort.
			unsigned int _arraySize, the number of items in the array.
			std::function<bool(const Type&, const Type&)> _comparisionFunc, function to determine order.
	*/
	template<typename Type>
	void BubbleSort(Type* _array, unsigned int _arraySize, std::function<bool(const Type&, const Type&)> _comparisionFunc)
	{
		for (unsigned int i = 0; i < _arraySize - 1; ++i)
		{
			bool swapped = false;

			for (unsigned int j = 0; j < _arraySize - i - 1; ++j)
				if (_comparisionFunc(_array[j], _array[j + 1]))
				{
					Swap<Type>(_array[j], _array[j + 1]);
					swapped = true;
				}

			if (!swapped)
				break;
		}
	}

	/*
		DESCRIPTION: Swaps adjacent items in the array until the array is sorted in ascending order.
		PARAMETERS:
			Type* _array, the array to sort.
			unsigned int _arraySize, the number of items in the array.
	*/
	template<typename Type>
	void BubbleSortAscending(Type* _array, unsigned int _arraySize)
	{
		BubbleSort<Type>(_array, _arraySize, [](const int& _lhs, const int& _rhs) { return _lhs > _rhs; });
	}

	/*
		DESCRIPTION: Swaps adjacent items in the array until the array is sorted in descending order.
		PARAMETERS:
			Type* _array, the array to sort.
			unsigned int _arraySize, the number of items in the array.
	*/
	template<typename Type>
	void BubbleSortDescending(Type* _array, unsigned int _arraySize)
	{
		BubbleSort<Type>(_array, _arraySize, [](const int& _lhs, const int& _rhs) { return _lhs < _rhs; });
	}
}
