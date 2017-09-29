// FlipByte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

bool IsValidArgumentsCount(const int & argc)
{
	return (argc == 2);
}

bool IsValidArgument(const char* argv)
{
	int i = 0;
	do
	{
		if (isdigit(argv[i]) && i < 4)
		{
			i++;
		}
		else
		{
			i++;
			return false;
		}
	} while (argv[i] != '\0');

	auto checkRange = atoi(argv);
	if (checkRange < 0 || checkRange > 255)
	{
		return false;
	}
	return true;
}

unsigned char FlipBits(unsigned char number)
{
	unsigned char result = 0;
	for (size_t i = 0; i < 8; i++)
	{
		result = result << 1;
		if ((number & 1) == 1)
		{
			result |= 1;
		}
		number = number >> 1;
	}
	return result;
}

int main(int argc, char* argv[])
{
	if (!IsValidArgumentsCount(argc))
	{
		cout << "flipbyte.exe using: <natural number less than or equal to 255>" << endl;
		return 1;
	}
	if (!IsValidArgument(argv[1]))
	{
		cout << "Invalid argument, argument should be <natural number less than or equal to 255>" << endl;
		return 1;
	}

	unsigned char value = atoi(argv[1]);
	cout << int(FlipBits(value)) << endl;

    return 0;
}

