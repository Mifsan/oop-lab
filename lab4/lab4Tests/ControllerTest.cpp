#include "stdafx.h"
#include "../lab4/Controller.h"
#include "../lab4/Body.h"


using namespace std;


struct ControllerDependencies
{
	stringstream input;
	stringstream output;
};

struct ControllerFixture : ControllerDependencies
{
	CController controller;

	ControllerFixture()
		: controller(input, output)
	{
	}


	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		controller.HandleCommand();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Controller, ControllerFixture)

BOOST_AUTO_TEST_CASE(can_handle_sphere)
{
	const string expectedOutput = R"(Sphere:
	density = 5
	volume = 4188.790205
	mass = 20943.95102
	radius = 10
)";
	VerifyCommandHandling("Sphere 5 10", "");
	BOOST_CHECK(controller.GetVectorOfBodies().front()->GetDensity() == 5);
	BOOST_CHECK(controller.GetVectorOfBodies().front()->ToString() == expectedOutput);
}
BOOST_AUTO_TEST_CASE(can_handle_invalid_input)
{
	VerifyCommandHandling("Sphere 5", "Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
}
BOOST_AUTO_TEST_CASE(can_handle_negative_density)
{
	VerifyCommandHandling("Sphere -5 10", "Density should not be negative\n");
	BOOST_CHECK(controller.GetVectorOfBodies().empty());
}
BOOST_AUTO_TEST_CASE(can_handle_negative_params)
{
	VerifyCommandHandling("Sphere 5 -10", "Radius should not be negative\n");
	BOOST_CHECK(controller.GetVectorOfBodies().empty());
}
BOOST_AUTO_TEST_CASE(can_handle_compound_body)
{
	VerifyCommandHandling("Compound\nSphere 5 10\nFinish\n", "> > Finish add to compound\n");
	BOOST_CHECK(controller.GetVectorOfBodies().size() == 1);
}
BOOST_AUTO_TEST_CASE(can_handle_any_bodies)
{
	VerifyCommandHandling("Sphere 5 10\n", "");
	VerifyCommandHandling("Compound\nSphere 5 10\nFinish\n", "> > Finish add to compound\n");
	VerifyCommandHandling("Compound\nSphere 5 10\nCompound\nCone 1 2 3\nCylinder 4 5 6\nSphere 1 1\nFinish\n", "> > > > > > Finish add to compound\n> Finish add to compound\n");
	BOOST_CHECK(controller.GetVectorOfBodies().size() == 3);
}
BOOST_AUTO_TEST_SUITE_END()