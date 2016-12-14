#pragma once

enum class Direction
{
	BACKWARD = -1,
	NONE = 0,
	FORWARD = 1
};

class CCar
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	int GetGear() const;
	int GetSpeed() const;
	bool GetEngineStatus() const;
	Direction GetDirection() const;
private:
	int m_speed = 0;
	int m_gear = 0;
	Direction m_drivingDirection = Direction::NONE;
	bool m_engineIsTurnedOn = false;
	bool SpeedInGearRange(int speed, int gear);
public:
	bool GearIsAvailableForDirection(int gear, Direction direction);
};
