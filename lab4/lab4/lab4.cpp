#include "stdafx.h"
#include "Body.h"
#include "Controller.h"

using namespace std;

int main()
{
	CController controller(cin, cout);
	controller.Help();
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		controller.HandleCommand();
	}
	controller.PrintAllBodies();
	controller.FindBodyWithMaxMass();
	controller.FindBodyWithSmallestWeight();

	return 0;
}