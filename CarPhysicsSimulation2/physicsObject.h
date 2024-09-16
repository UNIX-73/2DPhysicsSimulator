#pragma once
#include "physicsState.h"
#include "graphicObject.h"

class PhysicsObject : public PhysicsState {
public:
	using PhysicsState::PhysicsState;
	PhysicsObject(std::shared_ptr<GraphicObject> gObject, PhysicsState state = PhysicsState(), bool autoInertia = false);

	std::shared_ptr<GraphicObject> graphicObject;

	virtual void UpdateGraphics() override;

	void AutoInertia();
};