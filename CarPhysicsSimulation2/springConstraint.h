#pragma once
#include "constraint.h"

class SpringConstraint : public Constraint {
public:
	SpringConstraint(const Constraint constraintObj, double restLength, double stiffness, double damping, V2 anchorPointA = V2::ZeroVector, V2 anchorPointB = V2::ZeroVector) :
		Constraint(constraintObj), restLength(restLength), stiffness(stiffness), damping(damping), anchorPointA(anchorPointA), anchorPointB(anchorPointB) {};

	virtual void SolveConstraint(double step) override;

protected:
	double restLength;
	double stiffness;
	double damping;

	V2 anchorPointA;
	V2 anchorPointB;
};
