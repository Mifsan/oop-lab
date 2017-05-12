#pragma once
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "Solve.h"
#include <functional>
#include <string>
#include <sstream>

class CController
{
public:
	CController(std::istream& input, std::ostream& output);

	bool HandleCommand();
	bool Help();
	void PrintSolution();
private:
	
	bool SolveTheEquation(std::istream& args);

	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;

	EquationRoots m_roots;
	const ActionMap m_actions;
};