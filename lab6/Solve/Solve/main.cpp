#include "stdafx.h"
#include "Controller.h"

int main()
{
	CController controller(std::cin, std::cout);
	controller.Help();
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		controller.HandleCommand();
	}
	return 0;
}
