#pragma once
#include "physicsState.h"

struct ConstraintResult {
	bool constraintsX = false;
	bool constraintsY = false;
	bool constraints� = false;

	//	Jacobian
	double JxA = 0.0;
	double JyA = 0.0;
	double J�A = 0.0;
	double JxB = 0.0;
	double JyB = 0.0;
	double J�B = 0.0;
	
	//	External forces
	double QxA = 0.0;
	double QyA = 0.0;
	double Q�A = 0.0;
	double QxB = 0.0;
	double QyB = 0.0;
	double Q�B = 0.0;
};

class Constraint
{
public:
	Constraint(std::shared_ptr<PhysicsState> objA, std::shared_ptr<PhysicsState> objB) :
		objA(objA), objB(objB) {};

	virtual ~Constraint() = default;

	virtual ConstraintResult& SolveConstraint(double step);

	bool rk4Constraint = false;

	std::shared_ptr<PhysicsState>& GetObjA();
	std::shared_ptr<PhysicsState>& GetObjB();

protected:
	std::shared_ptr<PhysicsState> objA;
	std::shared_ptr<PhysicsState> objB; 
};