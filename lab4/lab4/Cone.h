#pragma 
#include "Body.h"

class CCone final: public CBody
{
public:
	CCone(double density, double radius, double height);

	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
protected:
	void AppendProperties(std::ostream& strm) const override;
private:
	double m_radius;
	double m_height;
};