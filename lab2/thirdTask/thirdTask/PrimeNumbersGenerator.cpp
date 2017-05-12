#include "stdafx.h"
#include "PrimeNumbersGenerator.h"

using namespace std;

const int MAX_UPPER_BOUND = 100000000;
const int MIN_UPPER_BOUND = 2;

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
	for (int i = 2; i * i <= upperBound; i++)
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
