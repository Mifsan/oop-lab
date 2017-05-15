#include "stdafx.h"
#include "PrimeNumbersGenerator.h"

static const int MAX_UPPER_BOUND = 100000000;
static const int MIN_UPPER_BOUND = 2;

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if ((upperBound < MIN_UPPER_BOUND) || (upperBound > MAX_UPPER_BOUND))
	{
		set<int> emptySet{};
		return emptySet;
	}
	vector<bool> numbers(upperBound + 1, true);
	set<int> primeNumbersSet;
	numbers[0] = false;
	numbers[1] = false;
	for (int i = MIN_UPPER_BOUND; i * i <= upperBound; i++)
	{
		if (numbers[i])
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				numbers[j] = false;
			}
		}
	}
	for (int i = 0; i <= upperBound; i++)
	{
		if (numbers[i])
		{
			primeNumbersSet.insert(i);
		}
	}
	return primeNumbersSet;
}
