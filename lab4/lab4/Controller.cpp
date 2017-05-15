#include "stdafx.h"
#include "Controller.h"

using namespace std;
using namespace std::placeholders;


CController::CController(std::istream & input, std::ostream & output)
	: m_input(input)
	, m_output(output)
	, m_actions({
		{ "Help", bind(&CController::Help, this) },
		{ "Sphere", bind(&CController::CreateSphere, this, _1) },
		{ "Parallelepiped", bind(&CController::CreateParallelepiped, this, _1) },
		{ "Cone", bind(&CController::CreateCone, this, _1) },
		{ "Cylinder", bind(&CController::CreateCylinder, this, _1) },
		{ "Compound", bind(&CController::CreateCompoundBody, this) },
})
{
}

bool CController::HandleCommand()
{
	string commandLine;

	if (!getline(m_input, commandLine) || (commandLine == "Finish"))
	{
		return false;
	}

	istringstream strm(commandLine);
	string action;
	strm >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		it->second(strm);
		return true;
	}

	m_output << "> Invalid command!" "\n";
	return false;
}

bool CController::Help()
{
	m_output << "Commands:\n"
		<< "> Sphere <density> <radius>\n"
		<< "> Parallelepiped <density> <width> <height> <depth>\n"
		<< "> Cone <density> <radius> <height>\n"
		<< "> Cylinder <density> <radius> <height>\n"
		<< "> Compound - to begining add elements to compound body\n"
		<< "> Finish - to finish add elements to compound body or exit\n";

	return true;
}

void CController::PrintAllBodies() const
{
	if (!m_bodies.empty())
	{
		for (auto &body : m_bodies)
		{
			m_output << body->ToString();
		}
	}
	else
	{
		m_output << "> You have not entered figures\n";
	}
}

void CController::FindBodyWithMaxMass() const
{
	if (!m_bodies.empty())
	{
		auto maxMassBody = m_bodies.front();
		for (auto body : m_bodies)
		{
			if (body->GetMass() > maxMassBody->GetMass())
			{
				maxMassBody = body;
			}
		}

		m_output << "> Figure with max mass is:\n\t" << maxMassBody->ToString();
	}
	else
	{
		m_output << "> You have not entered figures";
	}
}

void CController::FindBodyWithSmallestWeight() const
{
	if (!m_bodies.empty())
	{
		auto minWeightBody = m_bodies.front();

		const double G = 9.8;
		const double WATER_DENSITY = 1000;

		double minWeight = (minWeightBody->GetDensity() - WATER_DENSITY) * G * minWeightBody->GetVolume();
		double weight;

		for (auto body : m_bodies)
		{
			weight = (minWeightBody->GetDensity() - WATER_DENSITY) * G * minWeightBody->GetVolume();
			if (weight < minWeight)
			{
				minWeightBody = body;
				minWeight = weight;
			}
		}
		m_output << "> Figure with min weight is:\n\t" << minWeightBody->ToString();
	}
	else
	{
		m_output << "> You have not entered figures";
	}
}

std::vector<std::shared_ptr<CBody>> CController::GetVectorOfBodies() const
{
	return m_bodies;
}

bool CController::CreateSphere(std::istream& args)
{
	try
	{
		double density;
		double radius;

		if (!(args >> density) || !(args >> radius))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Sphere <density> <radius>\n");
		}
		shared_ptr<CBody> sphere = make_shared<CSphere>(density, radius);
		m_bodies.push_back(sphere);
		return true;
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}

bool CController::CreateParallelepiped(std::istream& args)
{
	try
	{
		double density;
		double width;
		double height;
		double depth;

		if (!(args >> density) || !(args >> width) || !(args >> height) || !(args >> depth))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Parallelepiped <density> <width> <height> <depth>\n");
		}
			shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, width, height, depth);
			m_bodies.push_back(parallelepiped);
			return true;
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}

bool CController::CreateCone(std::istream& args)
{
	try
	{
		double density;
		double height;
		double radius;

		if (!(args >> density) || !(args >> radius) || !(args >> height))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Cone <density> <radius> <height>\n");
		}
		shared_ptr<CBody> cone = make_shared<CCone>(density, radius, height);
		m_bodies.push_back(cone);
		return true;
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}

bool CController::CreateCylinder(std::istream& args)
{
	try
	{
		double density;
		double height;
		double radius;

		if (!(args >> density) || !(args >> radius) || !(args >> height))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Cylinder <density> <radius> <height>\n");
		}
		shared_ptr<CBody> cylinder = make_shared<CCone>(density, radius, height);
		m_bodies.push_back(cylinder);
		return true;
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}

bool CController::CreateCompoundBody()
{
	shared_ptr<CCompound> compound = make_shared<CCompound>();
	CController compoundController(m_input, m_output);
	while (m_output << "> ", compoundController.HandleCommand());
	m_output << "Finish add to compound" "\n";
	auto elements = compoundController.GetVectorOfBodies();
	for (auto element : elements)
	{
		compound->AddChildBody(element);
	}
	m_bodies.push_back(compound);
	return true;
}