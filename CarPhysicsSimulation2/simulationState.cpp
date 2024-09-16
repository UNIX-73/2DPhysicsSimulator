#include "simulationState.h"
#include "softConstraint.h"
#include "rigidConstraint.h"
#include "rigidAngularConstraint.h"

void SimulationState::EventStart()
{
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

}

void SimulationState::EventStep(double step)
{    
    c.car->rAxis->AddForce(V2(500000.0 , 0.0).rotateVector(c.car->vAxis->wAngle));
    c.car->flTyre->wAngle = c.car->vAxis->wAngle + 15.0;
    c.car->frTyre->wAngle = c.car->vAxis->wAngle + 15.0;


    c.pObjTest->AddForce(V2(19.0, 0.0));
}
