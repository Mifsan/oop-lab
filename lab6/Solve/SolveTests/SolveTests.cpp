#include "stdafx.h"
#include "../Solve/Solve.h"

using namespace std;

void CheckEqualEquations(EquationRoots sampleEquation, EquationRoots resultRoots)
{
	for (size_t i = 0; i < sampleEquation.numRoots; ++i)
	{
		BOOST_CHECK_CLOSE_FRACTION(resultRoots.roots[i], sampleEquation.roots[i], 9e-3);
	}
}

BOOST_AUTO_TEST_SUITE(function_Solve)

BOOST_AUTO_TEST_CASE(can_solve_equation_with_one_root)
{
	EquationRoots sampleEquation;
	sampleEquation.numRoots = 1;
	sampleEquation.roots[0] = -1;
	CheckEqualEquations(sampleEquation, Solve(2, 4, 2));
}

BOOST_AUTO_TEST_CASE(can_solve_equation_with_two_roots)
{
	EquationRoots sampleEquation;
	sampleEquation.numRoots = 2;
	sampleEquation.roots[0] = -1;
	sampleEquation.roots[1] = -0.666;
	CheckEqualEquations(sampleEquation, Solve(3, 5, 2));
}

BOOST_AUTO_TEST_CASE(can_handle_negative_descriminant)
{
	BOOST_REQUIRE_THROW(Solve(5, 1, 5), std::domain_error);
}

BOOST_AUTO_TEST_CASE(can_handle_the_coefficient_at_x_in_the_second_degree_equal_zero)
{
	BOOST_REQUIRE_THROW(Solve(0, 2, 5), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()