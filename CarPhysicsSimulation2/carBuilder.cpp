#include "carBuilder.h"
#include "simulationManager.h"
#include "softConstraint.h"
#include "physicsTyre.h"

CarBuilder::CarBuilder(SimulationManager& simManager, double vAxisLength, double hAxisLength) :
    simManager(simManager) {

    //  ENGINE
    sf::RectangleShape engineShape;
    engineShape.setFillColor(sf::Color(135, 135, 135));
    engineShape.setSize(sf::Vector2f(50.0f, 35.0f));  // Conversión explícita a float
    engineShape.setOrigin(25.0f, 35.0f / 2.0f);  // Conversión explícita a float
    engineShape.setPosition(0, 0);

    std::shared_ptr<GraphicObject> engineGraphic = std::make_shared<GraphicObject>(engineShape);
    engine = std::make_shared<PhysicsObject>(engineGraphic, PhysicsState(V2(-vAxisLength * 0.12, 0.0)));
    engine->UpdateMass(500.0);
    engine->AutoInertia();

    //  HAXIS
    sf::RectangleShape hAxisShape;
    hAxisShape.setFillColor(sf::Color(64, 64, 64));
    hAxisShape.setSize(sf::Vector2f(5.0f, static_cast<float>(hAxisLength)));  // Conversión explícita
    hAxisShape.setOrigin(2.5f, static_cast<float>(hAxisLength) / 2.0f);  // Conversión explícita
    hAxisShape.setPosition(0, 0);

    std::shared_ptr<GraphicObject> fAxisGraphic = std::make_shared<GraphicObject>(hAxisShape);
    fAxis = std::make_shared<PhysicsObject>(fAxisGraphic, PhysicsState(V2(vAxisLength / 2.0, 0.0)));
    fAxis->UpdateMass(40.0);
    fAxis->AutoInertia();

    std::shared_ptr<GraphicObject> rAxisGraphic = std::make_shared<GraphicObject>(hAxisShape);
    rAxis = std::make_shared<PhysicsObject>(rAxisGraphic, PhysicsState(V2(-vAxisLength / 2.0, 0.0)));
    rAxis->UpdateMass(40.0);
    rAxis->AutoInertia();

    //  VAXIS
    sf::RectangleShape vAxisShape;
    vAxisShape.setFillColor(sf::Color(100, 100, 100));
    vAxisShape.setSize(sf::Vector2f(static_cast<float>(vAxisLength), 5.0f));  // Conversión explícita
    vAxisShape.setOrigin(static_cast<float>(vAxisLength) / 2.0f, 2.5f);  // Conversión explícita
    vAxisShape.setPosition(0, 0);

    std::shared_ptr<GraphicObject> vAxisGraphic = std::make_shared<GraphicObject>(vAxisShape);
    vAxis = std::make_shared<PhysicsObject>(vAxisGraphic, PhysicsState(V2(0.0, 0.0)));
    vAxis->UpdateMass(80.0);
    vAxis->AutoInertia();

    //  TYRE
    sf::RectangleShape tyreShape;
    tyreShape.setFillColor(sf::Color(23, 23, 23));
    tyreShape.setSize(sf::Vector2f(35.0f, 15.0f));  // Conversión explícita
    tyreShape.setOrigin(35.0f / 2.0f, 7.5f);  // Conversión explícita
    tyreShape.setPosition(0, 0);

    std::shared_ptr<GraphicObject> flTyreGraphic = std::make_shared<GraphicObject>(tyreShape);
    std::shared_ptr<GraphicObject> frTyreGraphic = std::make_shared<GraphicObject>(tyreShape);

    std::shared_ptr<GraphicObject> rlTyreGraphic = std::make_shared<GraphicObject>(tyreShape);
    std::shared_ptr<GraphicObject> rrTyreGraphic = std::make_shared<GraphicObject>(tyreShape);

    flTyre = std::make_shared<PhysicsTyre>(PhysicsObject(flTyreGraphic, PhysicsState(V2(vAxisLength / 2.0, hAxisLength / 2.0))), 185.0);
    flTyre->UpdateMass(20.0);
    flTyre->AutoInertia();

    frTyre = std::make_shared<PhysicsTyre>(PhysicsObject(frTyreGraphic, PhysicsState(V2(vAxisLength / 2.0, -hAxisLength / 2.0))), 185.0);
    frTyre->UpdateMass(20.0);
    frTyre->AutoInertia();

    rlTyre = std::make_shared<PhysicsTyre>(PhysicsObject(rlTyreGraphic, PhysicsState(V2(-vAxisLength / 2.0, hAxisLength / 2.0))), 185.0);
    rlTyre->UpdateMass(20.0);
    rlTyre->AutoInertia();

    rrTyre = std::make_shared<PhysicsTyre>(PhysicsObject(rrTyreGraphic, PhysicsState(V2(-vAxisLength / 2.0, -hAxisLength / 2.0))), 185.0);
    rrTyre->UpdateMass(20.0);
    rrTyre->AutoInertia();

    
    CreateCar();
    //-------------------------------------------CONSTRAINTS-------------------------------------------
    
    //  Engine
    std::shared_ptr<SpringConstraint> engineToVAxis = std::make_shared<SpringConstraint>(Constraint(engine, vAxis), 0.0, 900000.0, 20000.0, V2::ZeroVector, V2(-vAxisLength * 0.12, 0.0));
    simManager.AddConstraint(engineToVAxis);

    std::shared_ptr<AngularConstraint> engineToVAxisAngle = std::make_shared<AngularConstraint>(Constraint(engine, vAxis), 90000.0, 20000.0);
    simManager.AddConstraint(engineToVAxisAngle);


    //  FAxis
    std::shared_ptr<SpringConstraint> fAxisToVAxisLength = std::make_shared<SpringConstraint>(Constraint(vAxis, fAxis), 0.0, 400000.0, 1000.0, V2(vAxisLength / 2.0, 0.0));
    simManager.AddConstraint(fAxisToVAxisLength);
    
    std::shared_ptr<AngularConstraint> fAxisToVAxisAngle = std::make_shared<AngularConstraint>(Constraint(vAxis, fAxis), 400000.0, 1000.0);
    simManager.AddConstraint(fAxisToVAxisAngle);


    //  RAxis
    std::shared_ptr<SpringConstraint> rAxisToVAxisLength = std::make_shared<SpringConstraint>(Constraint(vAxis, rAxis), 0.0, 400000.0, 1000.0, V2(-vAxisLength / 2.0, 0.0));
    simManager.AddConstraint(rAxisToVAxisLength);

    std::shared_ptr<AngularConstraint> rAxisToVAxisAngle = std::make_shared<AngularConstraint>(Constraint(vAxis, rAxis), 400000.0, 1000.0);
    simManager.AddConstraint(rAxisToVAxisAngle);



    //  FLTyre
    std::shared_ptr<SpringConstraint> flTyreToFAxis = std::make_shared<SpringConstraint>(Constraint(fAxis, flTyre), 0.0, 100000.0, 10000.0, V2(0.0, hAxisLength / 2.0));
    simManager.AddConstraint(flTyreToFAxis);

    //  FRTyre
    std::shared_ptr<SpringConstraint> frTyreToFAxis = std::make_shared<SpringConstraint>(Constraint(fAxis, frTyre), 0.0, 100000.0, 10000.0, V2(0.0, -hAxisLength / 2.0));
    simManager.AddConstraint(frTyreToFAxis);


    //  RLTyre
    std::shared_ptr<SpringConstraint> rlTyreToFAxis = std::make_shared<SpringConstraint>(Constraint(rAxis, rlTyre), 0.0, 100000.0, 10000.0, V2(0.0, hAxisLength / 2.0));
    simManager.AddConstraint(rlTyreToFAxis);

    std::shared_ptr<AngularConstraint> rlTyreToFAxisAngle = std::make_shared<AngularConstraint>(Constraint(rlTyre, rAxis), 100000.0, 10000.0);
    simManager.AddConstraint(rlTyreToFAxisAngle);

    //  RRTyre
    std::shared_ptr<SpringConstraint> rrTyreToFAxis = std::make_shared<SpringConstraint>(Constraint(rAxis, rrTyre), 0.0, 100000.0, 10000.0, V2(0.0, -hAxisLength / 2.0));
    simManager.AddConstraint(rrTyreToFAxis);

    std::shared_ptr<AngularConstraint> rrTyreToFAxisAngle = std::make_shared<AngularConstraint>(Constraint(rrTyre, rAxis), 100000.0, 10000.0);
    simManager.AddConstraint(rrTyreToFAxisAngle);
}

std::vector<std::shared_ptr<PhysicsObject>> CarBuilder::GetCarPhysicsRefs()
{
    return { fAxis, rAxis, vAxis, flTyre, frTyre, rlTyre, rrTyre, engine };
}

void CarBuilder::CreateCar()
{
    std::vector<std::shared_ptr<PhysicsObject>> carParts = { fAxis, rAxis, vAxis, flTyre, frTyre, rlTyre, rrTyre, engine };

    for (auto part : carParts)
    {
        if (part)
        {
            simManager.AddPhysicsObject(part);
        }
    }
}
