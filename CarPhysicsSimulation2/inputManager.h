#pragma once
#include <SFML/Graphics.hpp>
#include "graphicWindow.h"
#include "physicsManager.h"

class InputManager
{
public:
	InputManager(bool* RUN, GraphicWindow& gWindow, PhysicsManager& pManager) :
		RUN(RUN), gWindow(gWindow), pManager(pManager) {};
	~InputManager() {};

	bool KeyPressed(sf::Keyboard::Key key);

	void UpdateInput(double step);

private:
	bool* RUN;
	GraphicWindow& gWindow;
	PhysicsManager& pManager;
};