#pragma once

#include "Car.h"

class CCarController
{
public:
	CCarController() = default;
	CCarController(CCar & car, std::istream &in, std::ostream &out);
	~CCarController() = default;
	bool GetCommand(std::vector<std::string> & command);
	bool HandleCommand(std::vector<std::string> const& command);
private:
	CCar &m_car;
	std::istream &m_in;
	std::ostream &m_out;
	bool m_exit = false;

	const std::map<std::string, size_t> REQUIRED_COMMAND_ARG_COUNT =
	{
		{ "help", 0 },
		{ "exit", 0 },
		{ "info", 0 },
		{ "engineon", 0 },
		{ "engineoff", 0 },
		{ "setgear", 1 },
		{ "setspeed", 1 }
	};
};
