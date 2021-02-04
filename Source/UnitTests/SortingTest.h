/*
	FILE: SortingTest.h
	AUTHOR: Ozzie Mercado
	CREATED: February 3, 2021
	MODIFIED: February 4, 2021
	DESCRIPTION: Tests the various sorting functions and how they can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../Algorithms/Sorting.h"

namespace UT
{
	void TestSorting()
	{
		Test("Sorting")
		{
			constexpr unsigned int NUM_COUNT = 10;

			Subtest("BubbleSort()")
			{
				int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

				// Sort lowest to highest.
				Sort::BubbleSort<int>(numbers, NUM_COUNT, [](const int& _lhs, const int& _rhs) { return _lhs > _rhs; });

				for (unsigned int i = 1; i < NUM_COUNT; ++i)
					Require(numbers[i - 1] < numbers[i]);

				// Sort highest to lowest.
				Sort::BubbleSort<int>(numbers, NUM_COUNT, [](const int& _lhs, const int& _rhs) { return _lhs < _rhs; });

				for (unsigned int i = 1; i < NUM_COUNT; ++i)
					Require(numbers[i - 1] > numbers[i]);
			}

			Subtest("BubbleSortAscending()") // Lowest to highest.
			{
				int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

				Sort::BubbleSortAscending<int>(numbers, NUM_COUNT);

				for (unsigned int i = 1; i < NUM_COUNT; ++i)
					Require(numbers[i - 1] < numbers[i]);
			}

			Subtest("BubbleSortDescending()") // Highest to lowest.
			{
				int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

				Sort::BubbleSortDescending<int>(numbers, NUM_COUNT);

				for (unsigned int i = 1; i < NUM_COUNT; ++i)
					Require(numbers[i - 1] > numbers[i]);
			}
		}
	}
}
