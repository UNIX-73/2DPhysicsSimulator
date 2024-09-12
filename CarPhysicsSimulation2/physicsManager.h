#pragma once
#include "physicsObject.h"
#include <vector>
#include <memory>

class PhysicsManager
{
public:
	PhysicsManager();

	void AddPhysicsState(std::shared_ptr<PhysicsState>& pState);
	void AddPhysicsObject(std::shared_ptr<PhysicsObject>& pObj);

	void RemovePhysicsState(std::shared_ptr<PhysicsState>& pState);
	void RemovePhysicsObject(std::shared_ptr<PhysicsObject>& pObj);

	std::vector<std::shared_ptr<PhysicsState>> physicsStates;
	//std::vector<std::shared_ptr<PhysicsConstraint>> physicsConstraints;

	void Update(double step);
	void UpdatePhysics(double step);
	void IntegrateRk4(double step, std::shared_ptr<PhysicsState>& state);
	void UpdatePhysicsObjectGraphics();
};