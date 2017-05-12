#include "stdafx.h"
#include "Controller.h"

using namespace std;
using namespace std::placeholders;


CController::CController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actions({
		{ "Help", bind(&CController::Help, this) },
		{ "Solve", bind(&CController::SolveTheEquation, this, _1) },
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
		<< "> Solve <coef a> <coef b> <coef c>\n";

	return true;
}

void CController::PrintSolution()
{
	m_output << "The number of roots: " << m_roots.numRoots << endl;
	for (size_t i = 0; i < m_roots.numRoots; i++)
	{
		m_output << "Root number " << i + 1 << " = " << m_roots.roots[i] << endl;
	}
}

bool CController::SolveTheEquation(std::istream & args)
{
	try
	{
		double a;
		double b;
		double c;

		if (!(args >> a) || !(args >> b) || !(args >> c))
		{
			throw std::invalid_argument("Invalid count of arguments\nUsage: Solve <coef a> <coef b> <coef c>\n");
		}
		else
		{

			m_roots = Solve(a, b, c);
			PrintSolution();
			return true;
		}
	}
	catch (exception const& e)
	{
		m_output << e.what();
		return false;
	}
}