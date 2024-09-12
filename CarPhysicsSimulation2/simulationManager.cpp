#include "simulationManager.h"

SimulationManager::SimulationManager(bool* RUN, int windowWidth, int windowHeight, double stepsPerSecond, double fps, sf::Color backgroundColor) :
	RUN(RUN), gWindow(windowWidth, windowHeight), pManager(PhysicsManager()), stepManager(stepsPerSecond, fps), iManager(RUN, this->gWindow, this->pManager), backgroundColor(backgroundColor)
{
	stepManager.SetStepFunction(std::bind(&SimulationManager::UpdateSimulation, this));
	stepManager.SetGraphicFunction(std::bind(&SimulationManager::UpdateGraphics, this));
	
	step = 1.0 / stepsPerSecond;
}

SimulationManager::~SimulationManager()
{
	gWindow.window.close();
	gWindow.~GraphicWindow();
}

void SimulationManager::Update()
{
	//EVENT START
	if (eventStart)
	{
		eventStart();
		eventStart = nullptr;
	}

	stepManager.UpdateTimer();
}

void SimulationManager::UpdateSimulation() //Llamada desde el stepManager cada step
{
	if (gWindow.window.isOpen())
	{
		UpdateInput(step);
		UpdateWindow();

		//EVENT STEP
		if (eventStep) {
			eventStep(step);
		}

		UpdatePhysics(step);
	}
	else
	{
		*RUN = false;
	}
}

void SimulationManager::UpdateGraphics() //Llamada como callback desde el step manager cada frame
{
	gWindow.UpdateGraphics(backgroundColor);
}

void SimulationManager::UpdateWindow()
{
	gWindow.UpdateWindow();
}

void SimulationManager::UpdatePhysics(double step)
{
	pManager.Update(step);
}

void SimulationManager::UpdateInput(double step)
{
	iManager.UpdateInput(step);
}

void SimulationManager::SetEventStepCallback(const std::function<void(double)>& eventStep)
{
	this->eventStep = eventStep;
}

void SimulationManager::SetEventStartCallback(const std::function<void()>& eventStart)
{
	this->eventStart = eventStart;
}

void SimulationManager::AddGraphicObject(std::shared_ptr<GraphicObject> obj)
{
	gWindow.AddGraphicObject(obj);
}

void SimulationManager::AddPhysicsState(std::shared_ptr<PhysicsState> state)
{
	pManager.AddPhysicsState(state);
}

void SimulationManager::AddPhysicsObject(std::shared_ptr<PhysicsObject> obj)
{
	pManager.AddPhysicsObject(obj);

	AddGraphicObject(obj->graphicObject);
}
