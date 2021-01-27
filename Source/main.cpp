/*
	FILE: main.cpp
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: January 26, 2021
	DESCRIPTION: This is the entry point for the unit testing of all data structures developed.
*/

#include "UnitTests/UnitTest.h"
#include "UnitTests/BinarySearchTreeTest.h"

/*
	DESCRIPTION: Entry-point for the program.
	PARAMETERS: Not used.
	RETURNS: Not used. 0 always.
*/
int main(int _argCount, char** _argVals)
{
	UT::Start();

	UT::TestBinarySearchTree();

	UT::End();

	return 0;
}
