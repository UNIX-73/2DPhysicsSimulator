#pragma once
#include "simulationManager.h"
#include "carBuilder.h"

//Clase creada para pasar variables entre EventStart y EventStep. Se pueden definir aqu� las variables y se compartir�n.
class SimulationContext
{
public:
	SimulationContext() {};
	~SimulationContext() {};

	//DEFINIR VARIABLES DE AQU� HACIA ABAJO
	std::shared_ptr<PhysicsObject> pObjTest;
	std::shared_ptr<PhysicsObject> pObjTest2;
	std::shared_ptr<PhysicsObject> pObjTest3;


	std::shared_ptr<CarBuilder> car;


	//_____________________________________
};

class SimulationState
{
public:
	SimulationState(SimulationManager& simulationManager) :
		simulationManager(simulationManager) {
		simulationManager.SetEventStartCallback([this]() { this->EventStart(); });
		simulationManager.SetEventStepCallback([this](double step) { this->EventStep(step); });
	};


private:
	virtual void EventStart();
	virtual void EventStep(double step);

	SimulationManager& simulationManager;
	SimulationContext c;
};

