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
	void CalculateThePerimeter();
	void CalculateTheArea();

	double m_side1;
	double m_side2;
	double m_side3;
	double m_area;
	double m_perimeter;

};
