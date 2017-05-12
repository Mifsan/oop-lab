// Solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Solve.h"
#include <stdexcept>
#include <iostream>


void CheckCoefficient(double b)
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
		CheckCoefficient(a);
		EquationRoots EquationShouldBeSolved;
		double descriminant = pow(b, 2) - 4 * a * c;
		CheckDescriminant(descriminant);
		if (descriminant == 0)
		{
			EquationShouldBeSolved.numRoots = 1;
			EquationShouldBeSolved.roots[0] = -b / (2 * a);
		}
		else if (descriminant > 0)
		{
			EquationShouldBeSolved.numRoots = 2;
			EquationShouldBeSolved.roots[0] = (-b - sqrt(descriminant)) / (2 * a);
			EquationShouldBeSolved.roots[1] = (-b + sqrt(descriminant)) / (2 * a);
		}
		return EquationShouldBeSolved;
	}
	catch (...)
	{
		std::cout << "Unable to solve equation\n";
		throw;
	}
}