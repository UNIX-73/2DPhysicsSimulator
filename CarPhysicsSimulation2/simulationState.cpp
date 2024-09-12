#include "simulationState.h"

void SimulationState::EventStart()
{
	std::cout << "Simulation Started" << std::endl;

    sf::RectangleShape testShape;
    testShape.setFillColor(sf::Color::Red);
    testShape.setSize(sf::Vector2f(20, 20));
    testShape.setOrigin(10, 10);
    testShape.setRotation(140.0f);
    testShape.setPosition(100, 0);

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
}

void SimulationState::EventStep(double step)
{
	c.pObjTest->AddForce(V2(2.0, 0.0));
    c.pObjTest->AddTorque(1.0);
}
