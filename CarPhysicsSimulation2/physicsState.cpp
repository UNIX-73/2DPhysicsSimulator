#include "physicsState.h"

void PhysicsState::AddForce(V2 force, V2 point)
{
	currentForce += force;
}

void PhysicsState::AddTorque(double torque)
{
	currentTorque += torque;
}

void PhysicsState::UpdateGraphics()
{
	//No hace nada en physicsState, pero se utiliza en physicsObject, se crea aqui para no tener que verificar si es un child o no
}
