#include "stdafx.h"
#include "Car.h"

const std::map<int, std::pair<Direction, std::pair<int, int>>> GEARS =
{
	{ -1,{ Direction::BACKWARD,{ 0, 20 } } },
	{ 0,{ Direction::NONE,{ 0, 150 } } },
	{ 1,{ Direction::FORWARD,{ 0, 30 } } },
	{ 2,{ Direction::FORWARD,{ 20, 50 } } },
	{ 3,{ Direction::FORWARD,{ 30, 60 } } },
	{ 4,{ Direction::FORWARD,{ 40, 90 } } },
	{ 5,{ Direction::FORWARD,{ 50, 150 } } }
};


bool CCar::TurnOnEngine()
{
	if (!m_engineIsTurnedOn && m_gear == 0)
	{
		m_engineIsTurnedOn = true;
		return true;
	}
	return false;
}


bool CCar::TurnOffEngine()
{
	if (m_engineIsTurnedOn && m_gear == 0 && m_drivingDirection == Direction::NONE)
	{
		m_engineIsTurnedOn = false;
		return true;
	}
	return false;
}


bool CCar::SetGear(int gear)
{
	if ((m_engineIsTurnedOn && GearIsAvailableForDirection(gear, m_drivingDirection) && SpeedInGearRange(m_speed, gear)) || (!m_engineIsTurnedOn && gear == 0))
	{
		m_gear = gear;
		return true;
	}

	return false;
}


bool CCar::SetSpeed(int speed)
{
	if (SpeedInGearRange(speed, m_gear))
	{
		if (speed == 0) {
			m_drivingDirection = Direction::NONE;
		}
		else if (speed > 0 && m_gear == -1)
		{
			m_drivingDirection = Direction::BACKWARD;
		}
		else if (speed > 0 && m_gear >= 1 && m_gear <= 5)
		{
			m_drivingDirection = Direction::FORWARD;
		}
			m_speed = speed;
			return true;
	}
	return false;
}


int CCar::GetGear() const
{
	return m_gear;
}


int CCar::GetSpeed() const
{
	return m_speed;
}


bool CCar::GetEngineStatus() const
{
	return m_engineIsTurnedOn;
}


Direction CCar::GetDirection() const
{
	return m_drivingDirection;
}


bool CCar::SpeedInGearRange(int speed, int gear)
{
	return ((speed >= GEARS.at(gear).second.first && speed <= GEARS.at(gear).second.second) && !(gear == 0 && speed > m_speed));
}


bool CCar::GearIsAvailableForDirection(int gear, Direction direction)
{
	return (gear == 0)
		|| (gear == -1 && direction != Direction::FORWARD)
		|| (gear >= 1 && gear <= 5 && direction != Direction::BACKWARD);
}
