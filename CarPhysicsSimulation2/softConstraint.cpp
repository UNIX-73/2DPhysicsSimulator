#include "softConstraint.h"

void SoftConstraint::SolveConstraint(double step)
{
	springConstraint.SolveConstraint(step);
	angularConstraint.SolveConstraint(step);
};

