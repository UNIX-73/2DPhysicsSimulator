#pragma once
#include "V2.h"

class PhysicsState
{
public:
    // Constructor con valores predeterminados
    PhysicsState(V2 pos = V2(0.0, 0.0),
        V2 vel = V2(0.0, 0.0),
        V2 acc = V2(0.0, 0.0),
        double angle = 0.0,
        double angularVel = 0.0,
        double angularAcc = 0.0,
        V2 force = V2(0.0, 0.0),
        double torque = 0.0,
        double mass = 1.0,
        double inertia = 1.0,
        bool simulatePhysics = true)
        : wPos(pos), wVel(vel), wAcc(acc),
        wAngle(angle), wAngularVel(angularVel), wAngularAcc(angularAcc),
        currentForce(force), currentTorque(torque),
        mass(mass), inertia(inertia), simulatePhysics(simulatePhysics)
    {

    }

    virtual ~PhysicsState() {};

    bool simulatePhysics = true;

    V2 wPos;
    V2 wVel;
    V2 wAcc;

    double wAngle;
    double wAngularVel;
    double wAngularAcc;

    V2 currentForce;
    double currentTorque;

    double mass;
    double inertia;

    void AddForce(V2 force, V2 point = V2::ZeroVector);
    void AddTorque(double torque);
};
