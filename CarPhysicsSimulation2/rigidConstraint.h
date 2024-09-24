#pragma once
#include "constraint.h"

class RigidConstraint : public Constraint {

public:

	RigidConstraint(Constraint constrainedObj);

	virtual ConstraintResult& SolveConstraint(double step) override;


private:

	V2 delta;
	double deltaAngle;
	double restLength;
};