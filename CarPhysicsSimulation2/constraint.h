#pragma once
#include "physicsState.h"

class Constraint
{
public:
	Constraint(std::shared_ptr<PhysicsState> objA, std::shared_ptr<PhysicsState> objB) :
		objA(objA), objB(objB) {};

	~Constraint() {};

	virtual void SolveConstraint();

protected:
	std::shared_ptr<PhysicsState> objA;
	std::shared_ptr<PhysicsState> objB;
};