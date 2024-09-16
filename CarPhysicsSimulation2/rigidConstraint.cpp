#include "rigidConstraint.h"

void RigidConstraint::SolveConstraint(double step)
{

	V2 delta = objB->wPos - objA->wPos;

	if (delta == V2::ZeroVector) return;

	double currentDistance = delta.size();

	double C = currentDistance - restLength;

	//Jacobiano
	V2 j1 = delta.safeNormal();
	V2 j2 = -j1;

	V2 rVel = objB->wVel - objA->wVel;

	double lambda = -(rVel.dot(j1) + C * (1.0 / step)) / (objA->invMass + objB->invMass);

	//Damping
	V2 dampingForce;

	if (damping != 0.0)
	{
		dampingForce = damping * lambda * j1;
	}

	objA->AddForce(-j1 * lambda - dampingForce);
	objB->AddForce(-j2 * lambda + dampingForce);
}
