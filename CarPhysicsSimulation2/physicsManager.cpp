#include "physicsManager.h"
#include "constraintSolver.h"

PhysicsManager::PhysicsManager() {

}


void PhysicsManager::AddPhysicsState(std::shared_ptr<PhysicsState>& pState)
{
	physicsStates.push_back(pState);
}

void PhysicsManager::AddPhysicsObject(std::shared_ptr<PhysicsObject>& pObj)
{
    physicsStates.push_back(std::static_pointer_cast<PhysicsState>(pObj));
}

void PhysicsManager::RemovePhysicsState(std::shared_ptr<PhysicsState>& pState)
{
    auto it = std::find(physicsStates.begin(), physicsStates.end(), pState);
    if (it != physicsStates.end())
    {
        physicsStates.erase(it);
    }
}

void PhysicsManager::RemovePhysicsObject(std::shared_ptr<PhysicsObject>& pObj)
{
    auto pState = std::static_pointer_cast<PhysicsState>(pObj);
    RemovePhysicsState(pState);
}

void PhysicsManager::AddConstraint(std::shared_ptr<Constraint>& constraint)
{
    physicsConstraints.push_back(constraint);
}

void PhysicsManager::RemoveConstraint(std::shared_ptr<Constraint>& constraint)
{
    auto it = std::find(physicsConstraints.begin(), physicsConstraints.end(), constraint);
    if (it != physicsConstraints.end())
    {
        physicsConstraints.erase(it);
    }
}


void PhysicsManager::Update(double step)
{
	UpdatePhysics(step);

	UpdatePhysicsObjectGraphics();
}

void PhysicsManager::UpdatePhysics(double step)
{
    for (std::shared_ptr<PhysicsState>& state : physicsStates)
    {
        if (state->simulatePhysics)
        {
            state->SolveCustomForces(step);

            // Realiza la integración con RK4
            IntegrateRk4(step, state);

            // Restablece las fuerzas y torques después de la integración
            state->currentForce = V2::ZeroVector;
            state->currentTorque = 0.0;
        }
    }

    // Resuelve los constraints después de actualizar las físicas de los objetos
    
    //TODO: constraints


}

void PhysicsManager::UpdatePhysicsObjectGraphics()
{
    for (auto& state : physicsStates)
    {
        state->UpdateGraphics();  // Actualiza gráficos solo si es un PhysicsObject
    }
}

void PhysicsManager::IntegrateRk4(double step, std::shared_ptr<PhysicsState>& state)
{
    // Funciones para calcular las derivadas lineales
    auto velocityFunc = [](const PhysicsState& obj) -> V2 {
        return obj.wVel;  // Derivada de la posición es la velocidad
        };

    auto accelerationFunc = [](const PhysicsState& obj) -> V2 {
        return obj.currentForce * obj.invMass;  // Aceleración es fuerza * masa inversa
        };

    // Funciones para calcular las derivadas angulares
    auto angularVelocityFunc = [](const PhysicsState& obj) -> double {
        return obj.wAngularVel;  // Derivada del ángulo es la velocidad angular
        };

    auto angularAccelerationFunc = [](const PhysicsState& obj) -> double {
        return obj.currentTorque * obj.invInertia;  // Aceleración angular es torque * inercia inversa
        };

    // Almacenar el estado inicial
    V2 initialPosition = state->wPos;
    V2 initialVelocity = state->wVel;
    double initialAngle = state->wAngle;
    double initialAngularVelocity = state->wAngularVel;

    // Primer paso de RK4 (k1)
    V2 k1_position = velocityFunc(*state) * step;
    V2 k1_velocity = accelerationFunc(*state) * step;
    double k1_angle = angularVelocityFunc(*state) * step;
    double k1_angularVelocity = angularAccelerationFunc(*state) * step;

    // Actualizar para el segundo cálculo de RK4 (k2)
    state->wPos = initialPosition + k1_position * 0.5;
    state->wVel = initialVelocity + k1_velocity * 0.5;
    state->wAngle = initialAngle + k1_angle * 0.5;
    state->wAngularVel = initialAngularVelocity + k1_angularVelocity * 0.5;

    // Recalcula la aceleración lineal y angular con el estado actualizado
    k1_velocity = accelerationFunc(*state) * step;
    k1_angularVelocity = angularAccelerationFunc(*state) * step;

    V2 k2_position = velocityFunc(*state) * step;
    V2 k2_velocity = accelerationFunc(*state) * step;
    double k2_angle = angularVelocityFunc(*state) * step;
    double k2_angularVelocity = angularAccelerationFunc(*state) * step;

    // Actualizar para el tercer cálculo de RK4 (k3)
    state->wPos = initialPosition + k2_position * 0.5;
    state->wVel = initialVelocity + k2_velocity * 0.5;
    state->wAngle = initialAngle + k2_angle * 0.5;
    state->wAngularVel = initialAngularVelocity + k2_angularVelocity * 0.5;

    // Recalcula la aceleración lineal y angular con el estado actualizado
    k2_velocity = accelerationFunc(*state) * step;
    k2_angularVelocity = angularAccelerationFunc(*state) * step;

    V2 k3_position = velocityFunc(*state) * step;
    V2 k3_velocity = accelerationFunc(*state) * step;
    double k3_angle = angularVelocityFunc(*state) * step;
    double k3_angularVelocity = angularAccelerationFunc(*state) * step;

    // Actualizar para el cuarto cálculo de RK4 (k4)
    state->wPos = initialPosition + k3_position;
    state->wVel = initialVelocity + k3_velocity;
    state->wAngle = initialAngle + k3_angle;
    state->wAngularVel = initialAngularVelocity + k3_angularVelocity;

    // Recalcula la aceleración lineal y angular con el estado actualizado
    k3_velocity = accelerationFunc(*state) * step;
    k3_angularVelocity = angularAccelerationFunc(*state) * step;

    V2 k4_position = velocityFunc(*state) * step;
    V2 k4_velocity = accelerationFunc(*state) * step;
    double k4_angle = angularVelocityFunc(*state) * step;
    double k4_angularVelocity = angularAccelerationFunc(*state) * step;

    // Calcular el estado final combinando los resultados de RK4
    state->wPos = initialPosition + (k1_position + 2.0 * k2_position + 2.0 * k3_position + k4_position) / 6.0;
    state->wVel = initialVelocity + (k1_velocity + 2.0 * k2_velocity + 2.0 * k3_velocity + k4_velocity) / 6.0;
    state->wAngle = initialAngle + (k1_angle + 2.0 * k2_angle + 2.0 * k3_angle + k4_angle) / 6.0;
    state->wAngularVel = initialAngularVelocity + (k1_angularVelocity + 2.0 * k2_angularVelocity + 2.0 * k3_angularVelocity + k4_angularVelocity) / 6.0;
}



