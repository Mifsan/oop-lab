#pragma once
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "Solve.h"

class CController
{
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
public:
	CController(std::istream& input, std::ostream& output);

	bool HandleCommand();
	bool Help();
	void PrintSolution();
private:
	
	bool SolveTheEquation(std::istream& args);

	std::istream& m_input;
	std::ostream& m_output;

	EquationRoots m_roots;
	const ActionMap m_actions;
};