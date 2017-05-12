#include "stdafx.h"
#include "..\thirdTask\PrimeNumbersGenerator.h"

using namespace std;


BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

BOOST_AUTO_TEST_CASE(generate_empty_set)
{
	set<int> expectedResult{};
	auto result = GeneratePrimeNumbersSet(1);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_is_2)
{
	set<int> expectedResult{ 2 };
	auto result = GeneratePrimeNumbersSet(2);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_is_3)
{
	set<int> expectedResult{ 2, 3 };
	auto result = GeneratePrimeNumbersSet(3);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(generate_set_more_than_max)
{
	set<int> expectedResult{};
	auto result = GeneratePrimeNumbersSet(100000001);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(generate_set_of_500_primes)
{
	auto expectedResult = 500;
	auto result = GeneratePrimeNumbersSet(3571);

	BOOST_CHECK(result.size() == expectedResult);
}

#ifndef _DEBUG
BOOST_AUTO_TEST_CASE(generate_max_size_set)
{
	auto expectedResult = 5761455;
	auto result = GeneratePrimeNumbersSet(100000000);

	BOOST_CHECK(result.size() == expectedResult);
}
#endif

BOOST_AUTO_TEST_SUITE_END()