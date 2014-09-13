/** 
 * \file main.cpp
 * \brief This code executes all tests using gtest.
 * 
 * @author: Eder A. Perez.
 */

#include "gtest/gtest.h"
#include "allTests.h"



int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}