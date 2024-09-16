#pragma once

struct CustomForce
{
	bool applyCustomForce = true;
};

struct GroundFriction : public CustomForce
{
	bool useCustomMass = false;
	double customMass = 1.0;

	double staticFrictionCoefficient = 1.0;
	double dynamicFrictionCoefficient = 0.8;
};

struct AirFriction : public CustomForce
{
	double dragCoefficient = 0.1;
};






