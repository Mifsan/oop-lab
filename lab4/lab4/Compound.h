#pragma once
#include "Body.h"
class CCompound final: public CBody
{
public:
	CCompound();

	bool AddChildBody(std::shared_ptr<CBody> const &element);
	double GetVolume() const override;
	double GetMass() const override;
	void CalculateTheDensity();
	size_t NumberOfFigures() const;
protected:
	void AppendProperties(std::ostream& strm) const override;
private:
	std::vector<std::shared_ptr<CBody>> m_elements;
};

