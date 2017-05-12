#include "stdafx.h"
#include <string>
#include <iostream>

/*
���� ���������� ����� ����������� �� ����������. ������� ������� ����� �������� � �����, ��� ���� ��� ��������� �����, � ������
�������� ����� ����� 2 ������� (������� � ����� ������� � �� ����� ������ � ������), �� �� ����������� ������� ������� ������.
���������� ������ ����� ������������ ������, �� 000000 �� 999999. ������� ����� ����� "���������� ��� ����" �������
����� ������������ ������� ����� ����?
*/

namespace
{
	const unsigned LOWER_BOUND = 0;
	const unsigned UPPER_BOUND = 1000000;
}

short GetNumberOfFive(size_t number);

int main()
{
	unsigned short requeredNumberOfFive = 0;
	std::cout << "Enter requered number of 5: ";
	std::cin >> requeredNumberOfFive;
	unsigned numberOfLuckyTickets = 0;

	for (size_t i = LOWER_BOUND; i < UPPER_BOUND; ++i)
	{
		if (requeredNumberOfFive == GetNumberOfFive(i))
		{
			++numberOfLuckyTickets;
		}
	}
	std::cout << "number of lucky tickets:" << numberOfLuckyTickets << std::endl;
	return EXIT_SUCCESS;
}

short GetNumberOfFive(size_t number)
{
	short numberOfFive = 0;

	size_t startPosition = 0;
	std::string tmp = std::to_string(number);
	while (tmp.find("5", startPosition) != std::string::npos)
	{
		startPosition = tmp.find("5", startPosition) + 1;
		++numberOfFive;
	}
	return numberOfFive;
}
