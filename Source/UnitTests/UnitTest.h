/*
	FILE: UnitTest.h
	AUTHOR: Ozzie Mercado
	CREATED: January 26, 2021
	MODIFIED: January 26, 2021
	DESCRIPTION: Defines functions for conducting tests and printing out results. Inspired by Catch2.
*/

#pragma once

#include <chrono>
#include <iostream>
#include <string>

#define Test(_testName)\
	testName = _testName;\
	if (!testStarted)\
		std::cout << "ERROR: Start() not called. Test skipped.\n";\
	else

#define Subtest(_subtestName)\
	subtestName = _subtestName;\
	if (!testStarted)\
		std::cout << "ERROR: Start() not called. Subtest skipped.\n";\
	else

#define Require(_condition)\
	if (true) /* if (true) used to avoid warnings on Mac.*/\
	{\
		if (!testStarted)\
			std::cout << "ERROR: Start() not called. Require skipped.\n"; \
		else\
		{\
			++total; \
			if (!(_condition))\
			{\
				++failures; \
				std::cout\
					<< testName << " -> " << subtestName << std::endl\
					<< "\tTest failed with requirement:" << std::endl\
					<< "\t\t"#_condition << std::endl; \
			}\
			else\
			{\
				++passes; \
			}\
		}\
	}

namespace UT
{
	namespace
	{
		std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
		unsigned int total = 0;
		unsigned int passes = 0;
		unsigned int failures = 0;
		std::string testName = "Unnamed test";
		std::string subtestName = "";
		bool testStarted = false;
	}

	void Start()
	{
		if (testStarted)
			std::cout << "WARNING: Start() was already called. Expected call to End() before Start() is called again.\n";

		std::cout
			<< "STARTING TESTS\n"
			<< "--------------\n";

		total = passes = failures = 0;
		testName = "Unnamed test";
		subtestName = "";
		testStarted = true;
		startTime = std::chrono::high_resolution_clock::now();
	}

	void End()
	{
		if (!testStarted)
		{
			std::cout << "ERROR: Start() must be called before End().\n";
			return;
		}

		testStarted = false;

		std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

		std::cout
			<< "--------------\n"
			<< "TESTING COMPLETE:\n"
			<< "\tPasses: " << passes << std::endl
			<< "\tFailures: " << failures << std::endl
			<< "\tTotal: " << total << std::endl;

		if (total == 0)
			std::cout << "\tNo tests were conducted.\n";
		else if (failures == 0)
			std::cout << "\tALL TESTS PASSED!\n";
		else
			std::cout << "\t% Passed: " << (passes / static_cast<float>(total) * 100) << std::endl;

		std::cout 
			<< "\tDuration: " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() 
			<< " milliseconds" << std::endl;
	}
}
