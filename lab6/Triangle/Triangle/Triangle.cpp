#include "stdafx.h"
#include "Triangle.h"
#include <iostream>
#include <stdexcept>


bool SumOfTwoSidesEqualToTheThird(double side1, double side2, double side3)
{
	if ((side1 + side2 == side3) && ((side1 + side3 == side2) || (side2 + side3 == side1)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SumOfTwoSidesIsLessThanTheThird(double side1, double side2, double side3)
{
	if ((side1 + side2 < side3) || ((side1 + side3 < side2) || (side2 + side3 < side1)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SideIsNegativeNumber(double side)
{
	return (side < 0) ? true : false;
}

void CheckSides(double side1, double side2, double side3)
{
	if (SideIsNegativeNumber(side1) || SideIsNegativeNumber(side2) || SideIsNegativeNumber(side3))
	{
		throw std::invalid_argument("Argument must not be negative\n");
	}
	if (SumOfTwoSidesIsLessThanTheThird(side1, side2, side3))
	{
		throw std::domain_error("One of the sides of the triangle is larger than the sum of the other two sides\n");
	}
	if (SumOfTwoSidesEqualToTheThird(side1, side2, side3) || SumOfTwoSidesEqualToTheThird(side2, side1, side3) || SumOfTwoSidesEqualToTheThird(side3, side1, side2))
	{
		throw std::domain_error("Only one side in a degenerate triangle can be equal to the sum of the other two sides\n");
	}
}

CTriangle::CTriangle()
{
}

CTriangle::CTriangle(double side1, double side2, double side3)
{
	try
	{
		CheckSides(side1, side2, side3);
		m_side1 = side1;
		m_side2 = side2;
		m_side3 = side3;
		CalculateThePerimeter();
		CalculateTheArea();
	}
	catch (...)
	{
		std::cout << "Unable to construct CTriangle instance\n";
		throw;
	}
}

double CTriangle::GetSide1() const
{
	return m_side1;
}

double CTriangle::GetSide2() const
{
	return m_side2;
}

double CTriangle::GetSide3() const
{
	return m_side3;
}

double CTriangle::GetArea() const
{
	return m_area;
}

double CTriangle::GetPerimeter() const
{
	return m_perimeter;
}

void CTriangle::CalculateThePerimeter()
{
	m_perimeter = m_side1 + m_side2 + m_side3;
}

void CTriangle::CalculateTheArea()
{
	m_area = sqrt(m_perimeter * (m_perimeter - m_side1) * (m_perimeter - m_side2) * (m_perimeter - m_side3));
}



