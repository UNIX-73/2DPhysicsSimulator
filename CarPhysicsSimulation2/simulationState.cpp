#include "simulationState.h"
#include "springConstraint.h"
#include "angularConstraint.h"

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

    std::vector<sf::RectangleShape>testshapes = { testShape, testShape2 };

    std::shared_ptr<GraphicObject> gtest = std::make_shared<GraphicObject>(testshapes);

    c.pObjTest = std::make_shared<PhysicsObject>(gtest);

    c.pObjTest->inertia = 400.0;

    std::cout << std::to_string(c.pObjTest->mass) << std::endl;

    simulationManager.AddPhysicsObject(c.pObjTest);


    std::shared_ptr<GraphicObject> gtest2 = std::make_shared<GraphicObject>(testshapes);
    c.pObjTest2 = std::make_shared<PhysicsObject>(gtest2, PhysicsState(V2(5.0, 0.0)));
    c.pObjTest2->inertia = 400.0;

    simulationManager.AddPhysicsObject(c.pObjTest2);

    std::shared_ptr<SpringConstraint> testConstraint = std::make_shared<SpringConstraint>(Constraint(c.pObjTest, c.pObjTest2), 150.0, 10.0, 2.0);
    std::shared_ptr<AngularConstraint> angularTestConstraint = std::make_shared<AngularConstraint>(Constraint(c.pObjTest, c.pObjTest2), 1000.0, 80.0);


    simulationManager.AddConstraint(testConstraint);
    simulationManager.AddConstraint(angularTestConstraint);


}

void SimulationState::EventStep(double step)
{
	c.pObjTest2->AddForce(V2(40.0, 40.0));
}
