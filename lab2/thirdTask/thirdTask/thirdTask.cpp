// thirdTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PrimeNumbersGenerator.h"
#include <iostream>
#include <algorithm>

#include <iterator>
using namespace std;

const int MAX_NUM_OF_ARG = 2;

const int MAX_DISCHARGE = 10;

bool CheckArgCount(const int& argc);

bool CheckArgument(const char* arg);

int main(int argc, char* argv[])
{
	if (CheckArgCount(argc))
	{
		cout << "Invalid arguments count\n"
			<< "Usage: thirdTask.exe <Upper bound of values(max processing value: 100000000)>";
		return 1;
	}
	if (!CheckArgument(argv[1]))
	{
		return 1;
	}
	set<int> primeNumbers = GeneratePrimeNumbersSet(atoi(argv[1]));
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

bool CheckArgument(const char* arg)
{
	for (size_t i = 0; i < strlen(arg); i++)
	{
		if (!isdigit(arg[i]))
		{
			cout << "Invalid argument, argument must be a positive number\n";
			return false;
		}
	}
	if ((strlen(arg) > MAX_DISCHARGE) || (atof(arg) > INT_MAX))
	{
		cout << "Invalid argument, the argument can not exceed the maximum integer\n";
		return false;
	}
	return true;
}

bool CheckArgCount(const int& argc)
{
	return (argc != MAX_NUM_OF_ARG);
}

