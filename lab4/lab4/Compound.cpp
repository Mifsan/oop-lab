#include "stdafx.h"
#include "Compound.h"

CCompound::CCompound()
	: CBody("Compound")
{
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> const & element)
{
	if (this == element.get())
	{
		return false;
	}
	else
	{
		m_elements.push_back(element);
		CalculateTheDensity();
	}
	return false;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (auto element : m_elements)
	{
		mass += element->GetMass();
	}
	return mass;
}

double CCompound::GetVolume() const
{
	double volume = 0;
	for (auto element : m_elements)
	{
		volume += element->GetVolume();
	}
	return volume;
}

void CCompound::CalculateTheDensity()
{
	if (GetVolume() == 0)
	{
		m_density = 0;
	}
	else
	{
		m_density = GetMass() / GetVolume();
	}
}

size_t CCompound::NumberOfFigures() const
{
	return m_elements.size();
}



void CCompound::AppendProperties(std::ostream & strm) const
{
	strm << "> Compound body have " << std::to_string(NumberOfFigures()) << " elements:\n";
	for (auto element : m_elements)
	{
		strm << "\t" << element->ToString() << "\n";
	}
}
