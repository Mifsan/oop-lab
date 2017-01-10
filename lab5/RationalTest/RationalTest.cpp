#include "stdafx.h"
#include "../main/Rational.h"



void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

BOOST_AUTO_TEST_SUITE(Rational_number)

BOOST_AUTO_TEST_CASE(is_0_by_default)
{
	VerifyRational(CRational(), 0, 1);
}

BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
{
	VerifyRational(CRational(-_MAX_INT_DIG), -_MAX_INT_DIG, 1);
	VerifyRational(CRational(_MAX_INT_DIG), _MAX_INT_DIG, 1);
	VerifyRational(CRational(0), 0, 1);
}

BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
{
	VerifyRational(CRational(10, 3), 10, 3);
	VerifyRational(CRational(-10, 3), -10, 3);
	VerifyRational(CRational(10, -3), -10, 3);
	VerifyRational(CRational(-10, -3), 10, 3);
}

BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
{
	VerifyRational(CRational(6, 8), 3, 4);
	VerifyRational(CRational(6, -8), -3, 4);
	VerifyRational(CRational(-6, 8), -3, 4);
	VerifyRational(CRational(-6, -8), 3, 4);
	VerifyRational(CRational(-10, 20), -1, 2);
}

BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
{
	BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
{
	BOOST_CHECK_CLOSE_FRACTION(CRational(3, 4).ToDouble(), 0.75, 0.00001);
	BOOST_CHECK_CLOSE_FRACTION(CRational(8, 5).ToDouble(), 1.6, 0.00001);
	BOOST_CHECK_CLOSE_FRACTION(CRational(0).ToDouble(), 0, 0.00001);
}

BOOST_AUTO_TEST_CASE(has_unary_plus_that_returns_itself_without_changes)
{
	VerifyRational(CRational(1, 2), 1, 2);
	VerifyRational(CRational(5, 2), 5, 2);
	VerifyRational(CRational(0), 0, 1);
}

BOOST_AUTO_TEST_CASE(that_returns_itself_with_inverted_sign)
{
	VerifyRational(-CRational(4, 5), -4, 5);
	VerifyRational(-CRational(-4, 5), 4, 5);
	VerifyRational(-CRational(4, -5), 4, 5);
	VerifyRational(-CRational(-4, -5), -4, 5);
	VerifyRational(-CRational(0), 0, 1);
}

BOOST_AUTO_TEST_CASE(has_additional_operator)
{
	VerifyRational(CRational(1, 2) + CRational(1, 2), 1, 1);
	VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
	VerifyRational(CRational(1, 6) + CRational(1, 2), 2, 3);
	VerifyRational(CRational(1, 3) + 1, 4, 3);
	VerifyRational(1 + CRational(1, 3), 4, 3);
	VerifyRational(CRational(0) + CRational(1, 2), 1, 2);
	VerifyRational(CRational(1, 2) + CRational(0), 1, 2);
}

BOOST_AUTO_TEST_CASE(has_subtraction_operator)
{
	VerifyRational(CRational(1, 2) - CRational(1, 2), 0, 1);
	VerifyRational(CRational(1, 2) - CRational(1, 5), 3, 10);
	VerifyRational(CRational(1, 6) - CRational(1, 2), -1, 3);
	VerifyRational(CRational(1, 3) - 1, -2, 3);
	VerifyRational(1 - CRational(1, 2), 1, 2);
	VerifyRational(CRational(0) - CRational(1, 2), -1, 2);
	VerifyRational(CRational(1, 2) - CRational(0), 1, 2);
}

BOOST_AUTO_TEST_CASE(has_operation_of_addition_combined_with_assignment)
{
	VerifyRational(CRational(4, 100) += CRational(4, 100), 2, 25);
	VerifyRational(CRational(1, 3) += 0, 1, 3);
	VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
	VerifyRational(CRational(1, 2) += 1, 3, 2);
}

BOOST_AUTO_TEST_CASE(has_operation_of_substraction_combined_with_assignment)
{
	VerifyRational(CRational(4, 100) -= CRational(4, 100), 0, 1);
	VerifyRational(CRational(1, 3) -= 0, 1, 3);
	VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
	VerifyRational(CRational(1, 2) -= 1, -1, 2);
}

BOOST_AUTO_TEST_CASE(has_operation_of_multiplication)
{
	VerifyRational(CRational(1, 3) * 0, 0, 1);
	VerifyRational(0 * CRational(1, 3), 0, 1);
	VerifyRational(CRational(1, 6) * 2, 1, 3);
	VerifyRational(2 * CRational(1, 6), 1, 3);
	VerifyRational(CRational(1, 6) * -2, -1, 3);
	VerifyRational(-2 * CRational(1, 6), -1, 3);
	VerifyRational(CRational(3, 6) * CRational(3, 5), 3, 10);
	VerifyRational(CRational(3, 5) * CRational(3, 6), 3, 10);
}

BOOST_AUTO_TEST_CASE(has_operation_of_division)
{
	VerifyRational(CRational(1, 6) / 2, 1, 12);
	VerifyRational(2 / CRational(1, 6), 12, 1);
	VerifyRational(CRational(1, 6) / -2, -1, 12);
	VerifyRational(-2 / CRational(1, 6), -12, 1);
	VerifyRational(CRational(3, 6) / CRational(3, 5), 5, 6);
	VerifyRational(CRational(3, 5) / CRational(3, 6), 6, 5);
}

BOOST_AUTO_TEST_CASE(has_operation_of_multiplication_combined_with_assignment)
{
	VerifyRational(CRational(1, 3) *= 0, 0, 1);
	VerifyRational(CRational(1, 2) *= CRational(1, 6), 1, 12);
	VerifyRational(CRational(1, 2) *= 1, 1, 2);
	VerifyRational(CRational(2, 3) *= CRational(2, 3), 4, 9);
}

BOOST_AUTO_TEST_CASE(has_operation_of_division_combined_with_assignment)
{
	VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
	VerifyRational(CRational(1, 2) /= 1, 1, 2);
	VerifyRational(CRational(1, 2) /= CRational(1, 2), 1, 1);
}

BOOST_AUTO_TEST_CASE(cant_be_divided_on_0)
{
	BOOST_REQUIRE_THROW(CRational(1, 1) / 0, std::invalid_argument);
	BOOST_REQUIRE_THROW(CRational(1, 1) /= CRational(1, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(can_be_checked_for_equality)
{
	BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
	BOOST_CHECK(!(CRational(1, 2) == CRational(3, 2)));
	BOOST_CHECK(CRational(-3, 2) != CRational(3, 2));
	BOOST_CHECK(!(CRational(1, 2) != CRational(2, 4)));
	BOOST_CHECK(CRational(2, 1) == 2);
	BOOST_CHECK(2 == CRational(2, 1));
	BOOST_CHECK(!(CRational(1, 2) == 1));
	BOOST_CHECK(3 != CRational(-3, 1));
	BOOST_CHECK(!(CRational(-4, 1) != -4));
}

BOOST_AUTO_TEST_CASE(can_be_compared_with_operator_smaller)
{
	BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
	BOOST_CHECK(!(CRational(1, 3) < CRational(1, 3)));
	BOOST_CHECK(!(CRational(1, 3) < CRational(1, 4)));
	BOOST_CHECK(CRational(1, 3) < 1);
	BOOST_CHECK(!(1 < CRational(1, 3)));
	BOOST_CHECK(!(CRational(1, 1) < 1));
	BOOST_CHECK(!(CRational(3, 2) < 1));
	BOOST_CHECK((1 < CRational(3, 2)));
}

BOOST_AUTO_TEST_CASE(can_be_compared_with_operator_bigger)
{
	BOOST_CHECK(CRational(1, 2) > CRational(1, 3));
	BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
	BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
	BOOST_CHECK(1 > CRational(1, 2));
	BOOST_CHECK(!(CRational(1, 1) > 1));
	BOOST_CHECK(!(CRational(3, 2) > 3));
	BOOST_CHECK(3 > CRational(3, 2));
}

BOOST_AUTO_TEST_CASE(can_be_compared_with_operator_less_or_equal)
{
	BOOST_CHECK(CRational(1, 3) <= CRational(1, 2));
	BOOST_CHECK(CRational(1, 3) <= CRational(1, 3));
	BOOST_CHECK(!(CRational(1, 3) <= CRational(1, 4)));
	BOOST_CHECK(CRational(1, 3) <= 1);
	BOOST_CHECK(!(1 <= CRational(1, 3)));
	BOOST_CHECK(1 <= CRational(1, 1));
	BOOST_CHECK(!(CRational(3, 2) <= 1));
}

BOOST_AUTO_TEST_CASE(can_be_compared_with_operator_greater_or_equal)
{
	BOOST_CHECK(CRational(1, 2) > CRational(1, 3));
	BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
	BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
	BOOST_CHECK(1 >= CRational(1, 2));
	BOOST_CHECK(CRational(1, 1) >= 1);
	BOOST_CHECK(!(CRational(3, 2) >= 3));
}

BOOST_AUTO_TEST_CASE(can_be_written_to_ostream)
{
	{
		std::ostringstream output;
		output << CRational(-3, 14);
		BOOST_CHECK_EQUAL(output.str(), "-3/14");
	}
	{
		std::ostringstream output;
		output << "Rational = " << CRational(1, 14) << ".";
		BOOST_CHECK_EQUAL(output.str(), "Rational = 1/14.");
	}
	{
		std::ostringstream output;
		output << CRational(4);
		BOOST_CHECK_EQUAL(output.str(), "4/1");
	}
}

BOOST_AUTO_TEST_CASE(can_be_read_from_istream)
{
	{
		CRational rational;
		std::istringstream input("0");
		input >> rational;
		VerifyRational(rational, 0, 1);
	}
	{
		CRational rational;
		std::istringstream input("7/15");
		input >> rational;
		VerifyRational(rational, 7, 15);
	}
	{
		CRational rational;
		std::istringstream input("-1/1");
		input >> rational;
		VerifyRational(rational, -1, 1);
	}
	{
		CRational rational;
		std::istringstream input("not numeric string");
		input >> rational;
		BOOST_CHECK(input.fail());
	}
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_mixed_fraction)
{
	{
		CRational rational(16, 15);
		std::pair<int, CRational> expectedMixedFraction = std::make_pair(1, CRational(1, 15));
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, expectedMixedFraction.first);
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().second, expectedMixedFraction.second);
	}
	{
		CRational rational(-16, 15);
		std::pair<int, CRational> expectedMixedFraction = std::make_pair(-1, CRational(1, 15));
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().first, expectedMixedFraction.first);
		BOOST_CHECK_EQUAL(rational.ToCompoundFraction().second, expectedMixedFraction.second);
	}
}

BOOST_AUTO_TEST_SUITE_END()

