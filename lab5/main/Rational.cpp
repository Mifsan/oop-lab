#include "stdafx.h"
#include "Rational.h"

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 0;
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational operator+(const CRational & lRational, const CRational & rRational)
{
	int resultNumerator = lRational.GetNumerator() * rRational.GetDenominator() + rRational.GetNumerator() * lRational.GetDenominator();
	int resultDenominator = lRational.GetDenominator() * rRational.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

const CRational operator-(const CRational & lRational, const CRational & rRational)
{
	return lRational + CRational(-rRational.GetNumerator(), rRational.GetDenominator());
}

const CRational & CRational::operator+=(const CRational & summand)
{
	if (summand.GetNumerator() == 0)
	{
		return *this;
	}
	m_numerator = m_numerator * summand.GetDenominator() + summand.GetNumerator() * m_denominator;
	m_denominator = m_denominator * summand.GetDenominator();
	Normalize();
	return *this;
}

const CRational & CRational::operator-=(const CRational & sub)
{
	if (sub.GetNumerator() == 0)
	{
		return *this;
	}
	*this += CRational(-sub.GetNumerator(), sub.GetDenominator());
	return *this;
}

const CRational operator*(const CRational & lRational, const CRational & rRational)
{
	int resultNumerator = lRational.GetNumerator() * rRational.GetNumerator();
	int resultDenominator = lRational.GetDenominator() * rRational.GetDenominator();
	return CRational(resultNumerator, resultDenominator);
}

const CRational operator/(const CRational & lRational, const CRational & rRational)
{
	if (rRational.GetDenominator() == 0)
	{
		return lRational;
	}
	else
	{
		return lRational * CRational(rRational.GetDenominator(), rRational.GetNumerator());

	}
}

const CRational & CRational::operator*=(const CRational & multiplier)
{
	m_numerator *= multiplier.GetNumerator();
	m_denominator *= multiplier.GetDenominator();
	Normalize();
	return *this;
}

const CRational & CRational::operator/=(const CRational & divider)
{
	if (divider.GetDenominator() == 0)
	{
		return *this;
	}
	if (divider.GetNumerator() != 0)
	{
		*this *= CRational(divider.GetDenominator(), divider.GetNumerator());
	}
	return *this;
}

const bool operator ==(CRational const & lRational, CRational const & rRational)
{
	return (lRational.GetNumerator() == rRational.GetNumerator() && lRational.GetDenominator() == rRational.GetDenominator());
}

const bool operator !=(CRational const & lRational, CRational const & rRational)
{
	return !(lRational == rRational);
}

const bool operator <(CRational const & lRational, CRational const & rRational)
{
	return (lRational.GetNumerator() * rRational.GetDenominator() < rRational.GetNumerator() * lRational.GetDenominator());
}

const bool operator >(CRational const & lRational, CRational const & rRational)
{
	return (lRational.GetNumerator() * rRational.GetDenominator() > rRational.GetNumerator() * lRational.GetDenominator());
}

const bool operator <=(CRational const & lRational, CRational const & rRational)
{
	return !(lRational > rRational);
}

const bool operator >=(CRational const & lRational, CRational const & rRational)
{
	return !(lRational < rRational);
}

std::ostream & operator << (std::ostream & output, const CRational & rational)
{
	output << rational.GetNumerator() << "/" << rational.GetDenominator();
	return output;
}

std::istream & operator >> (std::istream & input, CRational & rational)
{
	int numerator = 0;
	int denominator = 1;
	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit);
	}
	return input;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	return std::make_pair(m_numerator / m_denominator, CRational(abs(m_numerator % m_denominator), m_denominator));
}
