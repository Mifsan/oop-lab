#pragma once
class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator()const;
	int GetDenominator() const;
	double ToDouble() const;
	const CRational operator+() const;
	const CRational operator-() const;
	const CRational & operator+=(const CRational & summand);
	const CRational & operator-=(const CRational & sub);
	const CRational & operator*=(const CRational & multiplier);
	const CRational & operator/=(const CRational & divider);
	std::pair<int, CRational> ToCompoundFraction()const;
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);
const CRational operator+(const CRational & lRational, const CRational & rRational);
const CRational operator-(const CRational & lRational, const CRational & rRational);
const CRational operator*(const CRational & lRational, const CRational & rRational);
const CRational operator/(const CRational & lRational, const CRational & rRational);
const bool operator ==(CRational const & lRational, CRational const & rRational);
const bool operator !=(CRational const & lRational, CRational const & rRational);
const bool operator <(CRational const & lRational, CRational const & rRational);
const bool operator >(CRational const & lRational, CRational const & rRational);
const bool operator <=(CRational const & lRational, CRational const & rRational);
const bool operator >=(CRational const & lRational, CRational const & rRational);
std::istream & operator >> (std::istream & input, CRational & rational);
std::ostream & operator << (std::ostream & output, const CRational & rational);