#pragma once

struct EquationRoots
{
	int numRoots;
	double roots[2];
};

EquationRoots Solve(double a, double b, double c);