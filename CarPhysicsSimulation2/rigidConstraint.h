#pragma once
#include "constraint.h"

class RigidConstraint : public Constraint {

public:

	RigidConstraint(Constraint constrainedObj) :
		Constraint(constrainedObj) {};

	virtual ConstraintResult& SolveConstraint(double step) override;



};