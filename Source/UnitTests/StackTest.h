/*
	FILE: StackTest.h
	AUTHOR: Ozzie Mercado
	CREATED: January 31, 2021
	MODIFIED: January 31, 2021
	DESCRIPTION: Tests the interface of the Stack and also demonstrates how the data
		structure can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../DataStructures/Stack.h"

namespace UT
{
	void TestStack()
	{
		Test("Stack")
		{
			constexpr unsigned int NUM_COUNT = 10;
			const int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

			Subtest("Push()")
			{
				Stack<int> stack;

				// Fill the stack with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					stack.Push(numbers[i]);

				// Check that all numbers are in the stack in the reverse order.
				unsigned int i = 0;
				for (Stack<int>::Node* iter = stack.Peek(); iter; iter = iter->Next())
					Require(iter->Data() == numbers[NUM_COUNT - 1 - i++]);
			}

			Subtest("Pop()")
			{
				constexpr unsigned int HALF_COUNT = NUM_COUNT / 2;

				Stack<int> stack;

				// Fill the stack with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					stack.Push(numbers[i]);

				// Remove from front.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					stack.Pop();

				// Check that the numbers remaining in the stack are what is expected.
				const int expectedResult[HALF_COUNT] = { 3, 5, 7, 6, 8 };

				unsigned int i = 0;
				for (Stack<int>::Node* iter = stack.Peek(); iter; iter = iter->Next())
					Require(iter->Data() == expectedResult[i++]);

				// Remove the remaining numbers.
				for (unsigned int i = 0; i < HALF_COUNT; ++i)
					stack.Pop();

				Require(stack.Size() == 0);
			}

			Subtest("Find()")
			{
				Stack<int> stack;

				// Test finding a number when the stack is empty.
				Require(stack.Find(16) == false)

				// Fill the stack with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					stack.Push(i * 2);

				// Test finding numbers in the stack.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					if (i % 2 == 0)
						Require(stack.Find(i) == true)
					else
						Require(stack.Find(i) == false)
				}

				// Test finding a number not in the stack.
				Require(stack.Find(1024) == false)
			}

			Subtest("Clear()")
			{
				Stack<int> stack;

				// Try clearing an empty stack.
				stack.Clear();

				// Fill the stack with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					stack.Push(i);

				// Clear the stack.
				stack.Clear();
				Require(stack.Size() == 0)

				// Try finding all numbers previously inserted.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(stack.Find(i) == false)
			}

			Subtest("Size()")
			{
				Stack<int> stack1;

				Require(stack1.Size() == 0)

				// Fill the tree with numbers and test that size increases by one at each iteration.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					stack1.Push(numbers[i]);
					Require(stack1.Size() == i + 1)
				}

				Require(stack1.Size() == NUM_COUNT)
			}

			Subtest("Peek()")
			{
				Stack<int> stack;

				Require(stack.Peek() == nullptr);

				stack.Push(32);

				Require(stack.Peek() != nullptr);
				Require(stack.Peek()->Data() == 32);

				stack.Pop();

				Require(stack.Peek() == nullptr);
			}
		}
	}
}