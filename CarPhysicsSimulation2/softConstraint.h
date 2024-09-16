#pragma once
#include "constraint.h"
#include "springConstraint.h"
#include "angularConstraint.h"

class SoftConstraint : public Constraint {
public:
    SoftConstraint(const Constraint& constraintObj, double restLength, double stiffness, double damping) :
        Constraint(constraintObj),  // Usa una referencia constante o un puntero inteligente
        stiffness(stiffness),
        damping(damping),
        springConstraint(SpringConstraint(constraintObj, restLength, stiffness, damping)),
        angularConstraint(AngularConstraint(constraintObj, stiffness, damping))
    {}

    virtual ~SoftConstraint() = default;

    virtual void SolveConstraint(double step) override;

private:
    double stiffness;
    double damping;

    SpringConstraint springConstraint;
    AngularConstraint angularConstraint;
};
