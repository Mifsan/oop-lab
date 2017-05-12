#pragma once

class CTriangle
{
public:
	CTriangle(double side1, double side2, double side3);
	double GetSide1()const;
	double GetSide2()const;
	double GetSide3()const;
	double GetArea()const;
	double GetPerimeter()const;
private:
	double m_side1, m_side2, m_side3, m_area, m_perimeter;
	void CalculateThePerimeter();
	void CalculateTheArea();
};
