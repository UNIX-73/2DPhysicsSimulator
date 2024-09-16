#pragma once
#include "physicsState.h"

class Constraint
{
public:
	Constraint(std::shared_ptr<PhysicsState> objA, std::shared_ptr<PhysicsState> objB) :
		objA(objA), objB(objB) {};

	virtual ~Constraint() = default;

	virtual void SolveConstraint(double step);

	bool rk4Constraint = false;

protected:
	std::shared_ptr<PhysicsState> objA;
	std::shared_ptr<PhysicsState> objB; 
};