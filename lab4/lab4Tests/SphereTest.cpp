#include "stdafx.h"

#include "../lab4/Sphere.h"

struct Sphere_
{
	const double expectedRadius = 10;
	const double expectedDensity = 10;
	const double expectedVolume = (pow(expectedRadius, 3) * M_PI) * 4 / 3;
	const CSphere sphere;
	Sphere_()
		: sphere(expectedDensity, expectedRadius)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Sphere_test, Sphere_)

BOOST_AUTO_TEST_CASE(has_a_body_type)
{
	BOOST_CHECK(static_cast<const CBody*>(&sphere));
}

BOOST_AUTO_TEST_CASE(has_a_radius)
{
	BOOST_CHECK_EQUAL(sphere.GetRadius(), expectedRadius);
}

BOOST_AUTO_TEST_CASE(has_a_density)
{
	BOOST_CHECK_EQUAL(sphere.GetDensity(), expectedDensity);
}

BOOST_AUTO_TEST_CASE(has_a_volume)
{
	BOOST_CHECK_CLOSE_FRACTION(sphere.GetVolume(), expectedVolume, 1e-7);
}

BOOST_AUTO_TEST_CASE(has_a_mass)
{
	BOOST_CHECK_CLOSE_FRACTION(sphere.GetMass(), expectedVolume * expectedDensity, 1e-7);
}

BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
{
	const std::string expectedString = "Sphere:\n\tdensity = 10\n\tvolume = 4188.790205\n\tmass = 41887.90205\n\tradius = 10\n";
	BOOST_CHECK_EQUAL(sphere.ToString(), expectedString);
}
BOOST_AUTO_TEST_CASE(can_handle_negative_values)
{
	BOOST_REQUIRE_THROW(CSphere(0, -5), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()