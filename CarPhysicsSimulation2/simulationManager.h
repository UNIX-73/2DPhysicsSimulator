#pragma once
#include "physicsManager.h"
#include "graphicWindow.h"
#include "timerManager.h"
#include "inputManager.h"

class SimulationManager
{
public:
	SimulationManager(bool* RUN, int windowWidth, int windowHeight, unsigned int substepsPerFrame, double fps, sf::Color backgroundColor = sf::Color(181, 181, 181));
	~SimulationManager();

	void Update(); //La idea es que está en el while principal

	void UpdateSimulation(); //Llamada desde el timer cuando pasa el tiempo del step
	void UpdateGraphics(); //Llamada como callback desde el timer
	void UpdateWindow();
	void UpdatePhysics(double step); //Also updates graphic objects of physicsObjects
	void UpdateInput(double step);

	void SetEventStepCallback(const std::function<void(double)>& eventStep);
	void SetEventStartCallback(const std::function<void()>& eventStart);

	void AddGraphicObject(std::shared_ptr<GraphicObject> obj);
	void AddPhysicsState(std::shared_ptr<PhysicsState> state);
	void AddPhysicsObject(std::shared_ptr<PhysicsObject> obj);
	void AddConstraint(std::shared_ptr<Constraint> constraint);

	void Stop();

	//TODO: Funciones de Remove
	

	TimerManager stepManager;
	GraphicWindow gWindow;
	PhysicsManager pManager;
	InputManager iManager;

private:
	bool* RUN;
	double step;

	sf::Color backgroundColor;


	//EVENTS
	std::function<void(double)> eventStep = nullptr; //Es el callback que se ejecuta antes de cada step, funciona como un eventStep
	std::function<void()> eventStart = nullptr;
};