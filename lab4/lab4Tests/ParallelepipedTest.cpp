#include "stdafx.h"
#include "../lab4/Parallelepiped.h"

struct Parallelepiped_
{
	const double expectedWidth = 8;
	const double expectedHeight = 5;
	const double expectedDepth = 2;
	const double expectedDensity = 20;
	const double expectedVolume = expectedWidth * expectedHeight * expectedDepth;
	const CParallelepiped sparallelepiped;
	Parallelepiped_()
		: sparallelepiped(expectedDensity, expectedWidth, expectedHeight, expectedDepth)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Parallelepiped_test, Parallelepiped_)

BOOST_AUTO_TEST_CASE(has_a_body_type)
{
	BOOST_CHECK(static_cast<const CBody*>(&sparallelepiped));
}

BOOST_AUTO_TEST_CASE(has_a_width)
{
	BOOST_CHECK_EQUAL(sparallelepiped.GetWidth(), expectedWidth);
}

BOOST_AUTO_TEST_CASE(has_a_height)
{
	BOOST_CHECK_EQUAL(sparallelepiped.GetHeight(), expectedHeight);
}

BOOST_AUTO_TEST_CASE(has_a_depth)
{
	BOOST_CHECK_EQUAL(sparallelepiped.GetDepth(), expectedDepth);
}

BOOST_AUTO_TEST_CASE(has_a_density)
{
	BOOST_CHECK_EQUAL(sparallelepiped.GetDensity(), expectedDensity);
}

BOOST_AUTO_TEST_CASE(has_a_volume)
{
	BOOST_CHECK_CLOSE_FRACTION(sparallelepiped.GetVolume(), expectedVolume, 1e-7);
}

BOOST_AUTO_TEST_CASE(has_a_mass)
{
	BOOST_CHECK_CLOSE_FRACTION(sparallelepiped.GetMass(), expectedVolume * expectedDensity, 1e-7);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const std::string expectedString = "Parallelepiped:\n\tdensity = 20\n\tvolume = 80\n\tmass = 1600\n\twidth = 8\n\theight = 5\n\tdepth = 2\n";
	BOOST_CHECK_EQUAL(sparallelepiped.ToString(), expectedString);
}
BOOST_AUTO_TEST_CASE(can_handle_negative_values)
{
	BOOST_REQUIRE_THROW(CParallelepiped(1, -5, 2, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CParallelepiped(1, 5, -2, 3), std::invalid_argument);
	BOOST_REQUIRE_THROW(CParallelepiped(1, 5, 2, -3), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
