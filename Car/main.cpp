// Car.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Car.h"
#include "CarController.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, "rus");
	CCar validCar;
	CCarController carController(validCar, cin, cout);
	vector<string> command;

	while (carController.GetCommand(command))
	{
		carController.HandleCommand(command);
	}
	return EXIT_SUCCESS;
}
