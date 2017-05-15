#include "stdafx.h"
#include "Controller.h"

using namespace std;
using namespace std::placeholders;


CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actions({
		{ "Help", bind(&CController::Help, this) },
		{ "Triangle", bind(&CController::CreateTriangle, this, _1) },
})
{
}

bool CController::HandleCommand()
{
	string commandLine;

	if (!getline(m_input, commandLine))
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
		<< "> Triangle <side1> <side2> <side3>\n";

	return true;
}

void CController::PrintTriangleInfo()
{
	m_output << "Perimeter: " << m_triangle[0].GetPerimeter() << endl
		<< "Area: " << m_triangle[0].GetArea() << endl;
}

bool CController::CreateTriangle(std::istream & args)
{
	try
	{
		double side1;
		double side2;
		double side3;

		if (!(args >> side1) || !(args >> side2) || !(args >> side3))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Triangle <side1> <side2> <side3>\n");
			
		}
		else
		{
			CTriangle currentTriangle(side1, side2, side3);
			m_triangle.clear();
			m_triangle.push_back(currentTriangle);
			PrintTriangleInfo();
			return true;
		}
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}