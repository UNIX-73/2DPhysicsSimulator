#pragma once
#include "physicsState.h"
#include "graphicObject.h"

class PhysicsObject : public PhysicsState {
public:
	using PhysicsState::PhysicsState;
	PhysicsObject(std::shared_ptr<GraphicObject>& gObject, PhysicsState state = PhysicsState()) :
		PhysicsState(state), graphicObject(gObject)
	{

	}

	std::shared_ptr<GraphicObject> graphicObject;

	void UpdateGraphics();
};