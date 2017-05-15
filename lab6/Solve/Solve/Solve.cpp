// Solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Solve.h"


void CheckCoefficientOfTheEquation(double b)
{
	if (b == 0)
	{
		throw std::invalid_argument("The coefficient of the x^2 can not be 0\n");
	}
}

double CheckDescriminant(double descriminant)
{
	if (descriminant < 0)
	{
		throw std::domain_error("The equation has no roots\n");
	}
	return descriminant;
}

EquationRoots Solve(double a, double b, double c)
{
	try
	{
		CheckCoefficientOfTheEquation(a);
		EquationRoots equationShouldBeSolved;
		double descriminant = pow(b, 2) - 4 * a * c;
		CheckDescriminant(descriminant);
		if (descriminant == 0)
		{
			equationShouldBeSolved.numRoots = 1;
			equationShouldBeSolved.roots[0] = -b / (2 * a);
		}
		else if (descriminant > 0)
		{
			equationShouldBeSolved.numRoots = 2;
			equationShouldBeSolved.roots[0] = (-b - sqrt(descriminant)) / (2 * a);
			equationShouldBeSolved.roots[1] = (-b + sqrt(descriminant)) / (2 * a);
		}
		return equationShouldBeSolved;
	}
	catch (...)
	{
		std::cout << "Unable to solve equation\n";
		throw;
	}
}