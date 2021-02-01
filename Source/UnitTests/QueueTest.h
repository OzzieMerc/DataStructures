/*
	FILE: QueueTest.h
	AUTHOR: Ozzie Mercado
	CREATED: February 1, 2021
	MODIFIED: February 1, 2021
	DESCRIPTION: Tests the interface of the Queue and also demonstrates how the data
		structure can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../DataStructures/Queue.h"

namespace UT
{
	void TestQueue()
	{
		Test("Queue")
		{
			constexpr unsigned int NUM_COUNT = 10;
			const int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

			Subtest("Enqueue()")
			{
				Queue<int> queue;

				// Fill the queue with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					queue.Enqueue(numbers[i]);

				// Check that all numbers are in the queue in order.
				unsigned int i = 0;
				for (Queue<int>::Node* iter = queue.Peek(); iter; iter = iter->Next())
					Require(iter->Data() == numbers[i++]);
			}

			Subtest("Dequeue()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				Queue<int> queue;

				// Fill the queue with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					queue.Enqueue(numbers[i]);

				// Remove from front.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					queue.Dequeue();

				// Check that the numbers remaining in the queue are what is expected.
				const int expectedResult[HALF_COUNT] = { 0, 9, 4, 2, 1 };

				unsigned int i = 0;
				for (Queue<int>::Node* iter = queue.Peek(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult[i++]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					queue.Dequeue();

				Require(queue.Size() == 0);
			}

			Subtest("Find()")
			{
				Queue<int> queue;

				// Test finding a number when the queue is empty.
				Require(queue.Find(16) == false)

				// Fill the queue with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					queue.Enqueue(i * 2);

				// Test finding numbers in the queue.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					if (i % 2 == 0)
						Require(queue.Find(i) == true)
					else
						Require(queue.Find(i) == false)
				}

				// Test finding a number not in the queue.
				Require(queue.Find(1024) == false)
			}

			Subtest("Clear()")
			{
				Queue<int> queue;

				// Try clearing an empty queue.
				queue.Clear();

				// Fill the queue with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					queue.Enqueue(i);

				// Clear the queue.
				queue.Clear();
				Require(queue.Size() == 0)

				// Try finding all numbers previously inserted.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(queue.Find(i) == false)
			}

			Subtest("Size()")
			{
				Queue<int> queue1;

				Require(queue1.Size() == 0)

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					queue1.Enqueue(numbers[i]);
					Require(queue1.Size() == i + 1)
				}

				Require(queue1.Size() == NUM_COUNT)
			}

			Subtest("Peek()")
			{
				Queue<int> queue;

				Require(queue.Peek() == nullptr);

				queue.Enqueue(32);

				Require(queue.Peek() != nullptr);
				Require(queue.Peek()->Data() == 32);

				queue.Dequeue();

				Require(queue.Peek() == nullptr);
			}
		}
	}
}