#pragma once
#include "constraint.h"

class RigidConstraint : public Constraint
{
public:
	RigidConstraint(const Constraint constraintObj, double restLength, double damping = 0.0, V2 anchorPointA = V2::ZeroVector, V2 anchorPointB = V2::ZeroVector) :
		Constraint(constraintObj), restLength(restLength), damping(damping), anchorPointA(anchorPointA), anchorPointB(anchorPointB) {};

	virtual void SolveConstraint(double step) override;


private:
	double restLength;
	double damping;
	
	V2 anchorPointA;
	V2 anchorPointB;
};