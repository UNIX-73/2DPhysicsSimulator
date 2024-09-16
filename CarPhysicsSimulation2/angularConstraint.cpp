#include "angularConstraint.h"
#include <string>

// Constructor
AngularConstraint::AngularConstraint(Constraint constraintObj, double stiffness, double damping, double AAngle, double BAngle) :
    Constraint(constraintObj), stiffness(stiffness), damping(damping), AAngle(AAngle), BAngle(BAngle)
{
    V2 delta = objB->wPos - objA->wPos;
    V2 relativeOrientation = delta.safeNormal();
    double initialOrientation = relativeOrientation.degAngle();

    relAngleA = NormalizeAngle(objA->wAngle - initialOrientation + AAngle);
    relAngleB = NormalizeAngle(objB->wAngle - initialOrientation + BAngle);
}

// SolveConstraint
void AngularConstraint::SolveConstraint(double step)
{
    V2 delta = objB->wPos - objA->wPos;
    V2 relativeOrientation = delta.safeNormal();
    double orientation = relativeOrientation.degAngle();

    // Calcular ángulos relativos
    double currentRelAngleA = NormalizeAngle(objA->wAngle - orientation + AAngle);
    double currentRelAngleB = NormalizeAngle(objB->wAngle - orientation + BAngle);

    // Calcular el error angular normalizado
    double errorA = NormalizeAngle(currentRelAngleA - relAngleA);
    double errorB = NormalizeAngle(currentRelAngleB - relAngleA);

    // Aplicar fuerzas de resorte y amortiguación
    double torqueA = -errorA * stiffness;
    double torqueB = -errorB * stiffness;

    double dampingA = objA->wAngularVel * -damping;
    double dampingB = objB->wAngularVel * -damping;

    objA->AddTorque(torqueA + dampingA);
    objB->AddTorque(torqueB + dampingB);
}
