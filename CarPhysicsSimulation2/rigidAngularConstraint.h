#pragma once
#include "constraint.h"


class RigidAngularConstraint : public Constraint
{
public:
	RigidAngularConstraint(const Constraint constraintObj, double damping = 0.0, double angleA = 0.0, double angleB = 0.0);

	virtual void SolveConstraint(double step) override;

protected:
	double damping;

	double angleA;
	double angleB;

	double relAngleA;
	double relAngleB;
};