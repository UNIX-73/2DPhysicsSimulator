#pragma once
#include "physicsObject.h"

class PhysicsTyre : public PhysicsObject
{
public:
	PhysicsTyre(PhysicsObject physicsObject, double supportedMass = 1.0, double tractionCoefficient = 1.0, double lateralFrictionCoefficient = 1.0, double rollingResistanceCoefficient = 0.01) :
		PhysicsObject(physicsObject), supportedMass(supportedMass), lateralFrictionCoefficient(lateralFrictionCoefficient), tractionCoefficient(tractionCoefficient), rollingResistanceCoefficient(rollingResistanceCoefficient) {};
	

	virtual void SolveCustomForces(double step) override;


	double supportedMass;
	double tractionCoefficient;
	double lateralFrictionCoefficient;
	double rollingResistanceCoefficient;
};