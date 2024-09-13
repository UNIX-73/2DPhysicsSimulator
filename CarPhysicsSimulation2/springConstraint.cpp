#include "springConstraint.h"

void SpringConstraint::SolveConstraint(double step)
{
    // Posiciones de los puntos de anclaje en el sistema de coordenadas global
    V2 posA = objA->wPos + anchorPointA.rotateVector(objA->wAngle);
    V2 posB = objB->wPos + anchorPointB.rotateVector(objB->wAngle);

    V2 delta = posB - posA;
    double distance = delta.size();

    if (distance == 0.0) return;

    // Fuerza de resorte
    double forceMagnitude = -stiffness * (distance - restLength);

    // Velocidad relativa en la dirección de la distancia del resorte
    V2 relativeVelocity = objB->wVel - objA->wVel;
    double dampingForce = -damping * (relativeVelocity.dot(delta) / distance);

    // Fuerza total aplicada
    double totalForce = forceMagnitude + dampingForce;

    // Dirección de la fuerza
    V2 force = (delta / distance) * totalForce;

    // Aplica la fuerza a ambos objetos en direcciones opuestas
    objA->AddForce(-force);
    objB->AddForce(force);
}
