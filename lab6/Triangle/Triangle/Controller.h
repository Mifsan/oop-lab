#pragma once
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "Triangle.h"
#include <functional>
#include <string>
#include <sstream>

class CController
{
public:
	CController(std::istream& input, std::ostream& output);

	bool HandleCommand();
	bool Help();
	void PrintTriangleInfo();
private:
	bool CreateTriangle(std::istream& args);

	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	std::istream& m_input;
	std::ostream& m_output;

	std::vector<CTriangle> m_triangle;
	const ActionMap m_actions;
};