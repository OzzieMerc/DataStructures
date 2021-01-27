/*
	FILE: DynamicArrayTest.h
	AUTHOR: Ozzie Mercado
	CREATED: January 27, 2021
	MODIFIED: January 27, 2021
	DESCRIPTION: Tests the interface of the Dynamic Array and also demonstrates how the data structure
		can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../DataStructures/DynamicArray.h"

namespace UT
{
	void TestDynamicArray()
	{
		Test("DynamicArray")
		{
			constexpr unsigned int NUM_COUNT = 10;
			const int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

			Subtest("Append()")
			{
				DynamicArray<int> dynArray;

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray.Append(numbers[i]);

				// Check that all numbers are in the array in the same order.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(dynArray[i] == numbers[i]);
			}

			Subtest("Insert()")
			{
				DynamicArray<int> dynArray1;

				// Insert numbers into the front of the array.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray1.Insert(0, numbers[i]);

				// Check that all numbers are in the array in the reverse order.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(dynArray1[i] == numbers[NUM_COUNT - 1 - i]);


				DynamicArray<int> dynArray2;

				// Insert numbers into the middle of the array.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray2.Insert(i/2, numbers[i]);

				// Check that all numbers are in the array in the reverse order.
				const int expectedResult[NUM_COUNT] = { 6, 5, 0, 4, 1, 2, 9, 3, 7, 8 };

				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(dynArray2[i] == expectedResult[i]);


				DynamicArray<int> dynArray3;

				// Insert numbers into the back of the array.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray3.Insert(i, numbers[i]);

				// Check that all numbers are in the array in order.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(dynArray3[i] == numbers[i]);
			}

			Subtest("Remove()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				DynamicArray<int> dynArray1;

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray1.Append(numbers[i]);

				// Remove from front.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					dynArray1.Remove(0);

				// Check that the numbers remaining in the array are what is expected.
				const int expectedResult1[HALF_COUNT] = { 0, 9, 4, 2, 1 };

				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					Require(dynArray1[i] == expectedResult1[i]);


				DynamicArray<int> dynArray2;

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray2.Append(numbers[i]);

				// Remove from middle.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					dynArray2.Remove((NUM_COUNT - i) / 2);

				// Check that all numbers are in the array in the reverse order.
				const int expectedResult2[HALF_COUNT] = { 8, 6, 7, 2, 1 };

				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					Require(dynArray2[i] == expectedResult2[i]);


				DynamicArray<int> dynArray3;

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray3.Append(numbers[i]);

				// Remove from back.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					dynArray3.Remove(NUM_COUNT - 1 - i);

				// Check that all numbers are in the array in order.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					Require(dynArray3[i] == numbers[i]);

				// Check that the numbers remaining in the array are what is expected.
				const int expectedResult3[HALF_COUNT] = { 8, 6, 7, 5, 3 };

				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					Require(dynArray3[i] == expectedResult3[i]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					dynArray3.Remove(0);

				Require(dynArray3.Size() == 0);
			}

			Subtest("Find()")
			{
				DynamicArray<int> dynArray;

				// Test finding a number when the array is empty.
				Require(dynArray.Find(16) == false)

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray.Append(i * 2);

				// Test finding numbers in the array.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					if (i % 2 == 0)
						Require(dynArray.Find(i) == true)
					else
						Require(dynArray.Find(i) == false)
				}

				// Test finding a number not in the array.
				Require(dynArray.Find(1024) == false)
			}

			Subtest("Clear()")
			{
				DynamicArray<int> dynArray;

				// Try clearing an empty array.
				dynArray.Clear();

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray.Append(i);

				// Clear the array.
				dynArray.Clear();
				Require(dynArray.Size() == 0)

				// Try finding all numbers previously inserted.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(dynArray.Find(i) == false)
			}

			Subtest("Size()")
			{
				DynamicArray<int> dynArray;

				Require(dynArray.Size() == 0)

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					dynArray.Append(numbers[i]);
					Require(dynArray.Size() == i + 1)
				}

				Require(dynArray.Size() == NUM_COUNT)
			}

			Subtest("Capacity()")
			{
				DynamicArray<int> dynArray;

				Require(dynArray.Capacity() == 0)

				// Fill the tree with numbers and test that capacity increases as expected.
				const int expectedResult[NUM_COUNT] = { 1, 2, 4, 4, 8, 8, 8, 8, 16, 16 };

				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					dynArray.Append(numbers[i]);
					Require(dynArray.Capacity() == expectedResult[i])
				}

				dynArray.Clear();
				Require(dynArray.Capacity() == 0)
			}

			Subtest("Reserve()")
			{
				DynamicArray<int> dynArray;

				dynArray.Reserve(4);
				Require(dynArray.Capacity() == 4)

				dynArray.Reserve(17);
				Require(dynArray.Capacity() == 17)

				dynArray.Reserve(8);
				Require(dynArray.Capacity() == 8)

				dynArray.Reserve(0);
				Require(dynArray.Capacity() == 0)
			}

			Subtest("ShrinkToFit()")
			{
				DynamicArray<int> dynArray;

				// Try shrinking an empty array.
				dynArray.ShrinkToFit();

				// Fill the array with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					dynArray.Append(i);

				Require(dynArray.Capacity() != dynArray.Size())
				
				// Test shrinking the array capacity to the array size.
				dynArray.ShrinkToFit();
				Require(dynArray.Capacity() == dynArray.Size())
			}
		}
	}
}
