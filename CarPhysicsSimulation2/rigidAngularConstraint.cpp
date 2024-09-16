#include "rigidAngularConstraint.h"

RigidAngularConstraint::RigidAngularConstraint(const Constraint constraintObj, double damping, double angleA, double angleB) :
	Constraint(constraintObj), damping(damping), angleA(angleA), angleB(angleB) 
{
	V2 delta = objB->wPos - objA->wPos;
	V2 relativeOrientation = delta.safeNormal();
	double initialOrientation = relativeOrientation.degAngle();

	relAngleA = NormalizeAngle(objA->wAngle - initialOrientation + angleA);
	relAngleB = NormalizeAngle(objB->wAngle - initialOrientation + angleB);
}


void RigidAngularConstraint::SolveConstraint(double step)
{
    // Calcular la dirección entre los dos objetos
    V2 delta = objB->wPos - objA->wPos;
    V2 relativeOrientation = delta.safeNormal();
    double orientation = relativeOrientation.degAngle();

    // Calcular ángulos relativos actuales
    double currentRelAngleA = NormalizeAngle(objA->wAngle - orientation + angleA);
    double currentRelAngleB = NormalizeAngle(objB->wAngle - orientation + angleB);

    // Calcular el error angular normalizado para ambos objetos
    double errorA = NormalizeAngle(currentRelAngleA - relAngleA);
    double errorB = NormalizeAngle(currentRelAngleB - relAngleB);

    // Error combinado del constraint angular
    double C = errorA + errorB;

    // Multiplicador de Lagrange para resolver el constraint angular
    double angularLambda = C / (objA->invInertia + objB->invInertia);



    // Aplicar torques correctivos ajustados
    objA->AddTorque(-angularLambda);  // Torque negativo para objA
    objB->AddTorque(-angularLambda);  // Torque positivo para objB
}
