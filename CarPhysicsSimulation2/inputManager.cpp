#include "inputManager.h"
#include <iostream>

bool InputManager::KeyPressed(sf::Keyboard::Key key)
{
	if (!sf::Keyboard::isKeyPressed(key)) return false;
	else return true;
}

void InputManager::UpdateInput(double step)
{
	if (KeyPressed(sf::Keyboard::Escape)) *RUN = false;

	//Camera
	if (KeyPressed(sf::Keyboard::Left)) gWindow.MoveCamera(V2(-1.0, 0.0), step);

	if (KeyPressed(sf::Keyboard::Right)) gWindow.MoveCamera(V2(1.0, 0.0), step);

	if (KeyPressed(sf::Keyboard::Up)) gWindow.MoveCamera(V2(0.0, -1.0), step);

	if (KeyPressed(sf::Keyboard::Down)) gWindow.MoveCamera(V2(0.0, 1.0), step);

	if (KeyPressed(sf::Keyboard::Multiply)) gWindow.ChangeZoom(1.0, step);

	if (KeyPressed(sf::Keyboard::Subtract)) gWindow.ChangeZoom(-1.0, step);
}
