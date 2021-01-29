/*
	FILE: main.cpp
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: January 29, 2021
	DESCRIPTION: This is the entry point for the unit testing of all data structures developed.
*/

#include "UnitTests/UnitTest.h"

#include "UnitTests/AVLTreeTest.h"
#include "UnitTests/BinarySearchTreeTest.h"
#include "UnitTests/DoublyLinkedListTest.h"
#include "UnitTests/DynamicArrayTest.h"
#include "UnitTests/SinglyLinkedListTest.h"

/*
	DESCRIPTION: Entry-point for the program.
	PARAMETERS: Not used.
	RETURNS: Not used. 0 always.
*/
int main(int _argCount, char** _argVals)
{
	UT::Start();

	UT::TestAVLTree();
	UT::TestBinarySearchTree();
	UT::TestDoublyLinkedList();
	UT::TestDynamicArray();
	UT::TestSinglyLinkedList();

	UT::End();

	return 0;
}
