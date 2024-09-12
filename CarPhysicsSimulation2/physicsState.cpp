#include "physicsState.h"

void PhysicsState::AddForce(V2 force, V2 point)
{
	currentForce += force;
}

void PhysicsState::AddTorque(double torque)
{
	currentTorque += torque;
}
