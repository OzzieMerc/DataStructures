/*
	FILE: main.cpp
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: February 1, 2021
	DESCRIPTION: This is the entry point for the unit testing of all data structures developed.
*/

#include "UnitTests/UnitTest.h"

// Data structure test includes.
#include "UnitTests/AVLTreeTest.h"
#include "UnitTests/BinarySearchTreeTest.h"
#include "UnitTests/DoublyLinkedListTest.h"
#include "UnitTests/DynamicArrayTest.h"
#include "UnitTests/SinglyLinkedListTest.h"
#include "UnitTests/StackTest.h"
#include "UnitTests/QueueTest.h"

// Algorithm test includes.
#include "UnitTests/SortingTest.h"

/*
	DESCRIPTION: Entry-point for the program.
	PARAMETERS: Not used.
	RETURNS: Not used. 0 always.
*/
int main(int _argCount, char** _argVals)
{
	UT::Start();

	// Test Data Structures.
	UT::TestAVLTree();
	UT::TestBinarySearchTree();
	UT::TestDoublyLinkedList();
	UT::TestDynamicArray();
	UT::TestSinglyLinkedList();
	UT::TestStack();
	UT::TestQueue();

	// Test Algorithms.
	UT::TestSorting();

	UT::End();

	return 0;
}
