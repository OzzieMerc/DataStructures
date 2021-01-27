/*
	FILE: AVLTreeTest.h
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: January 27, 2021
	DESCRIPTION: Tests the interface of the AVL Tree and also demonstrates how the data	structure
		can be used.
*/

#pragma once

#include "../UnitTests/UnitTest.h"
#include "../DataStructures/AVLTree.h"

namespace UT
{
	void TestAVLTree()
	{
		Test("AVLTree")
		{
			constexpr unsigned int NUM_COUNT = 10;
			const int numbers[NUM_COUNT] = { 8, 6, 7, 5, 3, 0, 9, 4, 2, 1 };

			Subtest("Insert()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);
			}

			Subtest("Remove()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Try removing when the tree is empty.
				Require(tree.Remove(16) == false)

					// Fill the tree with numbers.
					for (unsigned int i = 0; i < NUM_COUNT; ++i)
						tree.Insert(numbers[i]);

				// Remove all even numbers.
				for (unsigned int i = 2; i < NUM_COUNT; i += 2)
					Require(tree.Remove(i) == true)

					// Test if all even numbers were removed.
					for (unsigned int i = 1; i < NUM_COUNT; ++i)
					{
						if (i % 2 == 0)
							Require(tree.Remove(i) == false) // Even numbers should already be removed.
					}

				// Remove the rest.
				Require(tree.Remove(0) == true)

					for (unsigned int i = 1; i < NUM_COUNT; i += 2)
					{
						if (i % 2 != 0)
							Require(tree.Remove(i) == true) // Odd numbers should be removed during this call.
					}

				Require(tree.Remove(0) == false)
					Require(tree.Size() == 0)
			}

			Subtest("Find()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Try finding when the tree is empty.
				Require(tree.Find(16) == false)

					// Fill the tree with numbers.
					for (unsigned int i = 0; i < NUM_COUNT; ++i)
						tree.Insert(numbers[i]);

				// Test finding all numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(tree.Find(i) == true)

					// Test finding numbers not inserted.
					Require(tree.Find(1024) == false)
			}

			Subtest("Clear()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Try clearing an empty tree.
				tree.Clear();

				// Fill the tree with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);

				// Clear the tree.
				tree.Clear();
				Require(tree.Size() == 0)

					// Try finding all numbers previously inserted.
					for (unsigned int i = 0; i < NUM_COUNT; ++i)
						Require(tree.Find(i) == false)

						// Try removing all numbers previously inserted.
						for (unsigned int i = 0; i < NUM_COUNT; ++i)
							Require(tree.Remove(i) == false)
			}

			Subtest("Size()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				Require(tree.Size() == 0)

					// Fill the tree with numbers and test that size increases by one at each iteration.
					for (unsigned int i = 0; i < NUM_COUNT; ++i)
					{
						tree.Insert(numbers[i]);
						Require(tree.Size() == i + 1)
					}

				Require(tree.Size() == NUM_COUNT)
			}

			Subtest("Height()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				Require(tree.Height() == 0)

				const int expectedHeight[NUM_COUNT] = { 1, 2, 2, 3, 3, 4, 4, 4, 4, 5 };

				// Fill the tree with numbers and test that the height increases as expected.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
				{
					tree.Insert(numbers[i]);
					Require(tree.Height() == expectedHeight[i]);
				}
			}

			Subtest("ToArrayInorder()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Fill the tree with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);

				int toArrayResult[NUM_COUNT] = { 0 };
				tree.ToArrayInorder(toArrayResult);

				// Test if the array is inorder.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(toArrayResult[i] == i);
			}

			Subtest("ToArrayPreorder()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Fill the tree with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);

				const int expectedResult[NUM_COUNT] = { 4, 3, 2, 0, 1, 6, 5, 8, 7, 9 };
				int toArrayResult[NUM_COUNT] = { 0 };
				tree.ToArrayPreorder(toArrayResult);

				// Test if the array is in preorder.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(toArrayResult[i] == expectedResult[i]);
			}

			Subtest("ToArrayPostorder()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Fill the tree with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);

				const int expectedResult[NUM_COUNT] = { 1, 0, 2, 3, 5, 7, 9, 8, 6, 4 };
				int toArrayResult[NUM_COUNT] = { 0 };
				tree.ToArrayPostorder(toArrayResult);

				// Test if the array is in postorder.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(toArrayResult[i] == expectedResult[i]);
			}

			Subtest("ToArrayInReverseOrder()")
			{
				AVLTree<int> tree(
					[](const int& _lhs, const int& _rhs) { return _lhs < _rhs; },
					[](const int& _lhs, const int& _rhs) { return _lhs > _rhs; }
				);

				// Fill the tree with numbers.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					tree.Insert(numbers[i]);

				int toArrayResult[NUM_COUNT] = { 0 };
				tree.ToArrayInReverseOrder(toArrayResult);

				// Test if the array is in reverse order.
				for (unsigned int i = 0; i < NUM_COUNT; ++i)
					Require(toArrayResult[i] == NUM_COUNT - 1 - i);
			}
		}
	}
}
