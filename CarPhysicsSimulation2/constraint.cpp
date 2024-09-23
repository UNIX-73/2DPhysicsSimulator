#include "constraint.h"

ConstraintResult& Constraint::SolveConstraint(double step)
{
	ConstraintResult none = ConstraintResult();
	return none;
	//Child solveConstraint
}

std::shared_ptr<PhysicsState>& Constraint::GetObjA()
{
	return objA;
}

std::shared_ptr<PhysicsState>& Constraint::GetObjB()
{
	return objB;
}
