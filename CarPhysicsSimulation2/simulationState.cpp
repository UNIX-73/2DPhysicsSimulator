#include "simulationState.h"
#include "constraintSolver.h"
#include "rigidConstraint.h"

void SimulationState::EventStart()
{
    /*
	std::cout << "Simulation Started" << std::endl;

    
    sf::RectangleShape testShape;
    testShape.setFillColor(sf::Color::Red);
    testShape.setSize(sf::Vector2f(5, 5));
    testShape.setOrigin(2.5f, 2.5f);
    testShape.setPosition(-15, 0);
    
    
    sf::RectangleShape testShape2;
    testShape2.setFillColor(sf::Color::Blue);
    testShape2.setSize(sf::Vector2f(20, 20));
    testShape2.setOrigin(10, 10);
    testShape2.setPosition(0, 0);

    std::vector<sf::RectangleShape>testshapes = { testShape2, testShape };

    std::shared_ptr<GraphicObject> gtest = std::make_shared<GraphicObject>(testshapes);
    c.pObjTest = std::make_shared<PhysicsObject>(gtest);

    c.pObjTest->UpdateInertia(1000.0);


    simulationManager.AddPhysicsObject(c.pObjTest);


    std::shared_ptr<GraphicObject> gtest2 = std::make_shared<GraphicObject>(testshapes);
    c.pObjTest2 = std::make_shared<PhysicsObject>(gtest2, PhysicsState(V2(150.0, -100.0)));
    c.pObjTest2->UpdateInertia(400.0);

    simulationManager.AddPhysicsObject(c.pObjTest2);


    std::shared_ptr<GraphicObject> gtest3 = std::make_shared<GraphicObject>(testshapes);
    c.pObjTest3 = std::make_shared<PhysicsObject>(gtest3, PhysicsState(V2(300.0, 0.0)));
    c.pObjTest3->inertia = 400.0;


    simulationManager.AddPhysicsObject(c.pObjTest3);





    std::shared_ptr<RigidConstraint> testConstraint = std::make_shared<RigidConstraint>(Constraint(c.pObjTest, c.pObjTest2), 150.0, 10.0);
    simulationManager.AddConstraint(testConstraint);

    std::shared_ptr<RigidAngularConstraint> testConstraintA1 = std::make_shared<RigidAngularConstraint>(Constraint(c.pObjTest, c.pObjTest2));
    simulationManager.AddConstraint(testConstraintA1);



    std::shared_ptr<RigidConstraint> testConstraint2 = std::make_shared<RigidConstraint>(Constraint(c.pObjTest2, c.pObjTest3), 150.0, 10.0);
   // simulationManager.AddConstraint(testConstraint2);

    std::shared_ptr<RigidConstraint> testConstraint3 = std::make_shared<RigidConstraint>(Constraint(c.pObjTest3, c.pObjTest), 150.0, 10.0);
    //simulationManager.AddConstraint(testConstraint3);





    c.car = std::make_shared<CarBuilder>(CarBuilder(simulationManager, 200.0, 100.0));
    */



    sf::RectangleShape testShape;
    testShape.setFillColor(sf::Color::Red);
    testShape.setSize(sf::Vector2f(5, 5));
    testShape.setOrigin(2.5f, 2.5f);
    testShape.setPosition(0, 0);

    std::vector<sf::RectangleShape> shape1 = { testShape };

    std::shared_ptr<GraphicObject> g1 = std::make_shared<GraphicObject>(shape1);
    std::shared_ptr<GraphicObject> g2 = std::make_shared<GraphicObject>(shape1);
    std::shared_ptr<GraphicObject> g3 = std::make_shared<GraphicObject>(shape1);


    c.pObjTest = std::make_shared<PhysicsObject>(g1);
    c.pObjTest->UpdateMass(20.0);
    c.pObjTest->wPos = V2(-20.0, 0.0);

    c.pObjTest2 = std::make_shared<PhysicsObject>(g2);
    c.pObjTest2->UpdateMass(45.0);


    c.pObjTest3 = std::make_shared<PhysicsObject>(g3);
    c.pObjTest3->UpdateMass(75.0);
    c.pObjTest3->wPos = V2(0.0, -20.0);



    std::shared_ptr<RigidConstraint> testConstraint1 = std::make_shared<RigidConstraint>(Constraint(c.pObjTest, c.pObjTest2));
    std::shared_ptr<RigidConstraint> testConstraint2 = std::make_shared<RigidConstraint>(Constraint(c.pObjTest2, c.pObjTest3));



    simulationManager.AddPhysicsObject(c.pObjTest);
    simulationManager.AddPhysicsObject(c.pObjTest2);
    simulationManager.AddPhysicsObject(c.pObjTest3);

    simulationManager.AddConstraint(testConstraint1);
    simulationManager.AddConstraint(testConstraint2);

}

void SimulationState::EventStep(double step)
{
    c.pObjTest3->AddForce(V2(1000.0, 0.0));
}
