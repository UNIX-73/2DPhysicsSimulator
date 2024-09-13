#pragma once
#include "constraint.h"

class AngularConstraint : public Constraint
{
public:
	AngularConstraint(Constraint constraintObj, double stiffness, double damping, double AAngle = 0.0, double BAngle = 0.0);

	virtual void SolveConstraint(double step) override;
private:
	double stiffness;
	double damping;

	double AAngle;
	double BAngle;

	V2 relativeOrientation;
	double relAngleA;
	double relAngleB;
};

