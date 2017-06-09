#pragma once
#include "Body.h"
#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Compound.h"	

class CController
{
	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;
public:	
	CController(std::istream& input, std::ostream& output);

	bool HandleCommand();
	bool Help() const;
	void PrintAllBodies() const;
	void FindBodyWithMaxMass() const;
	void FindBodyWithSmallestWeight() const;
	std::vector<std::shared_ptr<CBody>> GetVectorOfBodies() const;
private:
	bool CreateSphere(std::istream& args);
	bool CreateParallelepiped(std::istream& args);
	bool CreateCone(std::istream& args);
	bool CreateCylinder(std::istream& args);
	bool CreateCompoundBody();

	std::vector<std::shared_ptr<CBody>> m_bodies;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actions;
};