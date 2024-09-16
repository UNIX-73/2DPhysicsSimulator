#include "physicsObject.h"

PhysicsObject::PhysicsObject(std::shared_ptr<GraphicObject> gObject, PhysicsState state, bool autoInertia) :
	PhysicsState(state), graphicObject(gObject)
{
	if (autoInertia)
	{
		double width = graphicObject->rectangleShapes.front().getSize().x;
		double height = graphicObject->rectangleShapes.front().getSize().y;

		UpdateInertia((1.0 / 12.0) * mass * (width * width + height * height));
	}
}

void PhysicsObject::UpdateGraphics()
{
	graphicObject->wPos = wPos;
	graphicObject->wRotation = wAngle;
}

void PhysicsObject::AutoInertia()
{
	double width = graphicObject->rectangleShapes.front().getSize().x;
	double height = graphicObject->rectangleShapes.front().getSize().y;

	UpdateInertia((1.0 / 12.0) * mass * (width * width + height * height));
}
