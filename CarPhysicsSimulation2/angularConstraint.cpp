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

    std::cout << "RelAngleA: " << std::to_string(relAngleA) << std::endl;
    std::cout << "RelAngleB: " << std::to_string(relAngleB) << std::endl;
}

// SolveConstraint
void AngularConstraint::SolveConstraint(double step)
{
    V2 delta = objB->wPos - objA->wPos;
    V2 relativeOrientation = delta.safeNormal();
    double orientation = relativeOrientation.degAngle();

    
    objA->wAngle = orientation;
    objB->wAngle = orientation;
    
}
