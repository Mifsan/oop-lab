#include "stdafx.h"
#include "..\Car\Car.h"

struct CarFixture
{
	CCar car;
};

void CheckCarGearForSpeedRange(CCar &car, int gear, int minSpeed, int maxSpeed)
{
	car.SetGear(gear);
	BOOST_CHECK(car.SetSpeed(minSpeed) && car.GetSpeed() == minSpeed);
	BOOST_CHECK(car.SetSpeed(maxSpeed) && car.GetSpeed() == maxSpeed);
	int speedBeforeSetSpeed = car.GetSpeed();
	BOOST_CHECK(!car.SetSpeed(minSpeed - 1) && car.GetSpeed() == speedBeforeSetSpeed);
	BOOST_CHECK(!car.SetSpeed(maxSpeed + 1) && car.GetSpeed() == speedBeforeSetSpeed);
}

// ����� CCar
BOOST_FIXTURE_TEST_SUITE(CCar_class, CarFixture)

// ��������� ���������� ��-��������� ��������
BOOST_AUTO_TEST_CASE(engine_is_turned_off_by_default)
{
	BOOST_CHECK(!car.GetEngineStatus());
}

// ���������� ��-��������� ����� �� ����������� ��������
BOOST_AUTO_TEST_CASE(gear_is_neutral_by_default)
{
	BOOST_CHECK(car.GetGear() == 0);
}

// ���������� ��-��������� �� ����� ��������
BOOST_AUTO_TEST_CASE(speed_is_zero_by_default)
{
	BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
}

// ���������� ��-��������� ����� �� �����
BOOST_AUTO_TEST_CASE(direction_is_none_by_default)
{
	BOOST_CHECK(car.GetDirection() == Direction::NONE);
}

// ����������� ��������� ����� ���� �������
BOOST_AUTO_TEST_CASE(turned_off_engine_can_be_turned_on)
{
	BOOST_CHECK(car.TurnOnEngine() && car.GetEngineStatus());
}

// ���������� ��������� ���������� �� ����� ����� ����������
BOOST_AUTO_TEST_CASE(turned_on_engine_cannot_be_turned_on)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.GetEngineStatus() && !car.TurnOnEngine());
}

// ����������� ��������� ���������� �� ����� ����� �����������
BOOST_AUTO_TEST_CASE(turned_off_engine_cannot_be_turned_off)
{
	BOOST_CHECK(!car.TurnOffEngine());
}

// ����������� ��������� ���������� ����� ����������� �������� ������ �� �����������
BOOST_AUTO_TEST_CASE(can_set_gear_only_to_neutral_if_engine_is_turned_off)
{
	BOOST_CHECK(car.SetGear(0) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(-1) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(1) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(2) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(3) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(4) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
	BOOST_CHECK(!car.SetGear(5) && car.GetGear() == 0 && car.GetDirection() == Direction::NONE);
}

// ���������� ��������� ���������� � ��������� ����� ����� ����������� �������� �� ��������� ��� ������ ��������
BOOST_AUTO_TEST_CASE(can_set_gear_to_reverse_or_first_if_engine_is_turned_on)
{
	car.TurnOnEngine();
	BOOST_CHECK(car.SetGear(-1) && car.GetGear() == -1);
	BOOST_CHECK(car.SetGear(1) && car.GetGear() == 1);
}

// ���������� ��������� ���������� ����� �������� �������� ������ ���� �������� � �������� ��������� ����� ��������.
BOOST_AUTO_TEST_CASE(can_set_gear_if_engine_is_turned_on_and_speed_within_range)
{
	car.TurnOnEngine();
	BOOST_CHECK(!car.SetGear(2) && car.GetGear() == 0);
}

// ����������� ��������� ���������� �� ����� �������� ��������
BOOST_AUTO_TEST_CASE(cannot_set_speed_if_engine_is_turned_off)
{
	BOOST_CHECK(!car.GetEngineStatus() && !car.SetSpeed(1) && car.GetSpeed() == 0 && car.GetDirection() == Direction::NONE);
}

// ���������� ���������� ����� �������� �������� ������ � �������� ��������� � ��������.
// ����������: �� ����������� �������� �������� �������� ����� ������ � 0
BOOST_AUTO_TEST_CASE(can_set_speed_within_range_if_engine_is_turned_on)
{
	car.TurnOnEngine();
	CheckCarGearForSpeedRange(car, -1, 0, 20);
	CheckCarGearForSpeedRange(car, 0, 0, 0);
	CheckCarGearForSpeedRange(car, 1, 0, 30);
	CheckCarGearForSpeedRange(car, 2, 20, 50);
	CheckCarGearForSpeedRange(car, 3, 30, 60);
	CheckCarGearForSpeedRange(car, 4, 40, 90);
	CheckCarGearForSpeedRange(car, 5, 50, 150);
}

// ���������� ��������� ���������� ����� ��������� ������ � ��������� ����� � ���� ������� �������� - �����������
BOOST_AUTO_TEST_CASE(turned_on_engine_can_be_turned_off_if_speed_is_zero)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	BOOST_CHECK(!car.TurnOffEngine());
	car.SetGear(0);
	car.SetSpeed(0);
	BOOST_CHECK(car.GetSpeed() == 0 && car.TurnOffEngine());
}

BOOST_AUTO_TEST_SUITE_END()