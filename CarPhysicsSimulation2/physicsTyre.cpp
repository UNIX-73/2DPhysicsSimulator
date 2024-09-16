#include "physicsTyre.h"


void PhysicsTyre::SolveCustomForces(double step)
{
    PhysicsObject::SolveCustomForces(step);

    // Obtener la dirección hacia adelante de la rueda en ángulo 0 en el mundo
    V2 forwardDir = V2(1.0, 0.0); // Inicialmente apuntando a lo largo del eje X global (ángulo 0)

    // Rotar la dirección hacia adelante según el ángulo de la rueda (wAngle en grados)
    forwardDir = forwardDir.rotateVector(wAngle);

    // Obtener la dirección lateral, que es perpendicular a forwardDir
    V2 lateralDir = forwardDir.perpendicular(); // Esta también debe estar en coordenadas globales

    // Proyectar la velocidad del objeto en las direcciones longitudinales y laterales
    double longVel = wVel.dot(forwardDir);         // Componente de la velocidad a lo largo del eje de la rueda
    double latVel = wVel.dot(lateralDir);          // Componente de la velocidad perpendicular al eje de la rueda

    // Calcular la fuerza normal sobre la rueda (considerando la masa)
    double gravity = 9.81; // Aceleración de la gravedad
    double supportedMass = this->mass; // Asume que tienes acceso a la masa soportada por la rueda
    double normalForce = supportedMass * gravity;

    // Calcular la fuerza longitudinal, afectada por la masa soportada
    double traction = -longVel * tractionCoefficient * normalForce;

    // Calcular la fuerza lateral, afectada por la masa soportada
    double lateralForce = -latVel * lateralFrictionCoefficient * normalForce;

    // La fuerza total es la suma de las fuerzas longitudinales y laterales
    V2 totalForce = forwardDir * traction + lateralDir * lateralForce;

    // Aplicar la fuerza en el centro de la rueda
    AddForce(totalForce);

    // Calcular y aplicar el torque resultante de la rotación de la rueda
    double rollingResistance = -wAngularVel * rollingResistanceCoefficient * normalForce;
    AddTorque(rollingResistance);
}
