#include "simulationState.h"
#include "constraintSolver.h"
#include "rigidConstraint.h"

void SimulationState::EventStart()
{
    std::vector<std::shared_ptr<Constraint>> constraints = {};

    std::shared_ptr<PhysicsState> obj1 = std::make_shared<PhysicsState>();
    obj1->UpdateMass(20.0);
    std::shared_ptr<PhysicsState> obj2 = std::make_shared<PhysicsState>();
    obj2->UpdateInertia(30.0);
    obj2->wAngularVel = 2.1;
    std::shared_ptr<PhysicsState> obj3 = std::make_shared<PhysicsState>();
    std::shared_ptr<PhysicsState> obj4 = std::make_shared<PhysicsState>();
    obj4->wVel.x = 21.0;

    std::shared_ptr<RigidConstraint> testConstraint1 = std::make_shared<RigidConstraint>(Constraint(obj1, obj2));
    std::shared_ptr<RigidConstraint> testConstraint2 = std::make_shared<RigidConstraint>(Constraint(obj2, obj3));
    std::shared_ptr<RigidConstraint> testConstraint3 = std::make_shared<RigidConstraint>(Constraint(obj3, obj4));
    std::shared_ptr<RigidConstraint> testConstraint4 = std::make_shared<RigidConstraint>(Constraint(obj2, obj1));
    std::shared_ptr<RigidConstraint> testConstraint5 = std::make_shared<RigidConstraint>(Constraint(obj1, obj3));
    std::shared_ptr<RigidConstraint> testConstraint6 = std::make_shared<RigidConstraint>(Constraint(obj1, obj4));
    std::shared_ptr<RigidConstraint> testConstraint7 = std::make_shared<RigidConstraint>(Constraint(obj2, obj1));

    constraints = { testConstraint1, testConstraint2, testConstraint3, testConstraint4, testConstraint5, testConstraint6, testConstraint7 };

    ConstraintSolver solver(1.0, constraints);

    solver.SolveConstraints();



    /*
    std::cout << "W: " << std::endl;
    solver.PrintW();

    std::cout << "Q: " << std::endl;
    solver.PrintQ();

    std::cout << "J: " << std::endl;
    solver.PrintJ();

    std::cout << "q_dot: " << std::endl;
    solver.Print_q_dot();
    */
}

void SimulationState::EventStep(double step)
{    

}
