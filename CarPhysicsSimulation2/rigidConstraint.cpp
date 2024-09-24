#include "rigidConstraint.h"

RigidConstraint::RigidConstraint(Constraint constrainedObj) :
    Constraint(constrainedObj) 
{
    delta = objB->wPos - objA->wPos;
    deltaAngle = delta.degAngle();
    restLength = delta.size();
}

ConstraintResult& RigidConstraint::SolveConstraint(double step)
{
    // Calcular la posición actual delta y la distancia
    V2 deltaPos = objB->wPos - objA->wPos;

    // Si la diferencia de posición es cero, no hay constraints que resolver
    if (deltaPos == V2::ZeroVector)
    {
        ConstraintResult result;
        result.constraintsX = true;
        result.constraintsY = true;
        result.constraintsØ = false;

        result.JxA = 0.0;
        result.JyA = 0.0;
        result.JxB = 0.0;
        result.JyB = 0.0;

        result.QxA = 0.0;
        result.QyA = 0.0;
        result.QxB = 0.0;
        result.QyB = 0.0;

        return result;
    }

    // Calcular la distancia actual entre los objetos
    double currentDistance = deltaPos.size();

    // Normalizar deltaPos para obtener el Jacobiano (dirección del constraint)
    V2 j = deltaPos.safeNormal();

    // Velocidad relativa entre los objetos
    V2 rVel = objB->wVel - objA->wVel;

    // Error del constraint: la diferencia entre la distancia actual y la distancia de descanso
    double C = currentDistance - restLength;

    // Resolver lambda (multiplicador de Lagrange)
    double denominator = (objA->invMass + objB->invMass);
    if (denominator == 0) {
        std::cout << "Error: denominador es cero al calcular lambda." << std::endl;
        ConstraintResult result;
        result.constraintsX = true;
        result.constraintsY = true;
        result.constraintsØ = false;

        result.JxA = 0.0;
        result.JyA = 0.0;
        result.JxB = 0.0;
        result.JyB = 0.0;

        result.QxA = 0.0;
        result.QyA = 0.0;
        result.QxB = 0.0;
        result.QyB = 0.0;

        return result;
    }

    double lambda = -(rVel.dot(j) + C * (1.0 / step)) / denominator;

    // Crear el resultado con los valores correctos
    ConstraintResult result;

    result.JxA = -j.x;
    result.JyA = -j.y;
    result.JxB = j.x;
    result.JyB = j.y;

    // Aplicar las fuerzas calculadas en función de lambda y el Jacobiano
    result.QxA = lambda * j.x;
    result.QyA = lambda * j.y;
    result.QxB = lambda * j.x;
    result.QyB = lambda * j.y;

    result.constraintsX = true;
    result.constraintsY = true;
    result.constraintsØ = false; // No estás resolviendo ángulo por ahora

    return result;
}
