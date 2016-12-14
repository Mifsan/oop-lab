#include "stdafx.h"
#include "CarController.h"

std::string DirectionToString(Direction direction)
{
	switch (direction)
	{
	case Direction::NONE:
		return "stands still";
	case Direction::FORWARD:
		return "moves forward";
	case Direction::BACKWARD:
		return "moves backward";
	default:
		return "";
	}
}

std::string GearToString(int gear)
{
	switch (gear)
	{
	case -1:
		return "reverse";
	case 0:
		return "neutral";
	case 1:
		return "first";
	case 2:
		return "second";
	case 3:
		return "third";
	case 4:
		return "fourth";
	case 5:
		return "fifth";
	default:
		return "";
	}
}

void PrintHelp(std::ostream &out)
{
	out << "info: Displays information about the condition of the engine, current driving direction, current speed, current gear.\n"
		<< "engineon: Turn on engine.\n"
		<< "engineoff: Turn off engine.\n"
		<< "setgear <gear>: Set current gear. If unable to set gear shows the reason.\n"
		<< "setspeed <speed>: Set current speed. If unable to set speed shows the reason.\n"
		<< "exit: Exit the program.\n";
}

CCarController::CCarController(CCar & car, std::istream &in, std::ostream &out)
	: m_car(car)
	, m_in(in)
	, m_out(out)
{
}

bool CCarController::GetCommand(std::vector<std::string> & command)
{
	m_out << "> ";
	std::string commandLine;
	if (m_exit || !getline(m_in, commandLine))
	{
		return false;
	}
	std::string lowerCasedCommandLine;
	lowerCasedCommandLine.resize(commandLine.length());
	std::transform(commandLine.begin(), commandLine.end(), lowerCasedCommandLine.begin(), ::towlower);
	boost::split(command, lowerCasedCommandLine, boost::is_any_of(" "));
	return true;
}

bool CCarController::HandleCommand(std::vector<std::string> const& commands)
{
	if (commands.empty())
	{
		return false;
	}
	if (REQUIRED_COMMAND_ARG_COUNT.find(commands[0]) == REQUIRED_COMMAND_ARG_COUNT.end())
	{
		m_out << "Unknown command: \"" << commands[0] << "\"\n";
		return false;
	}
	if (REQUIRED_COMMAND_ARG_COUNT.at(commands[0]) != commands.size() - 1)
	{
		m_out << "The command \"" << commands[0] << "\" requires " << REQUIRED_COMMAND_ARG_COUNT.at(commands[0]) << " argument(s) \n"
			<< "For information about the commands write \"help\"\n";
		return false;
	}
	if (commands[0] == "info")
	{
		m_out << "Engine " << (m_car.GetEngineStatus() ? "is turned on" : "is turned off") << "\n"
			<< "The car " << DirectionToString(m_car.GetDirection()) << "\n"
			<< "Current speed: " << m_car.GetSpeed() << "\n"
			<< "Current gear: " << GearToString(m_car.GetGear()) << "\n";
	}
	else if (commands[0] == "engineon")
	{
		m_car.TurnOnEngine();
	}
	else if (commands[0] == "engineoff")
	{
		m_car.TurnOffEngine();
	}
	else if (commands[0] == "setgear")
	{
		if (!m_car.SetGear(atoi(commands[1].c_str())))
		{
			m_out << "Unable to change gear\n";
			return false;
		}
	}
	else if (commands[0] == "setspeed")
	{
		if (!m_car.SetSpeed(atoi(commands[1].c_str())))
		{
			if (!m_car.GetEngineStatus())
			{
				m_out << "To change the speed you need to turn on the engine\n";
				return false;
			}
			else
			{
				m_out << "This speed is outside the range of gear\n";
				return false;
			}
		}
	}
	else if (commands[0] == "help")
	{
		PrintHelp(m_out);
	}
	else if (commands[0] == "exit")
	{
		m_exit = true;
	}
	return true;
}