/*
	FILE: SinglyLinkedListTest.h
	AUTHOR: Ozzie Mercado
	CREATED: January 27, 2021
	MODIFIED: January 29, 2021
	DESCRIPTION: Tests the interface of the Singly-Linked Lsit and also demonstrates how the data
		structure can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../DataStructures/SinglyLinkedList.h"

namespace UT
{
	void TestSinglyLinkedList()
	{
		Test("SinglyLinkedList")
		{
			constexpr unsigned int NUM_COUNT = 10;
			const int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

			Subtest("AddHead()")
			{
				SinglyLinkedList<int> list;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddHead(numbers[i]);

				// Check that all numbers are in the list in the reverse order.
				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == numbers[NUM_COUNT - 1 - i++]);
			}

			Subtest("AddTail()")
			{
				SinglyLinkedList<int> list;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddTail(numbers[i]);

				// Check that all numbers are in the list in the same order.
				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == numbers[i++]);
			}

			Subtest("Insert()")
			{
				SinglyLinkedList<int> list1;

				// Insert numbers into the front of the list.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list1.Insert(list1.PeekHead(), numbers[i]);

				// Check that all numbers are in the list in the reverse order.
				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list1.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == numbers[NUM_COUNT - 1 - i++]);


				SinglyLinkedList<int> list2;

				// Insert numbers into the middle of the list.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					const unsigned int HALF_COUNT = list2.Size() / 2;

					SinglyLinkedList<int>::Node* iter = list2.PeekHead();
					for (unsigned int j = 0; j < HALF_COUNT; ++j)
						iter = iter->Next();

					list2.Insert(iter, numbers[i]);
				}

				// Check that all numbers are in the list in the reverse order.
				const int expectedResult1[NUM_COUNT] = { 6, 5, 0, 4, 1, 2, 9, 3, 7, 8 };

				i = 0;
				for (SinglyLinkedList<int>::Node* iter = list2.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult1[i++]);


				SinglyLinkedList<int> list3;

				// Insert numbers into the back of the list.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list3.Insert(list3.PeekTail(), numbers[i]);

				// Check that all numbers are in the list in order.
				const int expectedResult2[NUM_COUNT] = { 6, 7, 5, 3, 0, 9, 4, 2, 1, 8 };
				i = 0;
				for (SinglyLinkedList<int>::Node* iter = list3.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult2[i++]);
			}

			Subtest("Remove()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				SinglyLinkedList<int> list1;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list1.AddTail(numbers[i]);

				// Remove from front.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list1.Remove(list1.PeekHead());

				// Check that the numbers remaining in the list are what is expected.
				const int expectedResult1[HALF_COUNT] = { 0, 9, 4, 2, 1 };

				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list1.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult1[i++]);


				SinglyLinkedList<int> list2;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list2.AddTail(numbers[i]);

				// Remove from middle.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
				{
					const unsigned int HALF_SIZE = list2.Size() / 2;

					SinglyLinkedList<int>::Node* iter = list2.PeekHead();
					for (unsigned int j = 0; j < HALF_SIZE; ++j)
						iter = iter->Next();

					list2.Remove(iter);
				}

				// Check that all numbers are in the list in the reverse order.
				const int expectedResult2[HALF_COUNT] = { 8, 6, 7, 2, 1 };

				i = 0;
				for (SinglyLinkedList<int>::Node* iter = list2.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult2[i++]);


				SinglyLinkedList<int> list3;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list3.AddTail(numbers[i]);

				// Remove from back.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list3.Remove(list3.PeekTail());

				// Check that the numbers remaining in the list are what is expected.
				const int expectedResult3[HALF_COUNT] = { 8, 6, 7, 5, 3 };

				i = 0;
				for (SinglyLinkedList<int>::Node* iter = list3.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult3[i++]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list3.Remove(list3.PeekHead());

				Require(list3.Size() == 0);
			}

			Subtest("RemoveHead()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				SinglyLinkedList<int> list;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddTail(numbers[i]);

				// Remove from front.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list.RemoveHead();

				// Check that the numbers remaining in the list are what is expected.
				const int expectedResult[HALF_COUNT] = { 0, 9, 4, 2, 1 };

				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult[i++]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list.RemoveHead();

				Require(list.Size() == 0);
			}

			Subtest("RemoveTail()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				SinglyLinkedList<int> list;

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddTail(numbers[i]);

				// Remove from back.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list.RemoveTail();

				// Check that the numbers remaining in the list are what is expected.
				const int expectedResult[HALF_COUNT] = { 8, 6, 7, 5, 3 };

				unsigned int i = 0;
				for (SinglyLinkedList<int>::Node* iter = list.PeekHead(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult[i++]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					list.RemoveTail();

				Require(list.Size() == 0);
			}

			Subtest("Find()")
			{
				SinglyLinkedList<int> list;

				// Test finding a number when the list is empty.
				Require(list.Find(16) == false)

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddTail(i * 2);

				// Test finding numbers in the list.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					if (i % 2 == 0)
						Require(list.Find(i) == true)
					else
						Require(list.Find(i) == false)
				}

				// Test finding a number not in the list.
				Require(list.Find(1024) == false)
			}

			Subtest("Clear()")
			{
				SinglyLinkedList<int> list;

				// Try clearing an empty list.
				list.Clear();

				// Fill the list with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					list.AddTail(i);

				// Clear the list.
				list.Clear();
				Require(list.Size() == 0)

				// Try finding all numbers previously inserted.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(list.Find(i) == false)
			}

			Subtest("Size()")
			{
				SinglyLinkedList<int> list1;

				Require(list1.Size() == 0)

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					list1.AddHead(numbers[i]);
					Require(list1.Size() == i + 1)
				}

				Require(list1.Size() == NUM_COUNT)


				SinglyLinkedList<int> list2;

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					const unsigned int HALF_COUNT = list2.Size() / 2;

					SinglyLinkedList<int>::Node* iter = list2.PeekHead();
					for (unsigned int j = 0; j < HALF_COUNT; ++j)
						iter = iter->Next();

					list2.Insert(iter, numbers[i]);
					Require(list2.Size() == i + 1)
				}

				Require(list2.Size() == NUM_COUNT)


				SinglyLinkedList<int> list3;

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					list3.AddTail(numbers[i]);
					Require(list3.Size() == i + 1)
				}

				Require(list3.Size() == NUM_COUNT)
			}

			Subtest("PeekHead()")
			{
				SinglyLinkedList<int> list;

				Require(list.PeekHead() == nullptr);

				list.AddHead(32);

				Require(list.PeekHead() != nullptr);
				Require(list.PeekHead()->Data() == 32);

				list.RemoveHead();

				Require(list.PeekHead() == nullptr);
			}

			Subtest("PeekTail()")
			{
				SinglyLinkedList<int> list;

				Require(list.PeekTail() == nullptr);

				list.AddTail(32);

				Require(list.PeekTail() != nullptr);
				Require(list.PeekTail()->Data() == 32);

				list.RemoveTail();

				Require(list.PeekTail() == nullptr);
			}
		}
	}
}