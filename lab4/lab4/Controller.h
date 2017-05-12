#pragma once
#include "stdafx.h"

#include "Body.h"

#include "Sphere.h"
#include "Parallelepiped.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Compound.h"	

class CController
{
public:	
	CController(std::vector<std::shared_ptr<CBody>>& bodies, std::istream& input, std::ostream& output);

	bool HandleCommand();
	bool Help();
	void PrintAllBodies(std::vector<std::shared_ptr<CBody>> const& bodies);
	void FindBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> const& bodies);
	void FindBodyWithSmallestWeight(std::vector<std::shared_ptr<CBody>> const& bodies);
private:
	bool CreateSphere(std::istream& args);
	bool CreateParallelepiped(std::istream& args);
	bool CreateCone(std::istream& args);
	bool CreateCylinder(std::istream& args);
	bool CreateCompoundBody();

	typedef std::map<std::string, std::function<bool(std::istream& args)>> ActionMap;

	std::vector<std::shared_ptr<CBody>>& m_bodies;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actions;
};