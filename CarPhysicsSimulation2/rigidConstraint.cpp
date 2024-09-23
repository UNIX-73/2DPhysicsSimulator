#include "rigidConstraint.h"

ConstraintResult& RigidConstraint::SolveConstraint(double step)
{
    ConstraintResult result;

    // Posiciones y ángulos actuales de objA y objB
    V2 posA = objA->wPos;
    V2 posB = objB->wPos;
    double angleA = objA->wAngle;
    double angleB = objB->wAngle;

    // Diferencias de posición y ángulo
    V2 deltaPos = posB - posA;
    double deltaAngle = angleB - angleA;

    // Velocidades lineales y angulares
    V2 velA = objA->wVel;
    V2 velB = objB->wVel;
    double angularVelA = objA->wAngularVel;
    double angularVelB = objB->wAngularVel;

    // Jacobiana (J): Restringimos las diferencias de movimiento lineal y angular
    result.JxA = -1.0; // A debería moverse en la dirección opuesta de B
    result.JxB = 1.0;
    result.JyA = -1.0;
    result.JyB = 1.0;
    result.JØA = -1.0;
    result.JØB = 1.0;

    // Fuerzas de reacción (Q): Estas fuerzas intentan reducir el error (delta)
    result.QxA = deltaPos.x / step; // Dividir el error por el paso de tiempo
    result.QxB = -deltaPos.x / step;
    result.QyA = deltaPos.y / step;
    result.QyB = -deltaPos.y / step;
    result.QØA = deltaAngle / step;
    result.QØB = -deltaAngle / step;

    // Indicamos que hay restricciones en los 3 grados de libertad (x, y, Ø)
    result.constraintsX = true;
    result.constraintsY = true;
    result.constraintsØ = true;

    return result;
}

