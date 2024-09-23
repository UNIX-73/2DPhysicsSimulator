#include "physicsState.h"

void PhysicsState::AddForce(V2 force, V2 point)
{
	if (point == V2::ZeroVector) currentForce += force;
	else
	{
		V2 globalPoint = point.rotateVector(wAngle); // Rotar el punto en función del ángulo actual del objeto

		// Sumar la fuerza a la fuerza total
		currentForce += force;

		// Calcular el torque: T = r x F, donde r es la posición relativa y F la fuerza
		// El torque es un escalar en 2D, así que usamos el producto cruzado 2D (r.x * F.y - r.y * F.x)
		float torque = globalPoint.x * force.y - globalPoint.y * force.x;

		// Sumar el torque a la rotación angular
		currentTorque += torque;
	}

}

void PhysicsState::AddTorque(double torque)
{
	currentTorque += torque;
}

void PhysicsState::UpdateMass(double mass)
{
	this->mass = mass;
	invMass = 1.0 / this->mass;
}

void PhysicsState::UpdateInertia(double inertia)
{
	this->inertia = inertia;
	invInertia = 1.0 / this->inertia;
}

void PhysicsState::SolveCustomForces(double step)
{
	//No hace nada en physicsState, pero se utiliza en physicsObject, se crea aqui para no tener que verificar si es un child o no
}

void PhysicsState::UpdateGraphics()
{
	//No hace nada en physicsState, pero se utiliza en physicsObject, se crea aqui para no tener que verificar si es un child o no
}
