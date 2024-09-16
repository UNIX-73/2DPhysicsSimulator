#pragma once
#include "physicsObject.h"
#include "simulationManager.h"

class CarBuilder
{
public:
    CarBuilder(SimulationManager& simManager, double vAxisLength, double hAxisLength);


    std::vector<std::shared_ptr<PhysicsObject>> GetCarPhysicsRefs();

    std::shared_ptr<PhysicsObject> engine = nullptr;
    std::shared_ptr<PhysicsObject> fAxis = nullptr;
    std::shared_ptr<PhysicsObject> rAxis = nullptr;
    std::shared_ptr<PhysicsObject> vAxis = nullptr;
    std::shared_ptr<PhysicsObject> flTyre = nullptr;
    std::shared_ptr<PhysicsObject> frTyre = nullptr;
    std::shared_ptr<PhysicsObject> rlTyre = nullptr;
    std::shared_ptr<PhysicsObject> rrTyre = nullptr;

private:
    SimulationManager& simManager;



    void CreateCar();
};
