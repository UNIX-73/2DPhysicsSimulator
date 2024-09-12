#include "physicsObject.h"

void PhysicsObject::UpdateGraphics()
{
	graphicObject->wPos = wPos;
	graphicObject->wRotation = wAngle;
}
